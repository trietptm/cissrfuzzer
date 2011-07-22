/* applicationCache_s for new applicationCache_s */
/* Create new empty applicationCache_s */
function applicationCache_() {
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
applicationCache_.prototype.add_sleep_object = function(this_type, this_name)
{
	this.dynamic == true;
	this.dynamic_name.push(this_name);
	this.dynamic_type.push(this_type);
};
/* Generate "BarProp" */
applicationCache_.prototype.generate = function () {
	this.add_functions ("update", [""], [""]);		
	this.add_functions ("swapCache", [""], [""]);		
	this.add_attribute ("UNCACHED", "unsignedshort"); 
	this.add_attribute ("IDLE", "unsignedshort"); 
	this.add_attribute ("CHECKING", "unsignedshort"); 
	this.add_attribute ("DOWNLOADING", "unsignedshort"); 
	this.add_attribute ("UPDATEREADY", "unsignedshort"); 
	this.add_attribute ("OBSOLETE", "unsignedshort"); 
	this.add_attribute ("status", "unsignedshort"); 
	this.add_functions("addEventListener", ["DOMString", "EventListener", "boolean"], ["type", "listener", "useCapture"]);
	this.add_functions("removeEventListener", ["DOMString", "EventListener", "boolean"], ["type", "listener", "useCapture"]);
	this.add_functions("dispatchEvent", ["Event"], ["evt"]);		
	this.add_attribute_function("onchecking");
	this.add_attribute_function("onerror");
	this.add_attribute_function("onnoupdate");
	this.add_attribute_function("ondownloading");
	this.add_attribute_function("onprogress");
	this.add_attribute_function("onupdateready");
	this.add_attribute_function("oncached");
	this.add_attribute_function("onobsolete");	
};
/* Add name */
applicationCache_.prototype.init_name = function (name_parameter) {
	this.name = name_parameter;
};
/* Add attributes */
applicationCache_.prototype.add_attribute = function (name_attribute, type_attribute) 
{
	var new_applicationCache_ = new attr;
	new_applicationCache_.add(name_attribute, type_attribute);
	this.all_atrib.push(new_applicationCache_);
};
/* Add attribute-function */
applicationCache_.prototype.add_attribute_function = function (name_attribute) 
{
	var new_applicationCache_ = new attr_func;
	new_applicationCache_.add(name_attribute);
	this.all_atr_func.push(new_applicationCache_);
};
/* Add functions(methods) */
applicationCache_.prototype.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = new func;
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
/* Add object */
applicationCache_.prototype.add_object = function (name_object)
{
	var new_applicationCache_ = new applicationCache_;
	new_applicationCache_.init_name(name_object);
	this.all_object[this.num_object] = new_applicationCache_;
	this.num_object ++;
}
/* not use
applicationCache_.prototype.add_object = function (type_object)
{
	var new_applicationCache_ = new applicationCache_;
	if (type_object == "applicationCache_") 
	{
	new_applicationCache_ = new applicationCache_;
	}
	
	new_applicationCache_.init_name(name_object);
	this.all_object[this.num_object] = new_applicationCache_;
	this.num_object ++;
}
*/
/* Return name of applicationCache_s */
applicationCache_.prototype.ret_name = function () {
	return this.name;
}
/* Return attributes */
applicationCache_.prototype.get_attribute = function () {
	var result = [];
	for(var i = 0; i < this.all_atrib.length; i++ )
	{
		result.push(this.all_atrib[i].ret_str());
	}
	return result;
}
/* Return functions */
applicationCache_.prototype.get_function = function () {
	var result = [];
	for(var i = 0; i < this.num_func; i++ )
	{
		result.push(this.all_func[i].ret_str());
	}
	return result;
}
applicationCache_.prototype.return_clas = function (name){
	var return_;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_ = this.all_object[j];
	}
	return return_;
}
applicationCache_.prototype.return_i_clas = function (name){
	var return_i;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_i = j;
	}
	return return_i;
}