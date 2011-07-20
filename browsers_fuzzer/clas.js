/* Class for new class */
/* Create new empty class */
function clas() {
	this.name =  "";
	this.all_func = [];
	this.num_func = 0;
	this.all_atrib = [];
	this.all_atr_func = [];	
	this.all_object = [];
	this.num_object = 0;
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
/* Add attribute-function */
clas.prototype.add_attribute_function = function (name_attribute) 
{
	var new_clas = new attr_func;
	new_clas.add(name_attribute);
	this.all_atr_func.push(new_clas);
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
/* Add object */
clas.prototype.add_object = function (name_object)
{
	var new_clas = new clas;
	new_clas.init_name(name_object);
	this.all_object[this.num_object] = new_clas;
	this.num_object ++;
}
clas.prototype.add_object_type = function (type_object, name_object)
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
	
	//new_clas.init_name(name_object);
	this.all_object[this.num_object] = new_clas;
	this.num_object ++;
}
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
clas.prototype.return_clas = function (name){
	var return_;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_ = this.all_object[j];
	}
	return return_;
}
clas.prototype.return_i_clas = function (name){
	var return_i;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_i = j;
	}
	return return_i;
}