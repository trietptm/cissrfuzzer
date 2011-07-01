#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <lines.hpp>
#include <name.hpp>
#include <allins.hpp>
#include <vector>

#define CONSTVALUE 0
#define VARVALUE 1
#define VARVALUEVULN 2
#define UNDEFINED 3

#define STANDART 1
#define TRAMPOLINE 2
#define WRAPPER 3

struct TFuncMalloc 
{
	char alloc_func_name[MAXSTR];//name of malloc function
	int push_malloc_size_count;//number of parameter that specifies size to allocate
	ea_t address;
	int type;//standart, trampoline, wrapper
	TFuncMalloc(char* f_name,int m_size_count )
	{
		qstrncpy(alloc_func_name,f_name,MAXSTR);
		push_malloc_size_count =m_size_count;
		address= BADADDR;
		type = STANDART;
	}
	TFuncMalloc(char* f_name,int m_size_count, ea_t _addr, int _type )
	{
		qstrncpy(alloc_func_name,f_name,MAXSTR);
		push_malloc_size_count =m_size_count;
		address = _addr;
		type = _type;
	}
};

struct TFuncMallocWrapper 
{
	char alloc_func_name[MAXSTR];//name of malloc function
	char ancestor[MAXSTR];//name of original
	int push_malloc_size_count;//number of parameter that specifies size to allocate
	ea_t address;
	int type;//undefined, trampoline, wrapper
	TFuncMallocWrapper(char* f_name, char* _ancestor, int m_size_count )
	{
		qstrncpy(alloc_func_name,f_name,MAXSTR);
		qstrncpy(ancestor,_ancestor,MAXSTR);
		push_malloc_size_count =m_size_count;
		address= BADADDR;
		type = STANDART;
	}
	TFuncMallocWrapper(char* f_name, char* _ancestor, int m_size_count, ea_t _addr, int _type )
	{
		qstrncpy(alloc_func_name,f_name,MAXSTR);
		qstrncpy(ancestor,_ancestor,MAXSTR);
		push_malloc_size_count =m_size_count;
		address = _addr;
		type = _type;
	}
};

struct TFuncMalloc_call
{
	ea_t address;
	ea_t address_of_push;
	ea_t address_of_last_size_object_modified;
	uint32 value;
	int type;//0 - const, 1 - var, 2- var potentional vulnerabel, 3 - undefined
	
	TFuncMalloc_call(ea_t _addr,int _type )
	{
		address = _addr;
		type = _type;
		value = 0;
		address_of_last_size_object_modified = BADADDR;
	}
	
	TFuncMalloc_call(ea_t _addr,int _type, uint32 _value )
	{
		address = _addr;
		type = _type;
		value = _value;
		address_of_last_size_object_modified = BADADDR;
	}
	TFuncMalloc_call(ea_t _addr,int _type, uint32 _value, ea_t last_src_addr )
	{
		address = _addr;
		type = _type;
		value = _value;
		address_of_last_size_object_modified = last_src_addr;
	}

};

//std::vector<TFuncMalloc> funcMalloc;
//std::vector<TFuncMalloc_call> Malloc_calls;
qvector <TFuncMalloc> funcMalloc;
qvector <TFuncMallocWrapper> funcMalloc_wrappers;
qvector<TFuncMalloc_call> Malloc_calls;
//("malloc", 1), ("RtlAllocateHeap", 1);

//funcMalloc.pushback(TFuncMalloc("malloc", 1));
//funcMalloc.pushback(TFuncMalloc("RtlAllocateHeap", 1));

int does_exist(TFuncMallocWrapper new_func_malloc)
{
	for(int i = 0; i< funcMalloc_wrappers.size(); i++){
		if(funcMalloc_wrappers[i].address == new_func_malloc.address)return 1;
	}
	return 0;
}

int IDAP_init(void)
{
	if(inf.filetype != f_ELF && inf.filetype != f_PE)    {
		error("Executable format must be PE or ELF, sorry.");
		return PLUGIN_SKIP;
	}

	return PLUGIN_KEEP;

}

void IDAP_term(void)
{
	return;
}



//ea_t loc - address of import
//size - len of array
//returns list of xrefs to, and size of list array
ea_t* find_import_xref(ea_t loc, int *size)
{
	//*size = 0;	
	int count = 0, i = 0;
	xrefblk_t xb;
	ea_t *list;
	for(bool ok = xb.first_to(loc, XREF_ALL); ok; ok = xb.next_to()) {
		//msg("Caller to ExAllocatePoolWithTag %a \n", xb.from); 
		count++;
	}

//	msg("find_import_xref %d \n", count); 

	list = (ea_t*)qalloc(sizeof(ea_t) * count);
	if(!list){
		msg("qalloc failed: bytes %a \n", count);
		return NULL;
	}

	for (bool ok = xb.first_to(loc, XREF_ALL); ok; ok = xb.next_to()) {
		//*list++ = xb.from;
		list[i] = xb.from;
		i++;
	}
//	msg("find_import_xref i = %d \n", i); 
	*size = count;
	return list;	
}

ea_t find_import_loc(const char *name)
{
	for (int i = 0; i < get_segm_qty(); i++) {
		segment_t *seg = getnseg(i);
		//msg("segment[%d]  %a %a\n", i, seg->startEA, seg->endEA); 
		if (seg->type == SEG_XTRN) {
			//msg("segment[%d]  == SEG_XTRN\n", i); 
			ea_t loc = get_name_ea(seg->startEA, name);
			if (loc != BADADDR) {
				return loc;
			}
		}
	}
	return BADADDR;	
}

//ea_t find_function_EA_by_name(FILE *file, char *name)
ea_t find_function_EA_by_name(char *name)
{
	int count = strlen(name);

	for (uint i = 0; i < get_func_qty(); ++i)
	{
		func_t *f = getn_func(i);
		char buffer[MAXSTR];
		get_short_name(BADADDR, f->startEA, buffer, MAXSTR);
		//qfprintf(file,"%s \n", buffer);
		if(strncmp(buffer, name, count) == 0){
			return f->startEA;
		}
	}
	return BADADDR;	
}



ea_t find_instruction_backward(ea_t start, uint16 itype)
{
	func_t *f = get_func(start);
	if(f)
	{
		ea_t addr = prev_head(start, f->startEA);
		while (addr != BADADDR)
		{
			flags_t flags = getFlags(addr);
			if (isHead(flags) && isCode(flags))
			{
				ua_ana0(addr);
				if(cmd.itype == itype)return addr;

			}
			addr = prev_head(addr, f->startEA);
		}
	}
	return BADADDR;
}

ea_t find_instruction_N_times_backward(ea_t start, uint16 itype, int count)
{
	func_t *f = get_func(start);
	int curr_count = 0;
	if(f)
	{
		ea_t addr = prev_head(start, f->startEA);
		while (addr != BADADDR)
		{
			flags_t flags = getFlags(addr);
			if (isHead(flags) && isCode(flags))
			{
				ua_ana0(addr);
				if(cmd.itype == itype)curr_count++;
				if(curr_count == count)return addr;

			}
			addr = prev_head(addr, f->startEA);
		}
	}
	return BADADDR;
}
//TODO: this is not a fucking smart function! this is total crap!!!
//TODO: kill locating algo by function, Cause there a lot of places, where IDA fucking sucks, and dont understand bounds of function!!!!
//replace by discovery up by the tree
ea_t find_instruction_that_changes_operand_backward_smart(ea_t start, op_t operand)
{
	func_t *f = get_func(start);
	char buf[MAXSTR];
	char instr_clean[MAXSTR];
	if(f)
	{
		ea_t addr = prev_head(start, f->startEA);
		while (addr != BADADDR)
		{
			flags_t flags = getFlags(addr);
			if (isHead(flags) && isCode(flags))
			{
				ua_ana0(addr);
				switch(cmd.itype){	
					case NN_lea:
					case NN_pop:
					case NN_shl:
					case NN_shr:					
					case NN_sal:
					case NN_sar:				
					case NN_imul:
					case NN_mul:
					case NN_idiv:
					case NN_div:
					case NN_xor:
					case NN_or:
					case NN_not:
					case NN_neg:
					case NN_inc:
					case NN_dec:
					case NN_add:
					case NN_sub:
					case NN_mov:
					case NN_movsx:
					case NN_movzx:{
						for(int i = 0; cmd.Operands[i].type != o_void; i++){
							if((cmd.Operands[i].type == operand.type) && (cmd.Operands[i].reg == operand.reg)){
								return addr;
							}

					}break;
					default:break;
				}
				}

			}
			addr = prev_head(addr, f->startEA);
		}
	}
	return BADADDR;
}

char* construct_output_filename(char *prefix)
{
	//char result[MAXSTR];
	char *result = (char*)qalloc(MAXSTR);
	get_root_filename(result, MAXSTR);
	qstrncat(result, prefix, MAXSTR);
	return result;
}

/*
op_t get_first_operand(FILE *f, ea_t addr)
{
	char buf[MAXSTR];
	char instr_clean[MAXSTR];
	// Store the disassembled text in buf
	ua_ana0(addr);
	generate_disasm_line(cmd.ea, buf, sizeof(buf)-1);
	// This will appear as colour-tagged text (which will
	// be mostly unreadable in IDA's
	tag_remove(buf, instr_clean, sizeof(instr_clean)-1);
	//qfprintf(f,"get_first_operand disasm instruction: %s\n", instr_clean);

	for(int i = 0; cmd.Operands[i].type != o_void; i++){
		qfprintf(f,"operand number %d, type %d, reg %d, phrase %d, value %a, addr %a\n", i, cmd.Operands[i].type,cmd.Operands[i].reg,
			cmd.Operands[i].phrase,cmd.Operands[i].value, cmd.Operands[i].addr);
		//if(cmd.Operands[i].type == o_reg) return cmd.Operands[i];
	}	
	return cmd.Operands[0];
	
}
*/
op_t get_first_operand_new(ea_t addr)
{
	ua_ana0(addr);

	return cmd.Operands[0];
	
}

//firstly sear
//ea_t loc - address of import
//size - len of array
//returns list of xrefs to, and size of list array
ea_t* find_function_xref(char *name, int *size)
{
	//*size = 0;	
	int count = 0, i = 0;
	*size = 0;
	xrefblk_t xb;
	char funcname_incode[MAXSTR];
	ea_t *list;


	ea_t func_addr = find_import_loc(name);
//	msg("%s in import = %a\n", name, func_addr);
	
	
	if(func_addr == BADADDR){
		qstrncpy(funcname_incode, name, MAXSTR-2);
		qstrncat(funcname_incode, "(", MAXSTR-1);
		//msg("name:%s func_name:%s = \n", name, funcname_incode);
		//malloc_addr = find_function_EA_by_name(f, "ExAllocatePoolWithTag");
		func_addr = find_function_EA_by_name(funcname_incode);
		//msg("%s in import = %a\n", name, func_addr);
	}
	

	if(func_addr == BADADDR)return NULL;

	for(bool ok = xb.first_to(func_addr, XREF_ALL); ok; ok = xb.next_to()) {
		//msg("Caller to ExAllocatePoolWithTag %a \n", xb.from); 
		count++;
	}

//	msg("find_import_xref %d \n", count); 

	list = (ea_t*)qalloc(sizeof(ea_t) * count);
	if(!list){
		msg("qalloc failed: bytes %a \n", count);
		return NULL;
	}

	for (bool ok = xb.first_to(func_addr, XREF_ALL); ok; ok = xb.next_to()) {
		//*list++ = xb.from;
		list[i] = xb.from;
		i++;
	}
//	msg("find_import_xref for %s : %d \n", name, i); 
	*size = count;
	return list;	
}

//firstly sear
//ea_t loc - address of import
//size - len of array
//returns list of xrefs to, and size of list array
ea_t* find_function_xref(ea_t addr, int *size)
{
	//*size = 0;	
	int count = 0, i = 0;
	*size = 0;
	xrefblk_t xb;
	char funcname_incode[MAXSTR];
	ea_t *list;

	if(addr == BADADDR)return NULL;

	for(bool ok = xb.first_to(addr, XREF_ALL); ok; ok = xb.next_to()) {
		count++;
	}


	list = (ea_t*)qalloc(sizeof(ea_t) * count);
	if(!list){
		msg("qalloc failed: bytes %a \n", count);
		return NULL;
	}

	for (bool ok = xb.first_to(addr, XREF_ALL); ok; ok = xb.next_to()) {
		//*list++ = xb.from;
		list[i] = xb.from;
		i++;
	}

	*size = count;
	return list;	
}


int is_trampoline(ea_t address)
{
	ua_ana0(address);
	if(cmd.itype == NN_jmp)return 1;
	return 0;
}

//TODO: better algo of course!!!
//By now - it's full os shitty false positives
int assign_type(ea_t address, int *value)
{
	flags_t flags = getFlags(address);
	if (isHead(flags) && isCode(flags))
	{
		ua_ana0(address);

		if(cmd.itype == NN_mov)
			if(cmd.Operands[1].type == o_imm){
				*value = cmd.Operands[1].value;
				return CONSTVALUE;
			}
			else
				return VARVALUE;

		return VARVALUEVULN;

	}
	else{
		return UNDEFINED;
	}

	return UNDEFINED;

}

void analyze_malloc_xref_ex(char *name, ea_t xref_addr, int push_count)
{
	char buffer[MAXSTR];
	int value = 0;
	int type;
	op_t memory_size_var;
	if(is_trampoline(xref_addr)){
		func_t *func = get_func(xref_addr);
//		msg("analyze_malloc_xref: %s %a - trampoline!\n", name, xref_addr);
		//too easy, how about mov ebp,esp jmp:malloc?
		if(func){
			char buff[MAXSTR];
			get_short_name(BADADDR, func->startEA, buff, MAXSTR);
			//get_long_name(BADADDR, func->startEA, buffer, MAXSTR);
			TFuncMallocWrapper new_malloc = TFuncMallocWrapper(buff, name, push_count, xref_addr, TRAMPOLINE);
			if(!does_exist(new_malloc))
				funcMalloc_wrappers.push_back(new_malloc);
		}
		else{
			TFuncMallocWrapper new_malloc = TFuncMallocWrapper("new malloc", name, push_count, xref_addr, TRAMPOLINE);
			if(!does_exist(new_malloc))
				funcMalloc_wrappers.push_back(new_malloc);
		}
	}



	ea_t push_malloc_size_addr = find_instruction_N_times_backward(xref_addr, NN_push, push_count);

	if(push_malloc_size_addr != BADADDR){
		memory_size_var = get_first_operand_new(push_malloc_size_addr);

		//Allocation of const memory size
		if(memory_size_var.type == o_imm){
			//msg("analyze_malloc_xref: %s %a - immediate!\n", name, push_malloc_size_addr);
			Malloc_calls.push_back(TFuncMalloc_call(xref_addr, CONSTVALUE, memory_size_var.value));

			//msg("analyze_malloc_xref: %s Malloc_call_list.size() = %d!\n", name, Malloc_calls.size());
			return;
		}

		//Allocation of var memory size


		//Allocation of var by register
		if(memory_size_var.type == o_reg){
			ea_t addr_of_src = find_instruction_that_changes_operand_backward_smart(push_malloc_size_addr, memory_size_var);
			msg("analyze_malloc_xref: %s %a - var!\n", name, push_malloc_size_addr);
			if(addr_of_src != BADADDR){
				type = assign_type(addr_of_src, &value);
				Malloc_calls.push_back(TFuncMalloc_call(xref_addr, type, value, addr_of_src));
			}
			else
				Malloc_calls.push_back(TFuncMalloc_call(xref_addr, UNDEFINED));

			msg("analyze_malloc_xref: %s Malloc_call_list.size() = %d!\n", name, Malloc_calls.size());

			return;
		}

		//Allocation of var by argument - new trampoline
		//TODO: better algo!
		if( (memory_size_var.type == o_displ) && (memory_size_var.reg == 5) && (memory_size_var.phrase == 5) && (memory_size_var.value == 0) && ( (int)memory_size_var.addr > 0) ){
			func_t *func = get_func(xref_addr);
			//too easy, how about mov ebp,esp call:malloc?
			if(func)

				get_short_name(BADADDR, func->startEA, buffer, MAXSTR);
				//get_long_name(BADADDR, func->startEA, buffer, MAXSTR);
				TFuncMallocWrapper new_malloc = TFuncMallocWrapper(buffer, name, memory_size_var.addr / sizeof(ea_t) - 1, func->startEA, WRAPPER);
				if(!does_exist(new_malloc))
					funcMalloc_wrappers.push_back(new_malloc);
				//funcMalloc.push_back(TFuncMalloc("here var name", memory_size_var.addr / sizeof(ea_t),func->startEA, WRAPPER));
			else{
				TFuncMallocWrapper new_malloc = TFuncMallocWrapper("new malloc", name, memory_size_var.addr / sizeof(ea_t) - 1, xref_addr, WRAPPER);//maybetter name malloc_at_%a?
				if(!does_exist(new_malloc))
					funcMalloc_wrappers.push_back(new_malloc);
					//funcMalloc.push_back(TFuncMalloc("here name of addr", memory_size_var.addr / sizeof(ea_t), xref_addr, WRAPPER));
			}

			return;

			msg("analyze_malloc_xref: %s Malloc_call_list.size() = %d!\n", name, Malloc_calls.size());

		}
		else{
			Malloc_calls.push_back(TFuncMalloc_call(xref_addr, VARVALUE));
		}
	}
	else{
		Malloc_calls.push_back(TFuncMalloc_call(xref_addr, UNDEFINED));
	}

	msg("analyze_malloc_xref: %s Malloc_call_list.size() = %d!\n", name, Malloc_calls.size());
}



void process_list_xref_ex(FILE* f, char *name, ea_t *list_addr, int size, int push_count)
{
	ea_t push_malloc_size_addr;
	op_t reg_var;
	func_t* func;
	char buffer[MAXSTR];
	for(int i = 0; i < size; i++){
		analyze_malloc_xref_ex(name, list_addr[i], push_count);
	}
}


void find_alloc_calls_ex(FILE* f, TFuncMalloc func)
{
	int size = 0;
	ea_t *list = find_function_xref(func.alloc_func_name, &size);
	if(size){
		process_list_xref_ex(f, func.alloc_func_name, list, size, func.push_malloc_size_count);
		qfree(list);
	}

}


void find_alloc_calls_warreps_ex(FILE* f, TFuncMallocWrapper func)
{
	int size = 0;
	ea_t *list = find_function_xref(func.address, &size);
	if(size){
		process_list_xref_ex(f, func.alloc_func_name, list, size, func.push_malloc_size_count);
		qfree(list);
	}

}



void pretty_printing_ex(FILE* f, TFuncMallocWrapper func)
{
	func_t *callee_func;
	char name_of_malloc_callee_function[MAXSTR];
	int func_name_set = 0;

	for(int i = 0; i < Malloc_calls.size(); i++){
		//qfprintf(f,"%s ----> %s xref: at %a \n", func.alloc_func_name, func.ancestor, Malloc_calls[i].address);
		qfprintf(f,"\r\n");
		callee_func = get_func(Malloc_calls[i].address);
		func_name_set = 0;

		if(callee_func){
			func_name_set = 1;
			get_short_name(BADADDR, callee_func->startEA, name_of_malloc_callee_function, MAXSTR);
			//generate_disasm_line(callee_func->startEA, name_of_malloc_callee_function, sizeof(name_of_malloc_callee_function));
			//tag_remove(name_of_malloc_callee_function, name_of_malloc_callee_function, sizeof(name_of_malloc_callee_function));
		}

		if(func_name_set)
			qfprintf(f,"%s argNumber = %d ----> %s xref: at %a %s\n", func.alloc_func_name, func.push_malloc_size_count, func.ancestor, Malloc_calls[i].address, name_of_malloc_callee_function);
		else
			qfprintf(f,"%s argNumber = %d ----> %s xref: at %a %s\n", func.alloc_func_name, func.push_malloc_size_count, func.ancestor, Malloc_calls[i].address, "CISSRT_undefined_function");
			//qfprintf(f,"%s xref: at %a %s\n", func.alloc_func_name, Malloc_calls[i].address, "CISSRT_undefined_function");


		if(Malloc_calls[i].type == CONSTVALUE){
			qfprintf(f,"Type: CONST = %d Malloc bytes\n", Malloc_calls[i].value);
		}
		else if(Malloc_calls[i].type == VARVALUE){
			char buf[MAXSTR];
			char instr_clean[MAXSTR];
			// Store the disassembled text in buf
			ua_ana0(Malloc_calls[i].address_of_last_size_object_modified);
			generate_disasm_line(cmd.ea, buf, sizeof(buf)-1);
			// This will appear as colour-tagged text (which will
			// be mostly unreadable in IDA's
			tag_remove(buf, instr_clean, sizeof(instr_clean)-1);
			if(Malloc_calls[i].address_of_last_size_object_modified != BADADDR)
				qfprintf(f,"Type: VAR, last modif at %a %s\n", Malloc_calls[i].address_of_last_size_object_modified, instr_clean);
			else
				qfprintf(f,"Type: VAR, last modif lost :(");
			//qfprintf(f,"last modif: %s\n", instr_clean);			
		}
		else if(Malloc_calls[i].type == VARVALUEVULN){
			char buf[MAXSTR];
			char instr_clean[MAXSTR];
			// Store the disassembled text in buf
			ua_ana0(Malloc_calls[i].address_of_last_size_object_modified);
			generate_disasm_line(cmd.ea, buf, sizeof(buf)-1);
			// This will appear as colour-tagged text (which will
			// be mostly unreadable in IDA's
			tag_remove(buf, instr_clean, sizeof(instr_clean)-1);
			//qfprintf(f,"get_first_operand disasm instruction: %s\n", instr_clean);
			if(Malloc_calls[i].address_of_last_size_object_modified != BADADDR)
				qfprintf(f,"Type: VAR, Possible Integer Overflow at %a %s\n", Malloc_calls[i].address_of_last_size_object_modified, instr_clean);
			else
				qfprintf(f,"Type: VAR, last modif lost :(");
		}
		else if(Malloc_calls[i].type == UNDEFINED){
			char buf[MAXSTR];
			char instr_clean[MAXSTR];
			// Store the disassembled text in buf
			ua_ana0(Malloc_calls[i].address_of_last_size_object_modified);
			generate_disasm_line(cmd.ea, buf, sizeof(buf)-1);
			// This will appear as colour-tagged text (which will
			// be mostly unreadable in IDA's
			tag_remove(buf, instr_clean, sizeof(instr_clean)-1);
			//qfprintf(f,"get_first_operand disasm instruction: %s\n", instr_clean);

			//qfprintf(f,"Type:var bytes, Possible Integer Overflow at %a %s\n", Malloc_calls[i].address_of_last_size_object_modified, instr_clean);
			if(Malloc_calls[i].address_of_last_size_object_modified != BADADDR)
				qfprintf(f,"Type: UNDEFINED, at %a %s", Malloc_calls[i].address_of_last_size_object_modified, instr_clean);//shouldnt be here
			else
				qfprintf(f,"Type: UNDEFINED, last modif lost :(");
		}
	}
}


void pretty_printing_ex(FILE* f, TFuncMalloc func)
{

	func_t *callee_func;
	char name_of_malloc_callee_function[MAXSTR];
	int func_name_set = 0;


	for(int i = 0; i < Malloc_calls.size(); i++){
		qfprintf(f,"\r\n");
		callee_func = get_func(Malloc_calls[i].address);
		func_name_set = 0;

		if(callee_func){
			func_name_set = 1;
			get_short_name(BADADDR, callee_func->startEA, name_of_malloc_callee_function, MAXSTR);
			//generate_disasm_line(callee_func->startEA, name_of_malloc_callee_function, sizeof(name_of_malloc_callee_function));
			//tag_remove(name_of_malloc_callee_function, name_of_malloc_callee_function, sizeof(name_of_malloc_callee_function));
		}

		if(func_name_set)
			qfprintf(f,"%s xref: at %a %s\n", func.alloc_func_name, Malloc_calls[i].address, name_of_malloc_callee_function);
		else
			qfprintf(f,"%s xref: at %a %s\n", func.alloc_func_name, Malloc_calls[i].address, "CISSRT_undefined_function");
		

		if(Malloc_calls[i].type == CONSTVALUE){
			qfprintf(f,"Type: CONST = %d Malloc bytes\n", Malloc_calls[i].value);
		}

		if(Malloc_calls[i].type == VARVALUE){
			char buffer[MAXSTR];
			//char instr_clean[MAXSTR];
			// Store the disassembled text in buf
			ua_ana0(Malloc_calls[i].address_of_last_size_object_modified);

			generate_disasm_line(cmd.ea, buffer, sizeof(buffer));
			tag_remove(buffer, buffer, sizeof(buffer));

			if(Malloc_calls[i].address_of_last_size_object_modified != BADADDR)
				qfprintf(f,"Type: VAR, last modif at %a %s\n", Malloc_calls[i].address_of_last_size_object_modified, buffer);
			else
				qfprintf(f,"Type: VAR, last modif lost :( \n");
			//qfprintf(f,"last modif: \n", instr_clean);			
		}

		if(Malloc_calls[i].type == VARVALUEVULN){
			char buffer[MAXSTR];
			//char instr_clean[MAXSTR];
			// Store the disassembled text in buf
			ua_ana0(Malloc_calls[i].address_of_last_size_object_modified);

			generate_disasm_line(cmd.ea, buffer, sizeof(buffer));
			tag_remove(buffer, buffer, sizeof(buffer));

			//qfprintf(f,"get_first_operand disasm instruction: %s\n", instr_clean);
			if(Malloc_calls[i].address_of_last_size_object_modified != BADADDR)
				qfprintf(f,"Type: VAR, Possible Integer Overflow %a %s\n", Malloc_calls[i].address_of_last_size_object_modified, buffer);
			else
				qfprintf(f,"Type: VAR, last modif lost :( \n");//shouldnt be here
		}

		if(Malloc_calls[i].type == UNDEFINED){
			char buffer[MAXSTR];
			// Store the disassembled text in buf
			ua_ana0(Malloc_calls[i].address_of_last_size_object_modified);

			generate_disasm_line(cmd.ea, buffer, sizeof(buffer));
			tag_remove(buffer, buffer, sizeof(buffer));

			//qfprintf(f,"get_first_operand disasm instruction: %s\n", instr_clean);
			if(Malloc_calls[i].address_of_last_size_object_modified != BADADDR)
				qfprintf(f,"Type: UNDEFINED, at %a %s", Malloc_calls[i].address_of_last_size_object_modified, buffer);//shouldnt be here
			else
				qfprintf(f,"Type: UNDEFINED, last modif lost :(");
		}
	}

}

void IDAP_run(int arg)
{
	FILE *f, *f2;
	char *filename = construct_output_filename(".import_allocs.txt");
	f = qfopen(filename, "wb");
	char *filename2 = construct_output_filename(".import_allocs_wrappers.txt");
	f2 = qfopen(filename2, "wb");

	//r0 allocators
	funcMalloc.push_back(TFuncMalloc(" ExAllocatePoolWithQuota", 2));
	funcMalloc.push_back(TFuncMalloc(" __imp__ExAllocatePoolWithQuota@8", 2));//ntoskrnl.exe

	funcMalloc.push_back(TFuncMalloc(" ExAllocatePoolWithQuotaTag", 2));
	funcMalloc.push_back(TFuncMalloc(" __imp__ExAllocatePoolWithQuotaTag@12", 2));//ntoskrnl.exe

	funcMalloc.push_back(TFuncMalloc("ExAllocatePoolWithTag", 2));
	funcMalloc.push_back(TFuncMalloc("__imp__ExAllocatePoolWithTag@12", 2));//ntoskrnl.exe

	funcMalloc.push_back(TFuncMalloc("ExAllocatePoolWithTagPriority", 2));
	funcMalloc.push_back(TFuncMalloc("__imp__ExAllocatePoolWithTagPriority@16", 2));//ntoskrnl.exe

	funcMalloc.push_back(TFuncMalloc("IoAllocateMdl", 2));
	funcMalloc.push_back(TFuncMalloc("__imp__IoAllocateMdl@20", 2));//ntoskrnl.exe

	funcMalloc.push_back(TFuncMalloc("RtlAllocateHeap", 3));
	funcMalloc.push_back(TFuncMalloc("__imp__RtlAllocateHeap", 3));//ntoskrnl.exe

	funcMalloc.push_back(TFuncMalloc("EngAllocMem", 2));
	funcMalloc.push_back(TFuncMalloc("__imp__EngAllocMem", 2));//win32k.sys
	funcMalloc.push_back(TFuncMalloc("__imp__EngAllocMem@12", 2));//win32k.sys


	//type pointer to size!!!
	//funcMalloc.push_back(TFuncMalloc("ZwAllocateVirtualMemory", 4));
	//funcMalloc.push_back(TFuncMalloc("__imp__ZwAllocateVirtualMemory@24", 4));//ntoskrnl.exe
	//funcMalloc.push_back(TFuncMalloc("NtAllocateVirtualMemory", 4));
	//funcMalloc.push_back(TFuncMalloc("__imp__NtAllocateVirtualMemory@24", 4));//ntoskrnl.exe



	//funcMalloc.push_back(TFuncMalloc("RtlReAllocateHeap", 4));
	//funcMalloc.push_back(TFuncMalloc("HeapAlloc", 3));



	//r3 allocators
	funcMalloc.push_back(TFuncMalloc("GlobalAlloc", 2));//kernel32.dll

	funcMalloc.push_back(TFuncMalloc("HeapAlloc", 3));//kernel32.dll
	funcMalloc.push_back(TFuncMalloc("__imp__HeapAlloc@12", 3));//kernel32.dll

	funcMalloc.push_back(TFuncMalloc("__imp__HeapReAlloc@16", 4));//kernel32.dll
	funcMalloc.push_back(TFuncMalloc("HeapReAlloc", 4));//kernel32.dll

	funcMalloc.push_back(TFuncMalloc("__imp__LocalAlloc@8", 2));//kernel32.dll
	funcMalloc.push_back(TFuncMalloc("LocalAlloc", 2));//kernel32.dll

	funcMalloc.push_back(TFuncMalloc("__imp__LocalReAlloc@12", 3));//kernel32.dll
	funcMalloc.push_back(TFuncMalloc("LocalReAlloc", 3));//kernel32.dll

	funcMalloc.push_back(TFuncMalloc("VirtualAlloc", 2));
	funcMalloc.push_back(TFuncMalloc("__imp__VirtualAlloc@16", 2));//kernel32.dll

	funcMalloc.push_back(TFuncMalloc("__imp__MpHeapAlloc", 3));//msdart.dll export
	funcMalloc.push_back(TFuncMalloc("__imp__MpHeapReAlloc", 3));//msdart.dll export

	funcMalloc.push_back(TFuncMalloc("__imp__GdipAlloc@4", 1));//gdiplus.dll export
	//funcMalloc.push_back(TFuncMalloc("GpMalloc", 1));//gdiplus.dll

	funcMalloc.push_back(TFuncMalloc("__imp__malloc", 1));//msvcrt.dll
	funcMalloc.push_back(TFuncMalloc("_malloc", 1));//msvcrt.dll, the same as __imp__malloc

	funcMalloc.push_back(TFuncMalloc("__imp__realloc", 2));//msvcrt.dll
	funcMalloc.push_back(TFuncMalloc("_realloc", 2));//msvcrt.dll

	//funcMalloc.push_back(TFuncMalloc("_alloca", 1));
	//funcMalloc.push_back(TFuncMalloc("_malloca", 1));



	uint i = 0, j = funcMalloc.size();
	msg("standart funcMalloc.size() = %d\n", funcMalloc.size());
	for(; i< funcMalloc.size(); i++){
		find_alloc_calls_ex(f, funcMalloc[i]);
		pretty_printing_ex(f, funcMalloc[i]);

		if(Malloc_calls.size() >  0 )
			Malloc_calls.clear();
		
		qfprintf(f,"\n\n");

		qflush( f );
	}

	qfclose( f );

	
	j = funcMalloc_wrappers.size();
	msg("standart funcMalloc_wrappers.size() = %d\n", j);

	
	//TODO: add level property 
	i = 0;
	while( i < j){

		find_alloc_calls_warreps_ex(f2, funcMalloc_wrappers[i]);
		msg("[%d].funcMalloc.size() = %d\n", i, funcMalloc_wrappers.size());
		msg("[%d].Malloc_calls.size() = %d\n", i, Malloc_calls.size());
		pretty_printing_ex(f2, funcMalloc_wrappers[i]);
		if(Malloc_calls.size() >  0 )
			Malloc_calls.clear();
		j = funcMalloc_wrappers.size();
		i++;
		qflush( f2 );
	}
	


	qfclose( f2 );


	return ;
}



char IDAP_comment[] = "Find Alloc";
char IDAP_help[] = "Find Alloc\n";


char IDAP_name[] = "Find Alloc";
char IDAP_hotkey[] = "";

plugin_t PLUGIN =
{
  IDP_INTERFACE_VERSION,
  0,
  IDAP_init,
  IDAP_term,
  IDAP_run,
  IDAP_comment,
  IDAP_help,
  IDAP_name,
  IDAP_hotkey
};