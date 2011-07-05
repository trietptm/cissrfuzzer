var clas = {
	name: "",
    attribute: [],
	function_list: []
}
clas.init_name = function(name_parameter) {
	name = name_parameter;
}
clas.init_attribute = function(attribute_parameter) {
	attribute = attribute_parameter;
}
clas.init_function_list = function(function_list_parameter) {
	function_list = function_list_parameter;
}
clas.ret_name = function() {
	return name;
}
clas.ret_attribute = function() {
	return attribute;
}
clas.ret_function_list = function() {
	return function_list;
}
clas.clean = function() {
	attribute = [];
	function_list = [];
}       
