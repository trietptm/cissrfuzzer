var fun_webkit = all_function_webkit.split("\n");
var webkit_class = [];
var webkit_j = -1;
var new_clas;
for(var i=0; i<fun_webkit.length; i++) {
	if (fun_webkit[i].length > 4) 
	{
		if(fun_webkit[i].substring(fun_webkit[i].length-5,fun_webkit[i].length-1) == ".idl") 
		{
			webkit_j++;
			webkit_class[webkit_j] = new clas;
			webkit_class[webkit_j].name = fun_webkit[i].substring(0,fun_webkit[i].length-5);
		}
		else {
		if (fun_webkit[i].length > 9) 
		{ 	
			if(fun_webkit[i].substring(0,9) == "attribute") 
			{	
				var new_attribute = fun_webkit[i].split(" ");
				webkit_class[webkit_j].add_attribute(new_attribute[2], new_attribute[1]);
			}
		}
		if (fun_webkit[i].indexOf("(") != -1) 
		{
			var fun_webkit_1 = fun_webkit[i].split("(");
			var fun_webkit_2 = fun_webkit_1[0].split(" ");
			var fun_webkit_type = fun_webkit_2[0]; // не нужно
			var fun_webkit_name = fun_webkit_2[1];
			fun_webkit_1[1] = fun_webkit_1[1].replace(')','');
			var fun_webkit_3 = fun_webkit_1[1].split(", ");
			var fun_webkit_t = [];
			var fun_webkit_n = [];
			for(var k =0; k<fun_webkit_3.length; k++) 
			{
				var fun_webkit_4 = fun_webkit_3[k].split(" ");
				fun_webkit_t.push(fun_webkit_4[0]);
				fun_webkit_n.push(fun_webkit_4[1]);
			};
			webkit_class[webkit_j].add_functions(fun_webkit_name, fun_webkit_t, fun_webkit_n);
		};
		}
	}
}
