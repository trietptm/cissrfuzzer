/* Object like "window" */
/* http://www.w3.org/TR/html5/browsers.html#the-window-object */
function windows() {
	this.window_ =  new clas;

	/*
	this.window_.add_object("window"); // тоже самое
	this.window_.add_object("self"); // тоже самое (текущее)
	this.window_.add_object("opener"); // тоже самое (родитель)
	this.window_.add_object("top");
	this.window_.add_object("parent");
	this.window_.add_object("frames");
	*/

	
	/* document */
	this.window_.add_object_type("Document", "document"); 


	
	/* frameElement */
	this.window_.add_object("frameElement"); 
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("tagName", "DOMString"); 
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("getAttribute", ["DOMString"], ["name"]);
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("setAttribute", ["DOMString", "DOMString"], ["name", "value"]);
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("removeAttribute", ["DOMString"], ["name"]);
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("getAttributeNode", ["DOMString"], ["name"]);
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("setAttributeNode", ["Attr"], ["newAttr"]);
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("removeAttributeNode", ["Attr"], ["oldAttr"]);
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("getElementsByTagName", ["DOMString"], ["name"]);
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("getAttributeNS", ["DOMString", "DOMString"], ["namespaceURI", "localName"]);
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("setAttributeNS", ["DOMString", "DOMString", "DOMString"], ["namespaceURI", "qualifiedName", "value"]);
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("removeAttributeNS", ["DOMString", "DOMString"], ["namespaceURI", "localName"]);	
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("getAttributeNodeNS", ["DOMString", "DOMString"], ["namespaceURI", "localName"]);	
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("setAttributeNodeNS", ["Attr"], ["newAttr"]);	
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("getElementsByTagNameNS", ["DOMString", "DOMString"], ["namespaceURI", "localName"]);		
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("hasAttribute", ["DOMString"], ["name"]);	
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("hasAttributeNS", ["DOMString", "DOMString"], ["namespaceURI", "localName"]);	
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("ELEMENT_NODE", "unsignedshort");
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("ATTRIBUTE_NODE", "unsignedshort");
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("TEXT_NODE", "unsignedshort");
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("CDATA_SECTION_NODE", "unsignedshort");
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("ENTITY_REFERENCE_NODE", "unsignedshort");
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("ENTITY_NODE", "unsignedshort");
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("PROCESSING_INSTRUCTION_NODE", "unsignedshort");
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("COMMENT_NODE", "unsignedshort");
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("DOCUMENT_NODE", "unsignedshort");
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("DOCUMENT_TYPE_NODE", "unsignedshort");
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("DOCUMENT_FRAGMENT_NODE", "unsignedshort");
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("NOTATION_NODE", "unsignedshort");
		// http://www.w3.org/TR/DOM-Level-2-Core/core.html NOde intarfase
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("nodeName", "DOMString");		
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("nodeValue", "DOMString");		
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("nodeType", "unsignedshort");		
		//NodeList
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("parentNode", "Node");			
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("firstChild", "Node");			
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("lastChild", "Node");			
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("previousSibling", "Node");			
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_attribute ("nextSibling", "Node");			
		//NamedNodeMap         
		//Document
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("insertBefore", ["Node", "Node"], ["newChild", "refChild"]);		
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("replaceChild", ["Node", "Node"], ["newChild", "oldChild"]);		
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("removeChild", ["Node"], ["oldChild"]);		
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("appendChild", ["Node"], ["newChild"]);		
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("hasChildNodes", [""], [""]);		
		this.window_.all_object[this.window_.return_i_clas("frameElement")].add_functions ("cloneNode", ["boolean"], ["deep"]);		
	
	/* navigator */
	this.window_.add_object("navigator"); 
		this.window_.all_object[this.window_.return_i_clas("navigator")].add_attribute ("appVersion", "DOMString"); 	
		this.window_.all_object[this.window_.return_i_clas("navigator")].add_attribute ("appName", "DOMString"); 	
		this.window_.all_object[this.window_.return_i_clas("navigator")].add_attribute ("platform", "DOMString"); 	
		this.window_.all_object[this.window_.return_i_clas("navigator")].add_attribute ("userAgent", "DOMString"); 	
		this.window_.all_object[this.window_.return_i_clas("navigator")].add_attribute ("onLine", "boolean"); 	
		this.window_.all_object[this.window_.return_i_clas("navigator")].add_functions ("registerProtocolHandler", ["DOMString", "DOMString", "DOMString"], ["scheme", "url", "title"]);		
		this.window_.all_object[this.window_.return_i_clas("navigator")].add_functions ("registerContentHandler", ["DOMString", "DOMString", "DOMString"], ["mimeType", "url", "title"]);		
		this.window_.all_object[this.window_.return_i_clas("navigator")].add_functions ("yieldForStorageUpdates", [""], [""]);	

	/* location */		
	this.window_.add_object("location");	
		this.window_.all_object[this.window_.return_i_clas("location")].add_attribute ("href", "DOMString"); 		
		this.window_.all_object[this.window_.return_i_clas("location")].add_attribute ("protocol", "DOMString"); 		
		this.window_.all_object[this.window_.return_i_clas("location")].add_attribute ("host", "DOMString"); 		
		this.window_.all_object[this.window_.return_i_clas("location")].add_attribute ("hostname", "DOMString"); 		
		this.window_.all_object[this.window_.return_i_clas("location")].add_attribute ("port", "DOMString"); 		
		this.window_.all_object[this.window_.return_i_clas("location")].add_attribute ("pathname", "DOMString"); 		
		this.window_.all_object[this.window_.return_i_clas("location")].add_attribute ("search", "DOMString"); 		
		this.window_.all_object[this.window_.return_i_clas("location")].add_attribute ("hash", "DOMString"); 		
		this.window_.all_object[this.window_.return_i_clas("location")].add_functions ("assign", ["DOMString"], ["url"]);
		this.window_.all_object[this.window_.return_i_clas("location")].add_functions ("replace", ["DOMString"], ["url"]);	
		this.window_.all_object[this.window_.return_i_clas("location")].add_functions ("reload", [""], [""]);	
		this.window_.all_object[this.window_.return_i_clas("location")].add_functions ("resolveURL", [""], [""]);			
	
	/* history */
	this.window_.add_object("history");
		this.window_.all_object[this.window_.return_i_clas("history")].add_attribute ("length", "long"); 
		this.window_.all_object[this.window_.return_i_clas("history")].add_attribute ("state", "any"); 
		this.window_.all_object[this.window_.return_i_clas("history")].add_functions ("go", [""], [""]);
		this.window_.all_object[this.window_.return_i_clas("history")].add_functions ("back", [""], [""]);
		this.window_.all_object[this.window_.return_i_clas("history")].add_functions ("forward", [""], [""]);
		this.window_.all_object[this.window_.return_i_clas("history")].add_functions ("pushState", ["any", "DOMString", "DOMString"], ["data", "title", "url"]);
		this.window_.all_object[this.window_.return_i_clas("history")].add_functions ("replaceState", ["any", "DOMString", "DOMString"], ["data", "title", "url"]);

	/* applicationCache */		
	this.window_.add_object("applicationCache");
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_functions ("update", [""], [""]);		
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_functions ("swapCache", [""], [""]);		
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute ("UNCACHED", "unsignedshort"); 
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute ("IDLE", "unsignedshort"); 
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute ("CHECKING", "unsignedshort"); 
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute ("DOWNLOADING", "unsignedshort"); 
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute ("UPDATEREADY", "unsignedshort"); 
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute ("OBSOLETE", "unsignedshort"); 
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute ("status", "unsignedshort"); 
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_functions("addEventListener", ["DOMString", "EventListener", "boolean"], ["type", "listener", "useCapture"]);
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_functions("removeEventListener", ["DOMString", "EventListener", "boolean"], ["type", "listener", "useCapture"]);
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_functions("dispatchEvent", ["Event"], ["evt"]);		
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute_function("onchecking");
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute_function("onerror");
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute_function("onnoupdate");
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute_function("ondownloading");
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute_function("onprogress");
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute_function("onupdateready");
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute_function("oncached");
		this.window_.all_object[this.window_.return_i_clas("applicationCache")].add_attribute_function("onobsolete");
		
	this.window_.add_object("locationbar");
	this.window_.add_object("menubar");
	this.window_.add_object("personalbar");
	this.window_.add_object("scrollbars");
	this.window_.add_object("statusbar");
	this.window_.add_object("toolbar");
	
	/* attribute for locationbar, menubar, personalbar, scrollbars, statusbar, toolbar */
		this.window_.all_object[this.window_.return_i_clas("locationbar")].add_attribute ("visible", "boolean"); 
		this.window_.all_object[this.window_.return_i_clas("menubar")].add_attribute ("visible", "boolean"); 
		this.window_.all_object[this.window_.return_i_clas("personalbar")].add_attribute ("visible", "boolean"); 
		this.window_.all_object[this.window_.return_i_clas("scrollbars")].add_attribute ("visible", "boolean"); 
		this.window_.all_object[this.window_.return_i_clas("statusbar")].add_attribute ("visible", "boolean"); 
		this.window_.all_object[this.window_.return_i_clas("toolbar")].add_attribute ("visible", "boolean"); 

/* function for "window" */
	this.window_.add_functions("stop", [""], [""]);
	this.window_.add_functions("focus", [""], [""]);
	this.window_.add_functions("blur", [""], [""]);
	this.window_.add_functions("print", [""], [""]);
	this.window_.add_functions("close", [""], [""]);
	this.window_.add_functions("alert", ["DOMString"], ["message"]);
	this.window_.add_functions("confirm", ["DOMString"], ["message"]);
	this.window_.add_functions("prompt", ["DOMString", "DOMString"], ["message", "default"]);
	this.window_.add_functions("open", ["DOMString", "DOMString", "DOMString", "DOMString"], ["url", "target", "features", "replace"]);

	this.window_.add_functions("WindowProxy", ["unsignedlong"], ["index"]);
	this.window_.add_functions("any", ["DOMString"], ["name"]);

	this.window_.add_functions("showModalDialog", ["DOMString"], ["url"]);
	/* !!! + global function */
	this.window_.add_functions("addEventListener", ["DOMString", "EventListener", "boolean"], ["type", "listener", "useCapture"]);
	this.window_.add_functions("removeEventListener", ["DOMString", "EventListener", "boolean"], ["type", "listener", "useCapture"]);
	this.window_.add_functions("dispatchEvent", ["Event"], ["evt"]);

	this.window_.add_attribute("name", "DOMString");
	this.window_.add_attribute("length", "unsignedlong");

/* attribute like function for "window" */
	this.window_.add_attribute_function("onabort");
	this.window_.add_attribute_function("onafterprint");
	this.window_.add_attribute_function("onbeforeprint");
	this.window_.add_attribute_function("onbeforeunload");
	this.window_.add_attribute_function("onblur");
	this.window_.add_attribute_function("oncanplay");
	this.window_.add_attribute_function("oncanplaythrough");
	this.window_.add_attribute_function("onchange");
	this.window_.add_attribute_function("onclick");
	this.window_.add_attribute_function("oncontextmenu");
	this.window_.add_attribute_function("oncuechange");
	this.window_.add_attribute_function("ondblclick");
	this.window_.add_attribute_function("ondrag");
	this.window_.add_attribute_function("ondragend");
	this.window_.add_attribute_function("ondragenter");
	this.window_.add_attribute_function("ondragleave");
	this.window_.add_attribute_function("ondragover");
	this.window_.add_attribute_function("ondragstart");
	this.window_.add_attribute_function("ondrop");
	this.window_.add_attribute_function("ondurationchange");
	this.window_.add_attribute_function("onemptied");
	this.window_.add_attribute_function("onended");
	this.window_.add_attribute_function("onerror");
	this.window_.add_attribute_function("onfocus");
	this.window_.add_attribute_function("onhashchange");
	this.window_.add_attribute_function("oninput");
	this.window_.add_attribute_function("oninvalid");
	this.window_.add_attribute_function("onkeydown");
	this.window_.add_attribute_function("onkeypress");
	this.window_.add_attribute_function("onkeyup");
	this.window_.add_attribute_function("onload");
	this.window_.add_attribute_function("onloadeddata");
	this.window_.add_attribute_function("onloadedmetadata");
	this.window_.add_attribute_function("onloadstart");
	this.window_.add_attribute_function("onmessage");
	this.window_.add_attribute_function("onmousedown");
	this.window_.add_attribute_function("onmousemove");
	this.window_.add_attribute_function("onmouseout");
	this.window_.add_attribute_function("onmouseover");
	this.window_.add_attribute_function("onmouseup");
	this.window_.add_attribute_function("onmousewheel");
	this.window_.add_attribute_function("onoffline");
	this.window_.add_attribute_function("ononline");
	this.window_.add_attribute_function("onpause");
	this.window_.add_attribute_function("onplay");
	this.window_.add_attribute_function("onplaying");
	this.window_.add_attribute_function("onpagehide");
	this.window_.add_attribute_function("onpageshow");
	this.window_.add_attribute_function("onpopstate");
	this.window_.add_attribute_function("onprogress");
	this.window_.add_attribute_function("onratechange");
	this.window_.add_attribute_function("onreadystatechange");
	this.window_.add_attribute_function("onredo");
	this.window_.add_attribute_function("onreset");
	this.window_.add_attribute_function("onresize");
	this.window_.add_attribute_function("onscroll");
	this.window_.add_attribute_function("onseeked");
	this.window_.add_attribute_function("onseeking");
	this.window_.add_attribute_function("onselect");
	this.window_.add_attribute_function("onshow");
	this.window_.add_attribute_function("onstalled");
	this.window_.add_attribute_function("onstorage");
	this.window_.add_attribute_function("onsubmit");
	this.window_.add_attribute_function("onsuspend");
	this.window_.add_attribute_function("ontimeupdate");
	this.window_.add_attribute_function("onundo");
	this.window_.add_attribute_function("onunload");
	this.window_.add_attribute_function("onvolumechange");
	this.window_.add_attribute_function("onwaiting");
};

windows.prototype.init_name = function (name_parameter) {
	this.window_.name = name_parameter;
};
windows.prototype.return_clas = function (name){
	var return_;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_ = this.all_object[j];
	}
	return return_;
}
windows.prototype.return_i_clas = function (name){
	var return_i;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_i = j;
	}
	return return_i;
}