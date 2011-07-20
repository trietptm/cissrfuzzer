/* document_s for new document_s */
/* Create new empty document_s */
function document_() {
	this.name = "document";
	this.all_func = [];
	this.num_func = 0;
	this.all_atrib = [];
	this.all_atr_func = [];	
	this.all_object = [];
	this.num_object = 0;
};
/* Generate "document" */
document_.prototype.generate = function () {
	//  + Location location
	this.add_attribute("URL", "DOMString");
	this.add_attribute("domain", "DOMString");
	this.add_attribute("referrer", "DOMString");
	this.add_attribute("cookie", "DOMString");
	this.add_attribute("lastModified", "DOMString");
	this.add_attribute("compatMode", "DOMString");
	this.add_attribute("charset", "DOMString");
	this.add_attribute("characterSet", "DOMString");
	this.add_attribute("defaultCharset", "DOMString");
	this.add_attribute("readyState", "DOMString");
	this.add_functions ("any", ["DOMString"], ["name"]);
	this.add_attribute("title", "DOMString");
	this.add_attribute("dir", "DOMString");
	/*
           attribute HTMLElement body;
  readonly attribute HTMLHeadElement head;
	*/
	this.add_object_type("HTMLCollection", "images"); 
	this.add_object_type("HTMLCollection", "embeds"); 
	this.add_object_type("HTMLCollection", "plugins"); 
	this.add_object_type("HTMLCollection", "links"); 
	this.add_object_type("HTMLCollection", "forms"); 
	this.add_object_type("HTMLCollection", "scripts"); 
	this.add_functions ("getElementsByName", ["DOMString"], ["elementName"]);	
	this.add_functions ("getElementsByClassName", ["DOMString"], ["classNames"]);	
	this.add_attribute("innerHTML", "DOMString");
	this.add_functions ("open", ["DOMString", "DOMString"], ["type", "replace"]);
	this.add_functions ("open", ["DOMString", "DOMString", "boolean"], ["name", "features", "replace"]);
	this.add_functions ("close", [""], [""]);		
	this.add_functions ("write", ["DOMString"], ["text"]);	
	this.add_functions ("writeln", ["DOMString"], ["text"]);	
	// readonly attribute WindowProxy defaultView;
	// readonly attribute Element activeElement;
	this.add_functions ("hasFocus", [""], [""]);	
	this.add_attribute("designMode", "DOMString");	
	this.add_functions ("execCommand", ["DOMString"], ["commandId"]);		
	this.add_functions ("execCommand", ["DOMString", "boolean"], ["commandId", "showUI"]);		
	this.add_functions ("execCommand", ["DOMString", "boolean", "DOMString"], ["commandId", "showUI", "value"]);		
	this.add_functions ("queryCommandEnabled", ["DOMString"], ["commandId"]);
	this.add_functions ("queryCommandIndeterm", ["DOMString"], ["commandId"]);
	this.add_functions ("queryCommandState", ["DOMString"], ["commandId"]);
	this.add_functions ("queryCommandSupported", ["DOMString"], ["commandId"]);
	this.add_functions ("queryCommandValue", ["DOMString"], ["commandId"]);
	this.add_object_type("HTMLCollection", "commands");	
	this.add_attribute_function("ondownloading");
	this.add_attribute_function("onabort");
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
	this.add_attribute_function("oninput");
	this.add_attribute_function("oninvalid");
	this.add_attribute_function("onkeydown");
	this.add_attribute_function("onkeypress");
	this.add_attribute_function("onkeyup");
	this.add_attribute_function("onload");
	this.add_attribute_function("onloadeddata");
	this.add_attribute_function("onloadedmetadata");
	this.add_attribute_function("onloadstart");
	this.add_attribute_function("onmousedown");
	this.add_attribute_function("onmousemove");
	this.add_attribute_function("onmouseout");
	this.add_attribute_function("onmouseover");
	this.add_attribute_function("onmouseup");
	this.add_attribute_function("onmousewheel");
	this.add_attribute_function("onpause");
	this.add_attribute_function("onplay");
	this.add_attribute_function("onplaying");
	this.add_attribute_function("onprogress");
	this.add_attribute_function("onratechange");
	this.add_attribute_function("onreadystatechange");
	this.add_attribute_function("onreset");
	this.add_attribute_function("onscroll");
	this.add_attribute_function("onseeked");
	this.add_attribute_function("onseeking");
	this.add_attribute_function("onselect");
	this.add_attribute_function("onshow");
	this.add_attribute_function("onstalled");
	this.add_attribute_function("onsubmit");
	this.add_attribute_function("onsuspend");
	this.add_attribute_function("ontimeupdate");
	this.add_attribute_function("onvolumechange");
	this.add_attribute_function("onwaiting");
};
/* Add name */
document_.prototype.init_name = function (name_parameter) {
	this.name = name_parameter;
};
/* Add attributes */
document_.prototype.add_attribute = function (name_attribute, type_attribute) 
{
	var new_document_ = new attr;
	new_document_.add(name_attribute, type_attribute);
	this.all_atrib.push(new_document_);
};
/* Add attribute-function */
document_.prototype.add_attribute_function = function (name_attribute) 
{
	var new_document_ = new attr_func;
	new_document_.add(name_attribute);
	this.all_atr_func.push(new_document_);
};
/* Add functions(methods) */
document_.prototype.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = new func;
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
/* Add object */
document_.prototype.add_object = function (name_object)
{
	var new_document_ = new document_;
	new_document_.init_name(name_object);
	this.all_object[this.num_object] = new_document_;
	this.num_object ++;
}
document_.prototype.add_object_type = function (type_object, name_object)
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
	this.all_object[this.num_object] = new_clas;
	this.num_object ++;
}
/* Return name of document_s */
document_.prototype.ret_name = function () {
	return this.name;
}
/* Return attributes */
document_.prototype.get_attribute = function () {
	var result = [];
	for(var i = 0; i < this.all_atrib.length; i++ )
	{
		result.push(this.all_atrib[i].ret_str());
	}
	return result;
}
/* Return functions */
document_.prototype.get_function = function () {
	var result = [];
	for(var i = 0; i < this.num_func; i++ )
	{
		result.push(this.all_func[i].ret_str());
	}
	return result;
}
document_.prototype.return_clas = function (name){
	var return_;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_ = this.all_object[j];
	}
	return return_;
}
document_.prototype.return_i_clas = function (name){
	var return_i;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_i = j;
	}
	return return_i;
}