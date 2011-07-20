/* Class for save attribute that is function*/
/* Create new empty attribute */
function attr_func () {
	this.name = "";
};
/* Add name and type */
attr_func.prototype.add = function(p_name) {
	this.name = p_name;
};
/* Return string. Example, ".name = function_name(); " */
attr_func.prototype.ret_str = function(function_name) {
	var str = "." + this.name + " = ";
	str += function_name + "();";
	return str;
}
