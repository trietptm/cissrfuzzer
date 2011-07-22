/* location_s for new location_s */
/* Create new empty location_s */
function location_() {
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
location_.prototype.add_sleep_object = function(this_type, this_name)
{
	this.dynamic == true;
	this.dynamic_name.push(this_name);
	this.dynamic_type.push(this_type);
};
/* Generate "Location" */
location_.prototype.generate = function () {
	this.add_attribute ("href", "DOMString"); 		
	this.add_attribute ("protocol", "DOMString"); 		
	this.add_attribute ("host", "DOMString"); 		
	this.add_attribute ("hostname", "DOMString"); 		
	this.add_attribute ("port", "DOMString"); 		
	this.add_attribute ("pathname", "DOMString"); 		
	this.add_attribute ("search", "DOMString"); 		
	this.add_attribute ("hash", "DOMString"); 		
	this.add_functions ("assign", ["DOMString"], ["url"]);
	this.add_functions ("replace", ["DOMString"], ["url"]);	
	this.add_functions ("reload", [""], [""]);	
	this.add_functions ("resolveURL", [""], [""]);			
};
/* Add name */
location_.prototype.init_name = function (name_parameter) {
	this.name = name_parameter;
};
/* Add attributes */
location_.prototype.add_attribute = function (name_attribute, type_attribute) 
{
	var new_location_ = new attr;
	new_location_.add(name_attribute, type_attribute);
	this.all_atrib.push(new_location_);
};
/* Add attribute-function */
location_.prototype.add_attribute_function = function (name_attribute) 
{
	var new_location_ = new attr_func;
	new_location_.add(name_attribute);
	this.all_atr_func.push(new_location_);
};
/* Add functions(methods) */
location_.prototype.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = new func;
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
/* Add object */
location_.prototype.add_object = function (name_object)
{
	var new_location_ = new location_;
	new_location_.init_name(name_object);
	this.all_object[this.num_object] = new_location_;
	this.num_object ++;
}
/* not use
location_.prototype.add_object = function (type_object)
{
	var new_location_ = new location_;
	if (type_object == "location_") 
	{
	new_location_ = new location_;
	}
	
	new_location_.init_name(name_object);
	this.all_object[this.num_object] = new_location_;
	this.num_object ++;
}
*/
/* Return name of location_s */
location_.prototype.ret_name = function () {
	return this.name;
}
/* Return attributes */
location_.prototype.get_attribute = function () {
	var result = [];
	for(var i = 0; i < this.all_atrib.length; i++ )
	{
		result.push(this.all_atrib[i].ret_str());
	}
	return result;
}
/* Return functions */
location_.prototype.get_function = function () {
	var result = [];
	for(var i = 0; i < this.num_func; i++ )
	{
		result.push(this.all_func[i].ret_str());
	}
	return result;
}
location_.prototype.return_clas = function (name){
	var return_;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_ = this.all_object[j];
	}
	return return_;
}
location_.prototype.return_i_clas = function (name){
	var return_i;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_i = j;
	}
	return return_i;
}