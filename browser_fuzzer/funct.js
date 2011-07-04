var funct = {
	function_return: "",
    function_name: "",
	function_arg: []
}
funct.fun_rt = function(fun_ret) {
	function_return = fun_ret;
}
funct.fun_nm = function(function_name_parameter) {
	var local = function_name_parameter.replace("()","");
	function_name = local.replace("(","");
}
funct.fun_arg = function(function_arg_parameter) {
	var tmp = [];
	var local;
	for(var i=0; i<function_arg_parameter.length; i++) {
		local = function_arg_parameter[i].replace("()","");
		tmp.push( local.replace("(","") );
	}
	function_arg = tmp;
}
funct.clean = function() {
	function_return = "";
    function_name = "";
	function_arg = [];
}
funct.return_function_return = function() {
	return function_return;
}
funct.return_function_name = function() {
	return function_name;
}
funct.return_function_arg = function() {
	return function_arg;
}
