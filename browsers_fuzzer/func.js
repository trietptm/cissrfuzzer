function func () {
	this.name = "";
	this.attribute = [];
	this.att_type = [];
	this.s_eval = "";
	this.number = 0;
};
func.prototype.ini_name = function (name_parameter) {
	this.name = name_parameter;
};
func.prototype.init_attribute = function(attribute_parameter, attribute_type) {
	this.attribute[this.number] = attribute_parameter;
	this.att_type[this.number] = attribute_type;
	this.number++;
};
func.prototype.clean = function() {
	this.attribute = [];
	this.att_type = [];
};
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
/*
func.creat_eval = function() {
	s_eval = name + "(";
	for(var i=0; i<num_attribute; i++) {
		s_eval += this.attribute[i][randint(this.attribute[i])];
		if (i != num_attribute - 1) s_eval += ", ";
	}
	
	s_eval += ");"
};  
func.ret_eval = function() {
	return s_eval;
};
func.make = function() {
	eval(s_eval);
};
func.creat_and_make = function() {
	s_eval = name + "(";
	for(var i=0; i<num_attribute; i++) {
		s_eval += this.attribute[i][randint(this.attribute[i])];
		if (i != num_attribute - 1) s_eval += ", ";
	}
	s_eval += ");"
	eval(s_eval);
}; 
*/