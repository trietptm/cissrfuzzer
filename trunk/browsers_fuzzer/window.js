/* window_s for new window_s */
/* Create new empty window_s */
function window_() {
	this.name = "";
	this.all_func = [];
	this.num_func = 0;
	this.all_atrib = [];
	this.all_atr_func = [];	
	this.all_object = [];
	this.num_object = 0;
	this.dynamic = false;
	this.dynamic_name = [];
	this.dynamic_type = [];
};
/* add dynamic object in "sleep" array  */
window_.prototype.add_sleep_object = function(this_type, this_name)
{
	this.dynamic == true;
	this.dynamic_name.push(this_name);
	this.dynamic_type.push(this_type);
};
/* Generate "window" */
window_.prototype.generate = function () {
	this.add_sleep_object("WindowProxy", "window");
	this.add_sleep_object("WindowProxy", "self");	
	this.add_sleep_object("WindowProxy", "frames");
	this.add_sleep_object("WindowProxy", "top");
	this.add_sleep_object("WindowProxy", "opener");
	this.add_sleep_object("WindowProxy", "parent");	
	this.add_object_type("Document", "document");	
	this.add_attribute ("name", "DOMString");	
	this.add_object_type("Location", "location");		
	this.add_object_type("History", "history");		
	this.add_object_type("BarProp", "locationbar");
	this.add_object_type("BarProp", "menubar");
	this.add_object_type("BarProp", "personalbar");
	this.add_object_type("BarProp", "scrollbars");
	this.add_object_type("BarProp", "statusbar");
	this.add_object_type("BarProp", "toolbar");
	this.add_functions ("close", [""], [""]);		
	this.add_functions ("stop", [""], [""]);		
	this.add_functions ("focus", [""], [""]);		
	this.add_functions ("blur", [""], [""]);		
	this.add_attribute ("length", "unsignedlong");	
	this.add_object_type("Element", "frameElement");	
	this.add_functions ("open", [""], [""]); // WindowProxy open(in optional DOMString url, in optional DOMString target, in optional DOMString features, in optional DOMString replace);
	this.add_functions ("WindowProxy", ["unsignedlong"], ["index"]);	
	this.add_functions ("any", ["DOMString"], ["name"]);	
	this.add_object_type("Navigator", "navigator");		
	this.add_object_type("ApplicationCache", "applicationCache");		
	this.add_functions ("alert", ["DOMString"], ["message"]);	
	this.add_functions ("confirm", ["DOMString"], ["message"]);	
	this.add_functions ("prompt", ["DOMString"], ["message"]);	// DOMString prompt(in DOMString message, in optional DOMString default);
	this.add_functions ("print", [""], [""]);	
	this.add_functions ("showModalDialog", ["DOMString"], ["url"]);	// any showModalDialog(in DOMString url, in optional any argument);
	this.add_attribute_function("onabort");
	this.add_attribute_function("onafterprint");
	this.add_attribute_function("onbeforeprint");
	this.add_attribute_function("onbeforeunload");
	this.add_attribute_function("onblur");
	this.add_attribute_function("oncanplay");
	this.add_attribute_function("oncanplaythrough");
	this.add_attribute_function("onchange");
	this.add_attribute_function("onclick");
	this.add_attribute_function("oncontextmenu");
	this.add_attribute_function("oncuechange");
	this.add_attribute_function("ondblclick");
	this.add_attribute_function("ondrag");
	this.add_attribute_function("ondragend");
	this.add_attribute_function("ondragenter");
	this.add_attribute_function("ondragleave");
	this.add_attribute_function("ondragover");
	this.add_attribute_function("ondragstart");
	this.add_attribute_function("ondrop");
	this.add_attribute_function("ondurationchange");
	this.add_attribute_function("onemptied");
	this.add_attribute_function("onended");
	this.add_attribute_function("onerror");
	this.add_attribute_function("onfocus");
	this.add_attribute_function("onhashchange");
	this.add_attribute_function("oninput");
	this.add_attribute_function("oninvalid");
	this.add_attribute_function("onkeydown");
	this.add_attribute_function("onkeypress");
	this.add_attribute_function("onkeyup");
	this.add_attribute_function("onload");
	this.add_attribute_function("onloadeddata");
	this.add_attribute_function("onloadedmetadata");
	this.add_attribute_function("onloadstart");
	this.add_attribute_function("onmessage");
	this.add_attribute_function("onmousedown");
	this.add_attribute_function("onmousemove");
	this.add_attribute_function("onmouseout");
	this.add_attribute_function("onmouseover");
	this.add_attribute_function("onmouseup");
	this.add_attribute_function("onmousewheel");
	this.add_attribute_function("onoffline");
	this.add_attribute_function("ononline");
	this.add_attribute_function("onpause");
	this.add_attribute_function("onplay");
	this.add_attribute_function("onplaying");
	this.add_attribute_function("onpagehide");
	this.add_attribute_function("onpageshow");
	this.add_attribute_function("onpopstate");
	this.add_attribute_function("onprogress");
	this.add_attribute_function("onratechange");
	this.add_attribute_function("onreadystatechange");
	this.add_attribute_function("onredo");
	this.add_attribute_function("onreset");
	this.add_attribute_function("onresize");
	this.add_attribute_function("onscroll");
	this.add_attribute_function("onseeked");
	this.add_attribute_function("onseeking");
	this.add_attribute_function("onselect");
	this.add_attribute_function("onshow");
	this.add_attribute_function("onstalled");
	this.add_attribute_function("onstorage");
	this.add_attribute_function("onsubmit");
	this.add_attribute_function("onsuspend");
	this.add_attribute_function("ontimeupdate");
	this.add_attribute_function("onundo");
	this.add_attribute_function("onunload");
	this.add_attribute_function("onvolumechange");
	this.add_attribute_function("onwaiting");
	/* !!! + global function */
	this.add_functions("addEventListener", ["DOMString", "EventListener", "boolean"], ["type", "listener", "useCapture"]);
	this.add_functions("removeEventListener", ["DOMString", "EventListener", "boolean"], ["type", "listener", "useCapture"]);
	this.add_functions("dispatchEvent", ["Event"], ["evt"]);
};
/* Add name */
window_.prototype.init_name = function (name_parameter) {
	this.name = name_parameter;
};
/* Add attributes */
window_.prototype.add_attribute = function (name_attribute, type_attribute) 
{
	var new_window_ = new attr;
	new_window_.add(name_attribute, type_attribute);
	this.all_atrib.push(new_window_);
};
/* Add attribute-function */
window_.prototype.add_attribute_function = function (name_attribute) 
{
	var new_window_ = new attr_func;
	new_window_.add(name_attribute);
	this.all_atr_func.push(new_window_);
};
/* Add functions(methods) */
window_.prototype.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = new func;
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
/* Add object */
window_.prototype.add_object = function (name_object)
{
	var new_window_ = new window_;
	new_window_.init_name(name_object);
	this.all_object[this.num_object] = new_window_;
	this.num_object ++;
}
window_.prototype.add_object_type = function (type_object, name_object)
{
	var new_clas = new clas;
	if (type_object == "Document") 
	{
		new_clas = new document_;
		new_clas.init_name(name_object);
		new_clas.generate();
	}
	if (type_object == "HTMLCollection") 
	{
		new_clas = new htmlcollection_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}
	if (type_object == "WindowProxy") 
	{
		new_clas = new window_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}		
	if (type_object == "Navigator") 
	{
		new_clas = new navigator_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}	
	if (type_object == "Location") 
	{
		new_clas = new location_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}	
	if (type_object == "BarProp") 
	{
		new_clas = new barprop_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}		
	if (type_object == "ApplicationCache") 
	{
		new_clas = new applicationCache_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}		
	if (type_object == "History") 
	{
		new_clas = new history_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}
	if (type_object == "Element") 
	{
		new_clas = new element_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}
	
	this.all_object[this.num_object] = new_clas;
	this.num_object ++;
}
/* Return name of window_s */
window_.prototype.ret_name = function () {
	return this.name;
}
/* Return attributes */
window_.prototype.get_attribute = function () {
	var result = [];
	for(var i = 0; i < this.all_atrib.length; i++ )
	{
		result.push(this.all_atrib[i].ret_str());
	}
	return result;
}
/* Return functions */
window_.prototype.get_function = function () {
	var result = [];
	for(var i = 0; i < this.num_func; i++ )
	{
		result.push(this.all_func[i].ret_str());
	}
	return result;
}
window_.prototype.return_clas = function (name){
	var return_;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_ = this.all_object[j];
	}
	return return_;
}
window_.prototype.return_i_clas = function (name){
	var return_i;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_i = j;
	}
	return return_i;
}

window_.prototype.random_event = function (){
	return this.all_atr_func[randint(this.all_atr_func)];
}