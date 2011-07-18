/* Class for new class */
/* Create new empty class */
function clas() {
	this.name =  "";
	this.all_func = [];
	this.num_func = 0;
	this.all_atrib = [];
};
/* Add name */
clas.prototype.init_name = function (name_parameter) {
	this.name = name_parameter;
};
/* Add attributes */
clas.prototype.add_attribute = function (name_attribute, type_attribute) 
{
	var new_clas = new attr;
	new_clas.add(name_attribute, type_attribute);
	this.all_atrib.push(new_clas);
};
/* Add functions(methods) */
clas.prototype.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = new func;
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
/* Return name of class */
clas.prototype.ret_name = function () {
	return this.name;
}
/* Return attributes */
clas.prototype.get_attribute = function () {
	var result = [];
	for(var i = 0; i < this.all_atrib.length; i++ )
	{
		result.push(this.all_atrib[i].ret_str());
	}
	return result;
}
/* Return functions */
clas.prototype.get_function = function () {
	var result = [];
	for(var i = 0; i < this.num_func; i++ )
	{
		result.push(this.all_func[i].ret_str());
	}
	return result;
}
