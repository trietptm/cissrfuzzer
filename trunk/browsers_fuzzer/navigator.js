/* navigator_s for new navigator_s */
/* Create new empty navigator_s */
function navigator_() {
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
navigator_.prototype.add_sleep_object = function(this_type, this_name)
{
	this.dynamic == true;
	this.dynamic_name.push(this_name);
	this.dynamic_type.push(this_type);
};
/* Generate "Navigator" */
navigator_.prototype.generate = function () {
	this.add_attribute ("appVersion", "DOMString"); 	
	this.add_attribute ("appName", "DOMString"); 	
	this.add_attribute ("platform", "DOMString"); 	
	this.add_attribute ("userAgent", "DOMString"); 	
	this.add_attribute ("onLine", "boolean"); 	
	this.add_functions ("registerProtocolHandler", ["DOMString", "DOMString", "DOMString"], ["scheme", "url", "title"]);		
	this.add_functions ("registerContentHandler", ["DOMString", "DOMString", "DOMString"], ["mimeType", "url", "title"]);		
	this.add_functions ("yieldForStorageUpdates", [""], [""]);	
};
/* Add name */
navigator_.prototype.init_name = function (name_parameter) {
	this.name = name_parameter;
};
/* Add attributes */
navigator_.prototype.add_attribute = function (name_attribute, type_attribute) 
{
	var new_navigator_ = new attr;
	new_navigator_.add(name_attribute, type_attribute);
	this.all_atrib.push(new_navigator_);
};
/* Add attribute-function */
navigator_.prototype.add_attribute_function = function (name_attribute) 
{
	var new_navigator_ = new attr_func;
	new_navigator_.add(name_attribute);
	this.all_atr_func.push(new_navigator_);
};
/* Add functions(methods) */
navigator_.prototype.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = new func;
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
/* Add object */
navigator_.prototype.add_object = function (name_object)
{
	var new_navigator_ = new navigator_;
	new_navigator_.init_name(name_object);
	this.all_object[this.num_object] = new_navigator_;
	this.num_object ++;
}
/* not use
navigator_.prototype.add_object = function (type_object)
{
	var new_navigator_ = new navigator_;
	if (type_object == "navigator_") 
	{
	new_navigator_ = new navigator_;
	}
	
	new_navigator_.init_name(name_object);
	this.all_object[this.num_object] = new_navigator_;
	this.num_object ++;
}
*/
/* Return name of navigator_s */
navigator_.prototype.ret_name = function () {
	return this.name;
}
/* Return attributes */
navigator_.prototype.get_attribute = function () {
	var result = [];
	for(var i = 0; i < this.all_atrib.length; i++ )
	{
		result.push(this.all_atrib[i].ret_str());
	}
	return result;
}
/* Return functions */
navigator_.prototype.get_function = function () {
	var result = [];
	for(var i = 0; i < this.num_func; i++ )
	{
		result.push(this.all_func[i].ret_str());
	}
	return result;
}
navigator_.prototype.return_clas = function (name){
	var return_;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_ = this.all_object[j];
	}
	return return_;
}
navigator_.prototype.return_i_clas = function (name){
	var return_i;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_i = j;
	}
	return return_i;
}