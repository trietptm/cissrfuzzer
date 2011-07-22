/* htmlcollection_s for new htmlcollection_s */
/* Create new empty htmlcollection_s */
function htmlcollection_() {
	this.name =  "HTMLCollection";
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
htmlcollection_.prototype.add_sleep_object = function(this_type, this_name)
{
	this.dynamic == true;
	this.dynamic_name.push(this_name);
	this.dynamic_type.push(this_type);
};
/* Generate "HTMLCollection" */
htmlcollection_.prototype.generate = function () {
	this.add_attribute ("length", "unsignedlong");	
	this.add_functions ("item", ["unsignedlong"], ["index"]);	
	this.add_functions ("namedItem", ["DOMString"], ["name"]);
};
/* Add name */
htmlcollection_.prototype.init_name = function (name_parameter) {
	this.name = name_parameter;
};
/* Add attributes */
htmlcollection_.prototype.add_attribute = function (name_attribute, type_attribute) 
{
	var new_htmlcollection_ = new attr;
	new_htmlcollection_.add(name_attribute, type_attribute);
	this.all_atrib.push(new_htmlcollection_);
};
/* Add attribute-function */
htmlcollection_.prototype.add_attribute_function = function (name_attribute) 
{
	var new_htmlcollection_ = new attr_func;
	new_htmlcollection_.add(name_attribute);
	this.all_atr_func.push(new_htmlcollection_);
};
/* Add functions(methods) */
htmlcollection_.prototype.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = new func;
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
/* Add object */
htmlcollection_.prototype.add_object = function (name_object)
{
	var new_htmlcollection_ = new htmlcollection_;
	new_htmlcollection_.init_name(name_object);
	this.all_object[this.num_object] = new_htmlcollection_;
	this.num_object ++;
}
/* not use
htmlcollection_.prototype.add_object = function (type_object)
{
	var new_htmlcollection_ = new htmlcollection_;
	if (type_object == "htmlcollection_") 
	{
	new_htmlcollection_ = new htmlcollection_;
	}
	
	new_htmlcollection_.init_name(name_object);
	this.all_object[this.num_object] = new_htmlcollection_;
	this.num_object ++;
}
*/
/* Return name of htmlcollection_s */
htmlcollection_.prototype.ret_name = function () {
	return this.name;
}
/* Return attributes */
htmlcollection_.prototype.get_attribute = function () {
	var result = [];
	for(var i = 0; i < this.all_atrib.length; i++ )
	{
		result.push(this.all_atrib[i].ret_str());
	}
	return result;
}
/* Return functions */
htmlcollection_.prototype.get_function = function () {
	var result = [];
	for(var i = 0; i < this.num_func; i++ )
	{
		result.push(this.all_func[i].ret_str());
	}
	return result;
}
htmlcollection_.prototype.return_clas = function (name){
	var return_;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_ = this.all_object[j];
	}
	return return_;
}
htmlcollection_.prototype.return_i_clas = function (name){
	var return_i;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_i = j;
	}
	return return_i;
}