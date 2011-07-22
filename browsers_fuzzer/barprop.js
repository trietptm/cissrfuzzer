/* barprop_s for new barprop_s */
/* Create new empty barprop_s */
function barprop_() {
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
barprop_.prototype.add_sleep_object = function(this_type, this_name)
{
	this.dynamic == true;
	this.dynamic_name.push(this_name);
	this.dynamic_type.push(this_type);
};
/* Generate "BarProp" */
barprop_.prototype.generate = function () {
	this.add_attribute ("visible", "boolean");	
};
/* Add name */
barprop_.prototype.init_name = function (name_parameter) {
	this.name = name_parameter;
};
/* Add attributes */
barprop_.prototype.add_attribute = function (name_attribute, type_attribute) 
{
	var new_barprop_ = new attr;
	new_barprop_.add(name_attribute, type_attribute);
	this.all_atrib.push(new_barprop_);
};
/* Add attribute-function */
barprop_.prototype.add_attribute_function = function (name_attribute) 
{
	var new_barprop_ = new attr_func;
	new_barprop_.add(name_attribute);
	this.all_atr_func.push(new_barprop_);
};
/* Add functions(methods) */
barprop_.prototype.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = new func;
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
/* Add object */
barprop_.prototype.add_object = function (name_object)
{
	var new_barprop_ = new barprop_;
	new_barprop_.init_name(name_object);
	this.all_object[this.num_object] = new_barprop_;
	this.num_object ++;
}
/* not use
barprop_.prototype.add_object = function (type_object)
{
	var new_barprop_ = new barprop_;
	if (type_object == "barprop_") 
	{
	new_barprop_ = new barprop_;
	}
	
	new_barprop_.init_name(name_object);
	this.all_object[this.num_object] = new_barprop_;
	this.num_object ++;
}
*/
/* Return name of barprop_s */
barprop_.prototype.ret_name = function () {
	return this.name;
}
/* Return attributes */
barprop_.prototype.get_attribute = function () {
	var result = [];
	for(var i = 0; i < this.all_atrib.length; i++ )
	{
		result.push(this.all_atrib[i].ret_str());
	}
	return result;
}
/* Return functions */
barprop_.prototype.get_function = function () {
	var result = [];
	for(var i = 0; i < this.num_func; i++ )
	{
		result.push(this.all_func[i].ret_str());
	}
	return result;
}
barprop_.prototype.return_clas = function (name){
	var return_;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_ = this.all_object[j];
	}
	return return_;
}
barprop_.prototype.return_i_clas = function (name){
	var return_i;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_i = j;
	}
	return return_i;
}