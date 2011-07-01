/*********************************************************************
* Find memcpy() IDA Pro plugin
*
* Copyright (c) 2008 Luis Miras
* Licensed under the BSD License
*
* Requirements: The plugin requires x86 processor.
*
* Description: The plugin searches for rep movsd/rep movsb
*              pairs identidying them as memcpy()
*              Single rep movsd and rep movsb instructions
*              are also recorded
*
* Data structures: a netnode is the main data structure.
*                  movsobj_t represents the either pairs
*                  or single instructions.
*
* netnodes are implemented internally as B-trees.
* IDA uses netnodes extensively for its own storage.
* netnodes are defined in netnode.hpp.
*
* netnodes in the plugin: calls - holds all indirect calls
*                         vtable - holds all vtables
*
* netnodes have various internal data structures.
* The plugin uses 2 types of arrays:
*    altval -  a sparce array of 32 bit values, initially set to 0.
*    supval -  an array of variable sized objects (MAXSPECSIZE)
*
* The plugin holds base addresses in altval and movsobj_t objects
* in supval
*********************************************************************/

#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <allins.hpp>
#include <intel.hpp>

#define NODE_COUNT -1

struct movsObj {
   ea_t movsDW; // addr of rep movsd. BADADDR if none
   ea_t movsBT; // addr of rep movsd. BADADDR if none
};

typedef movsObj movsobj_t;

static const char* header[] = {"Address", "Type", "Movsd/b distance", "Function"};
static const int widths[] = { 16, 25, 25, 55};
char window_title[] = "Inline memcpy" ;

/*********************************************************************
* Function: processMemcpy
*
* This function determines the types of memcpy based on the movsobj_t
* and calculates distance between rep movsd and rep movsb
*********************************************************************/
char* processMemcpy(movsobj_t* my_movs, ea_t* movs_distance)
{
   if (my_movs->movsDW == BADADDR)
   {
      *movs_distance = BADADDR;
      return "memcpy movsb only";
   }
   else if (my_movs-> movsBT == BADADDR)
   {
      *movs_distance = BADADDR;
      return "memcpy movsd only";
   }
   else
   {
      *movs_distance = my_movs-> movsBT - my_movs->movsDW;
      return "memcpy()";
   }
}

ea_t get_addr(movsobj_t* my_movs)
{
   if (my_movs->movsDW == BADADDR)
   {
      return my_movs-> movsBT;
   }
   else if (my_movs-> movsBT == BADADDR)
   {
      return my_movs->movsDW;
   }
   return BADADDR;
}

char* constrcut_output_filename(char *prefix)
{
	char result[MAXSTR];
	get_root_filename(result, MAXSTR);
	qstrncat(result, prefix, MAXSTR);
	return result;
}

long getobjcount(netnode* node)
{
    return node->altval(NODE_COUNT) - 1;
}

void idaapi mine_pretty_printing(netnode* calls)
{
    //netnode* node = (netnode* )obj;
	netnode* node = calls;
   movsobj_t my_movs;
	int n = 1;
	char arrptr_0[MAXSTR],arrptr_1[MAXSTR],arrptr_2[MAXSTR],arrptr_3[MAXSTR];
	FILE *f;
	//char filename[] = "indirect.txt";
	char *filename = constrcut_output_filename(".inline_memcpy.txt");
	f = qfopen(filename, "wb");
	/*
    if (n == 0) // sets up headers
    {
        for ( int i = 0; i < qnumber(icHeader); i++ )
            qstrncpy(arrptr[i], icHeader[i], MAXSTR);
        return;
    }
	*/
    // list empty?
    //if (!getobjcount(node))
    //    return;
	n = getobjcount(node);
	msg("object count = %d\n", n);
	for(int i = 1; i <= n;i++){
		char buffer[MAXSTR];
		   char* outstring = NULL;
		   ea_t movs_distance;
				node->supval(i, &my_movs, sizeof(my_movs));
		   func_t* currFunc = get_func(node->altval(i));

		   outstring = processMemcpy(&my_movs, &movs_distance);
		   qsnprintf(arrptr_0, MAXSTR, "%08a", node->altval(i));

			if(currFunc){
				get_short_name(BADADDR, currFunc->startEA, buffer, MAXSTR);
				qsnprintf(arrptr_1, MAXSTR, "%s", buffer);
			}
			else qsnprintf(arrptr_1, MAXSTR, "no function");	

		   qsnprintf(arrptr_2, MAXSTR, "%s", outstring);

		   if (movs_distance != BADADDR)
		   {
			  qsnprintf(arrptr_3, MAXSTR, "%02x", movs_distance);
		   }
		   else
			  qsnprintf(arrptr_3, MAXSTR, "");
		
		//msg("%s %s %s %s\n", arrptr_0, arrptr_1, arrptr_2, arrptr_3);
		//msg("%d\n", i);
		qfprintf(f, "%s %s %s %s\n", arrptr_0, arrptr_1, arrptr_2, arrptr_3);
		if((i%1000) == 0)qflush(f);
	}
	qfclose( f );
    return;
}

/*********************************************************************
* Function: description
*
* This is a standard callback in the choose2() SDK call. This function
* fills in all column content for a specific line. Headers names are
* set during the first call to this function, when n == 0.
* arrptr is a char* array to the column content for a line.
*                 arrptr[number of columns]
*
* description creates 3 columns based on the header array
*********************************************************************/
void idaapi description(void *obj,ulong n,char * const *arrptr)
{
   netnode *node = (netnode *)obj;
   movsobj_t my_movs;
   char* outstring = NULL;
   ea_t movs_distance;

   if ( n == 0 ) // sets up headers
   {
      for ( int i=0; i < qnumber(header); i++ )
         qstrncpy(arrptr[i], header[i], MAXSTR);
      return;
   }

   // list empty?
   if (!node->altval(NODE_COUNT))
      return;

   node->supval(n-1, &my_movs,sizeof(my_movs));
   outstring = processMemcpy(&my_movs, &movs_distance);
   qsnprintf(arrptr[0], MAXSTR, "%08a", node->altval(n-1));
   qsnprintf(arrptr[1], MAXSTR, "%s", outstring);

   if (movs_distance != BADADDR)
   {
      qsnprintf(arrptr[2], MAXSTR, "%02x", movs_distance);
   }
   else
   {
      qsnprintf(arrptr[2], MAXSTR, "");
   }
   func_t* currFunc = get_func(node->altval(n-1));
	char buffer[MAXSTR];
	if(currFunc){
		get_short_name(BADADDR, currFunc->startEA, buffer, MAXSTR);
		qsnprintf(arrptr[3], MAXSTR, "%s", buffer);
	}
	else qsnprintf(arrptr[3], MAXSTR, "no function");

   return;
}

/*********************************************************************
* Function: enter
*
* This is a standard callback in the choose2() SDK call. This function
* is called when the user pressed Enter or Double-Clicks on a line in
* the chooser list.
*********************************************************************/
void idaapi enter(void * obj,ulong n)
{
   ea_t addr;
   netnode *node = (netnode *)obj;
   addr = node->altval(n-1);
   jumpto(addr);
   return;
}

/*********************************************************************
* Function: destroy
*
* This is a standard callback in the choose2() SDK call. This function
* is called when the chooser list is being destroyed. Resource cleanup
* is common in this function. The netnode deleted here.
*********************************************************************/
void idaapi destroy(void* obj)
{
   netnode *node = (netnode *)obj;
   node->kill();
   return;
}

/*********************************************************************
* Function: size
*
* This is a standard callback in the choose2() SDK call. This function
* returns the number of lines to be used in the chooser list.
*********************************************************************/
ulong idaapi size(void* obj)
{
   ulong mysize;
   netnode *node = (netnode *)obj;
   mysize = node->altval(NODE_COUNT);
   return mysize;
}

/*********************************************************************
* Function: functionSearch
*
* functionSearch looks through functions for rep movsd and rep movsb
* memcpy is defined as a rep movsd followed by rep movsb
* single rep movsd and movsb are also recorded
*
* last_movs is used to track for rep movsd/rep movsb sets
* the netnode's alval and supval arrays are used
* node->alset contains the base address
* node->supset contains a movsobj_t object
*
*
* memcpy() == movsobj_t with {addr, addr}
* mosvd only == movsobj_t with {addr, BADADDR}
* movsb only == movsobj_t with {BADADDR, addr}
*
* NOTE: this function misses rep movw (66 F3 A5) instructions
*********************************************************************/
void functionSearch(func_t* funcAddr, netnode* node)
{
   movsobj_t my_movs;
   int counter = node->altval(NODE_COUNT);
   ea_t last_movs = BADADDR;
   ea_t addr = funcAddr->startEA;

   while (addr != BADADDR)
   {
      flags_t flags = getFlags(addr);
      if (isHead(flags) && isCode(flags))
      {
         // fill cmd, only looking for 2 byte instructions
         if (ua_ana0(addr) == 2)
         {
            if ((cmd.auxpref & aux_rep) && (cmd.itype == NN_movs))
            {
               if (cmd.Operands[1].dtyp == dt_dword) // rep movsd
               {
                  if (last_movs != BADADDR)
                  {
                     // two consecutive rep movsd
                     // set the previous one to movsd only
                     my_movs. movsDW = last_movs;
                     my_movs. movsBT = BADADDR;
                     node->altset(counter, last_movs);
                     node->supset(counter++, &my_movs,sizeof(my_movs));
                  }
                  // found a rep movsd waiting for rep movsb
                  last_movs = cmd.ea;
               }
               else if (cmd.Operands[1].dtyp == dt_byte) // rep movsb
               {
                  if (last_movs == BADADDR)
                  {
                     // rep movsb with no preceding rep movsd
                     my_movs. movsDW = BADADDR;
                     my_movs. movsBT = cmd.ea;
                     node->altset(counter, cmd.ea);
                     node->supset(counter++,&my_movs,sizeof(my_movs));
                  }
                  else  // memcpy()
                  {
                     // complete set rep movsd/rep movsb
                     my_movs. movsDW = last_movs;
                     my_movs. movsBT = cmd.ea;
                     node->altset(counter, last_movs);
                     node->supset(counter++, &my_movs,sizeof(my_movs));
                  }
                  last_movs = BADADDR;
               }
               else
               {
                  msg("%x: rep", addr);
                  msg("ERROR !!!\n");
               }
            }
         }
      }
      addr = next_head(addr, funcAddr->endEA);
   }

   if (last_movs != BADADDR)
   {
      // a remaining single rep movsd
      my_movs. movsDW = last_movs;
      my_movs. movsBT = BADADDR;
      node->altset(counter, last_movs);
      node->supset(counter++, &my_movs, sizeof(my_movs));
   }
   node->altset(NODE_COUNT, counter);
   return;
}

/*********************************************************************
* Function: collectData
*
* This function iterates through all functions calling functionSearch
*********************************************************************/
void collectData(netnode* node)
{
   for (uint i = 0; i < get_func_qty(); ++i)
   {
      func_t *f = getn_func(i);
      functionSearch(f, node);
   }
   return;
}

/********************************************************************
* Function: init
*
* init is a plugin_t function. It is executed when the plugin is
* initially loaded by IDA
********************************************************************/
int init(void)
{
   // plugin only works for x86 executables
   if (ph.id != PLFM_386)
      return PLUGIN_SKIP;
   return PLUGIN_OK;
}

/*********************************************************************
* Function: term
*
* term is a plugin_t function. It is executed when the plugin is
* unloading. Typically cleanup code is executed here.
* The window is closed to remove the choose2() callbacks
*********************************************************************/
void term(void)
{
   close_chooser(window_title);
   return;
}

/*********************************************************************
* Function: run
*
* run is a plugin_t function. It is executed when the plugin is run.
* This function collects data and and displays results
*
*   arg - defaults to 0. It can be set by a plugins.cfg entry. In this
*         case the arg is used for debugging/development purposes
* ;plugin displayed name    filename        hotkey    arg
* find_memcpy               findMemcpy     Ctrl-F12   0
* find_memcpy_unload        findMemcpy     Shift-F12  415
*
* Thus Shift-F12 runs the plugin with an option that will unload it.
* This allows (edit/recompile/copy) cycles.
*********************************************************************/
void run(int arg)
{
   char node_name[] = "$ inline memcpy";

   if(arg == 415)
   {
      PLUGIN.flags |= PLUGIN_UNL;
      msg("Unloading plugin...\n");
      return;
   }

   netnode* node = new netnode;
   if(close_chooser(window_title))
   {
      //window existed and is now closed
      msg("window existed and is now closed\n");
   }
   if (node->create(node_name) == 0)
   {
      msg("ERROR: creating netnode %\n", node_name);
      return;
   }
   // set netnode count to 0
   node->altset(NODE_COUNT, 0);

   // look for memcpys
   collectData(node);
mine_pretty_printing(node);
	

   // create chooser list box
   choose2(false,      // non-modal window
      -1, -1, -1, -1,  // position is determined by Windows
      node,            // object to show
      qnumber(header), // number of columns
      widths,          // widths of columns
      size,            // function that returns number of lines
      description,     // function that generates a line
      window_title,    // window title
      -1,              // use the default icon for the window
      0,               // position the cursor on the first line
      NULL,            // "kill" callback
      NULL,            // "new" callback
      NULL,            // "update" callback
      NULL,            // "edit" callback
      enter,           // function to call when the user pressed Enter
      destroy,         // function to call when the window is closed
      NULL,            // use default popup menu items
      NULL);           // use the same icon for all line

   return;
}

char comment[] = "findMemcpy - finds inline memcpy";
char help[]    = "findMemcpy\n"
                  "This plugin looks through all functions\n"
                  "for inline memcpy\n";
char wanted_name[] = "findMemcpy";
char wanted_hotkey[] = "";

/* defines the plugins interface to IDA */
plugin_t PLUGIN =
{
   IDP_INTERFACE_VERSION,
   0,              // plugin flags
   init,           // initialize
   term,           // terminate. this pointer may be NULL.
   run,            // invoke plugin
   comment,        // comment about the plugin
   help,           // multiline help about the plugin
   wanted_name,    // the preferred short name of the plugin
   wanted_hotkey   // the preferred hotkey to run the plugin
};
