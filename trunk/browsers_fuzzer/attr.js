function attr () {
	this.name = "";
	this.typ = "";
};
attr.prototype.add = function(p_name, p_type) {
	this.name = p_name;
	this.type = p_type;
};
attr.prototype.ret_str = function() {
	var str = "." + this.name + " = ";
	/*
	if (getvalue(this.type) != 0 )
		{
		str += getvalue(this.type) + ";";
		}
	else
		{
		str = ";";
		}
	*/
	str += getvalue(this.type) + ";";
	return str;
}
