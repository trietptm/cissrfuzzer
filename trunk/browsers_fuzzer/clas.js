function randint(local_array) {
	return Math.floor(Math.random() * (local_array.length));
};

var clas = {
	name: "",
	attribute: [],
	s_eval: "",
	num_attribute: 0
};
clas.init_name = function (name_parameter) {
	name = name_parameter;
};
clas.init_num_attribute = function(num_attribute_parameter) {
	num_attribute = num_attribute_parameter;
};
clas.init_attribute = function(attribute_parameter) {
	this.attribute.push(attribute_parameter);
};
clas.ret_name = function() {
	return name;
};
clas.ret_num_attribute = function() {
	return num_attribute;
};
clas.ret_attribute = function() {
	return attribute;
};
clas.clean = function() {
	attribute = [];
	num_attribute = 0;
};
clas.creat_eval = function() {
	s_eval = name + "(";
	for(var i=0; i<num_attribute; i++) {
		s_eval += this.attribute[i][randint(this.attribute[i])];
		if (i != num_attribute - 1) s_eval += ", ";
	}
	
	s_eval += ");"
};  
clas.ret_eval = function() {
	return s_eval;
};
clas.make = function() {
	eval(s_eval);
};
clas.creat_and_make = function() {
	s_eval = name + "(";
	for(var i=0; i<num_attribute; i++) {
		s_eval += this.attribute[i][randint(this.attribute[i])];
		if (i != num_attribute - 1) s_eval += ", ";
	}
	s_eval += ");"
	eval(s_eval);
}; 