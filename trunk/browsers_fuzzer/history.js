/* history_s for new history_s */
/* Create new empty history_s */
function history_() {
	this.name =  "";
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
history_.prototype.add_sleep_object = function(this_type, this_name)
{
	this.dynamic == true;
	this.dynamic_name.push(this_name);
	this.dynamic_type.push(this_type);
};
/* Generate "History" */
history_.prototype.generate = function () {
	this.add_attribute ("length", "long"); 
	this.add_attribute ("state", "any"); 
	this.add_functions ("go", [""], [""]);
	this.add_functions ("back", [""], [""]);
	this.add_functions ("forward", [""], [""]);
	this.add_functions ("pushState", ["any", "DOMString", "DOMString"], ["data", "title", "url"]);
	this.add_functions ("replaceState", ["any", "DOMString", "DOMString"], ["data", "title", "url"]);	
};
/* Add name */
history_.prototype.init_name = function (name_parameter) {
	this.name = name_parameter;
};
/* Add attributes */
history_.prototype.add_attribute = function (name_attribute, type_attribute) 
{
	var new_history_ = new attr;
	new_history_.add(name_attribute, type_attribute);
	this.all_atrib.push(new_history_);
};
/* Add attribute-function */
history_.prototype.add_attribute_function = function (name_attribute) 
{
	var new_history_ = new attr_func;
	new_history_.add(name_attribute);
	this.all_atr_func.push(new_history_);
};
/* Add functions(methods) */
history_.prototype.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = new func;
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
/* Add object */
history_.prototype.add_object = function (name_object)
{
	var new_history_ = new history_;
	new_history_.init_name(name_object);
	this.all_object[this.num_object] = new_history_;
	this.num_object ++;
}
/* not use
history_.prototype.add_object = function (type_object)
{
	var new_history_ = new history_;
	if (type_object == "history_") 
	{
	new_history_ = new history_;
	}
	
	new_history_.init_name(name_object);
	this.all_object[this.num_object] = new_history_;
	this.num_object ++;
}
*/
/* Return name of history_s */
history_.prototype.ret_name = function () {
	return this.name;
}
/* Return attributes */
history_.prototype.get_attribute = function () {
	var result = [];
	for(var i = 0; i < this.all_atrib.length; i++ )
	{
		result.push(this.all_atrib[i].ret_str());
	}
	return result;
}
/* Return functions */
history_.prototype.get_function = function () {
	var result = [];
	for(var i = 0; i < this.num_func; i++ )
	{
		result.push(this.all_func[i].ret_str());
	}
	return result;
}
history_.prototype.return_clas = function (name){
	var return_;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_ = this.all_object[j];
	}
	return return_;
}
history_.prototype.return_i_clas = function (name){
	var return_i;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_i = j;
	}
	return return_i;
}