/* Class for save function(method) */
/* Create new empty function */
function func () {
	this.name = "";
	this.attribute = [];
	this.att_type = [];
	this.s_eval = "";
	this.number = 0;
};
/* Add name of function */
func.prototype.ini_name = function (name_parameter) {
	this.name = name_parameter;
};
/* Add parametrs of function */
func.prototype.init_attribute = function(attribute_parameter, attribute_type) {
	this.attribute[this.number] = attribute_parameter;
	this.att_type[this.number] = attribute_type;
	this.number++;
};
/* Clean function */
func.prototype.clean = function() {
	this.attribute = [];
	this.att_type = [];
};
/* Return string. Example, ".run(5); " */
func.prototype.ret_str = function() {
	var str = "." + this.name + "(";
	for (var j=0; j<this.number; j++)
	{
	str += getvalue(this.att_type[j]);
	if (j != this.number -1) str += ", ";
	}
	str += ");"
	return str;	
};
