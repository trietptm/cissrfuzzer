var fun = all_function_firefox.split("\n");
var firefox_class = [];
var firefox_j = -1;
var new_clas;
for(var i=0; i<fun.length; i++) {
	if (fun[i].length > 4) 
	{
		if(fun[i].substring(fun[i].length-5,fun[i].length-1) == ".idl") 
		{
			firefox_j++;
			firefox_class[firefox_j] = new clas;
			firefox_class[firefox_j].name = fun[i].substring(0,fun[i].length-5);
		}
		else {
		if (fun[i].length > 9) 
		{ 	
			if(fun[i].substring(0,9) == "attribute") 
			{	
				var new_attribute = fun[i].split(" ");
				firefox_class[firefox_j].add_attribute(new_attribute[2], new_attribute[1]);
			}
		}
		if (fun[i].indexOf("(") != -1) 
		{
			var fun_1 = fun[i].split("(");
			var fun_2 = fun_1[0].split(" ");
			var fun_type = fun_2[0]; // не нужно
			var fun_name = fun_2[1];
			fun_1[1] = fun_1[1].replace(')','');
			var fun_3 = fun_1[1].split(", ");
			var fun_t = [];
			var fun_n = [];
			for(var k =0; k<fun_3.length; k++) 
			{
				var fun_4 = fun_3[k].split(" ");
				fun_t.push(fun_4[0]);
				fun_n.push(fun_4[1]);
			};
			firefox_class[firefox_j].add_functions(fun_name, fun_t, fun_n);
		};
		}
	}
}
