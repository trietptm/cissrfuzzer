function clas() {
	this.name =  "";
	this.all_func = [];
	this.num_func = 0;
	this.all_atrib = [];
};

clas.prototype.init_name = function (name_parameter) {
	this.name = name_parameter;
};
clas.prototype.add_attribute = function (name_attribute, type_attribute) 
{
	var new_clas = new attr;
	new_clas.add(name_attribute, type_attribute);
	this.all_atrib.push(new_clas);
};
clas.prototype.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = new func;
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
clas.prototype.ret_name = function () {
	return this.name;
}

clas.prototype.get_attribute = function () {
	var result = [];
	for(var i = 0; i < this.all_atrib.length; i++ )
	{
		//result += this.all_atrib[i].ret_str();
		//if (this.all_atrib[i].ret_str() )
		result.push(this.all_atrib[i].ret_str());
		//result += this.all_atrib[i];
	}
	return result;
}
clas.prototype.get_function = function () {
	var result = [];
	for(var i = 0; i < this.num_func; i++ )
	{
		//result += this.all_atrib[i].ret_str();
		//if (this.all_atrib[i].ret_str() )
		result.push(this.all_func[i].ret_str());
		//result += this.all_atrib[i];
	}
	return result;
}

/*
var clas = {
	name: "",
	all_func: [],
	num_func: 0,
	all_atrib: []	
};

clas.init_name = function (name_parameter) {
	this.name = name_parameter;
};
clas.add_attribute = function (name_attribute, type_attribute) 
{
	var new_clas = clone(attr);
	new_clas.add(name_attribute, type_attribute);
	this.all_atrib.push(new_clas);
};
clas.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = clone(func);
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
clas.ret_name = function () {
	return name;
}
clas.clone = function() {
	var myclone = {	
	name: "",
	all_func: [],
	num_func: 0,
	all_atrib: [],
	init_name : function (name_parameter) {this.name = name_parameter;},
	add_attribute : function (name_attribute, type_attribute) {var new_clas = clone(attr); new_clas.add(name_attribute, type_attribute); this.all_atrib.push(new_clas);},
	add_functions : function (name_function, fun_type, fun_name) { 	var new_func = clone(func); 	new_func.ini_name(name_function); 	new_func.init_attribute(fun_name, fun_type); 	this.all_func[this.num_func] = new_func; 	this.num_func ++;},
	ret_name : function () { 	return name; }
	};
   
   return myclone;
}
*/
/*
function init_names(name_parameter) {
	this.name = name_parameter;
};
function add_attribute(name_attribute, type_attribute) 
{
	var new_clas = clone(attr);
	new_clas.add(name_attribute, type_attribute);
	this.all_atrib.push(new_clas);
};
function add_functions(name_function, fun_type, fun_name)
{
	var new_func = clone(func);
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
function ret_name() {
	return this.name;
}
*/
