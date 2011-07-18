/* Class for save attribute */
/* Create new empty attribute */
function attr () {
	this.name = "";
	this.typ = "";
};
/* Add name and type */
attr.prototype.add = function(p_name, p_type) {
	this.name = p_name;
	this.type = p_type;
};
/* Return string. Example, ".name = "AAAA"; " */
attr.prototype.ret_str = function() {
	var str = "." + this.name + " = ";
	str += getvalue(this.type) + ";";
	return str;
}
