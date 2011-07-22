/* nodelist_s for new nodelist_s */
/* Create new empty nodelist_s */
function nodelist_() {
	this.name = "document";
	this.all_func = [];
	this.num_func = 0;
	this.all_atrib = [];
	this.all_atr_func = [];	
	this.all_object = [];
	this.num_object = 0;
	this.dynamic = false;
	this.dynamic_name = [];
	this.dynamic_type = [];
};
/* add dynamic object in "sleep" array  */
nodelist_.prototype.add_sleep_object = function(this_type, this_name)
{
	this.dynamic == true;
	this.dynamic_name.push(this_name);
	this.dynamic_type.push(this_type);
};
/* Generate "document" */
nodelist_.prototype.generate = function () {
	this.add_attribute("length", "unsignedlong");
	this.add_functions ("item", ["unsignedlong"], ["index"]);
};
/* Add name */
nodelist_.prototype.init_name = function (name_parameter) {
	this.name = name_parameter;
};
/* Add attributes */
nodelist_.prototype.add_attribute = function (name_attribute, type_attribute) 
{
	var new_nodelist_ = new attr;
	new_nodelist_.add(name_attribute, type_attribute);
	this.all_atrib.push(new_nodelist_);
};
/* Add attribute-function */
nodelist_.prototype.add_attribute_function = function (name_attribute) 
{
	var new_nodelist_ = new attr_func;
	new_nodelist_.add(name_attribute);
	this.all_atr_func.push(new_nodelist_);
};
/* Add functions(methods) */
nodelist_.prototype.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = new func;
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
/* Add object */
nodelist_.prototype.add_object = function (name_object)
{
	var new_nodelist_ = new nodelist_;
	new_nodelist_.init_name(name_object);
	this.all_object[this.num_object] = new_nodelist_;
	this.num_object ++;
}
nodelist_.prototype.add_object_type = function (type_object, name_object)
{
	var new_clas = new clas;
	if (type_object == "Document") 
	{
		new_clas = new document_;
		new_clas.init_name(name_object);
		new_clas.generate();
	}
	if (type_object == "HTMLCollection") 
	{
		new_clas = new htmlcollection_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}
	if (type_object == "Location") 
	{
		new_clas = new location_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}	
	if (type_object == "HTMLElement") 
	{
		new_clas = new htmlelement_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}		
	if (type_object == "HTMLHeadElement") 
	{
		new_clas = new htmlheadelement_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}		

	this.all_object[this.num_object] = new_clas;
	this.num_object ++;
}
/* Return name of nodelist_s */
nodelist_.prototype.ret_name = function () {
	return this.name;
}
/* Return attributes */
nodelist_.prototype.get_attribute = function () {
	var result = [];
	for(var i = 0; i < this.all_atrib.length; i++ )
	{
		result.push(this.all_atrib[i].ret_str());
	}
	return result;
}
/* Return functions */
nodelist_.prototype.get_function = function () {
	var result = [];
	for(var i = 0; i < this.num_func; i++ )
	{
		result.push(this.all_func[i].ret_str());
	}
	return result;
}
nodelist_.prototype.return_clas = function (name){
	var return_;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_ = this.all_object[j];
	}
	return return_;
}
nodelist_.prototype.return_i_clas = function (name){
	var return_i;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_i = j;
	}
	return return_i;
}