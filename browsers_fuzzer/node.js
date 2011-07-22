/* node_s for new node_s */
/* Create new empty node_s */
function node_() {
	this.name = "document";
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
node_.prototype.add_sleep_object = function(this_type, this_name)
{
	this.dynamic == true;
	this.dynamic_name.push(this_name);
	this.dynamic_type.push(this_type);
};
/* Generate "document" */
node_.prototype.generate = function () {
	this.add_attribute("ELEMENT_NODE", "unsignedshort");
	this.add_attribute("ATTRIBUTE_NODE", "unsignedshort");
	this.add_attribute("TEXT_NODE", "unsignedshort");
	this.add_attribute("CDATA_SECTION_NODE", "unsignedshort");
	this.add_attribute("ENTITY_REFERENCE_NODE", "unsignedshort");
	this.add_attribute("ENTITY_NODE", "unsignedshort");
	this.add_attribute("PROCESSING_INSTRUCTION_NODE", "unsignedshort");
	this.add_attribute("COMMENT_NODE", "unsignedshort");
	this.add_attribute("DOCUMENT_NODE", "unsignedshort");
	this.add_attribute("DOCUMENT_TYPE_NODE", "unsignedshort");
	this.add_attribute("DOCUMENT_FRAGMENT_NODE", "unsignedshort");
	this.add_attribute("NOTATION_NODE", "unsignedshort");
	this.add_attribute("nodeName", "DOMString");
	this.add_attribute("nodeValue", "DOMString");
	this.add_attribute("nodeType", "unsignedshort");
	this.add_sleep_object("Node", "parentNode");  
	this.add_object_type("NodeList", "childNodes"); 	  
	this.add_sleep_object("Node", "firstChild");
	this.add_sleep_object("Node", "lastChild");
	this.add_sleep_object("Node", "previousSibling");
	this.add_sleep_object("Node", "nextSibling");	
	this.add_object_type("NamedNodeMap", "attributes");   
	this.add_object_type("Document", "ownerDocument"); 	
	this.add_functions ("insertBefore", ["Node", "Node"], ["newChild", "refChild"]);	
	this.add_functions ("replaceChild", ["Node", "Node"], ["newChild", "oldChild"]);	
	this.add_functions ("removeChild", ["Node"], ["oldChild"]);	
	this.add_functions ("appendChild", ["Node"], ["newChild"]);	
	this.add_functions ("hasChildNodes", [""], [""]);	
	this.add_functions ("cloneNode", ["boolean"], ["deep"]);	
	this.add_functions ("normalize", [""], [""]);
	this.add_functions ("isSupported", ["DOMString", "DOMString"], ["feature", "version"]);		
	this.add_attribute("namespaceURI", "DOMString");								 
	this.add_attribute("prefix", "DOMString");								 
	this.add_attribute("localName", "DOMString");								 
	this.add_functions ("hasAttributes", [""], [""]);
};
/* Add name */
node_.prototype.init_name = function (name_parameter) {
	this.name = name_parameter;
};
/* Add attributes */
node_.prototype.add_attribute = function (name_attribute, type_attribute) 
{
	var new_node_ = new attr;
	new_node_.add(name_attribute, type_attribute);
	this.all_atrib.push(new_node_);
};
/* Add attribute-function */
node_.prototype.add_attribute_function = function (name_attribute) 
{
	var new_node_ = new attr_func;
	new_node_.add(name_attribute);
	this.all_atr_func.push(new_node_);
};
/* Add functions(methods) */
node_.prototype.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = new func;
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
/* Add object */
node_.prototype.add_object = function (name_object)
{
	var new_node_ = new node_;
	new_node_.init_name(name_object);
	this.all_object[this.num_object] = new_node_;
	this.num_object ++;
}
node_.prototype.add_object_type = function (type_object, name_object)
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
	if (type_object == "Location") 
	{
		new_clas = new location_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}	
	if (type_object == "HTMLElement") 
	{
		new_clas = new htmlelement_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}		
	if (type_object == "HTMLHeadElement") 
	{
		new_clas = new htmlheadelement_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}	
	
	if (type_object == "NodeList") 
	{
		new_clas = new nodelist_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}	
	if (type_object == "Node") 
	{
		new_clas = new node_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}	
	if (type_object == "NamedNodeMap") 
	{
		new_clas = new namednodemap_;
		new_clas.generate();	
		new_clas.init_name(name_object);	
	}
	
	this.all_object[this.num_object] = new_clas;
	this.num_object ++;
}
/* Return name of node_s */
node_.prototype.ret_name = function () {
	return this.name;
}
/* Return attributes */
node_.prototype.get_attribute = function () {
	var result = [];
	for(var i = 0; i < this.all_atrib.length; i++ )
	{
		result.push(this.all_atrib[i].ret_str());
	}
	return result;
}
/* Return functions */
node_.prototype.get_function = function () {
	var result = [];
	for(var i = 0; i < this.num_func; i++ )
	{
		result.push(this.all_func[i].ret_str());
	}
	return result;
}
node_.prototype.return_clas = function (name){
	var return_;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_ = this.all_object[j];
	}
	return return_;
}
node_.prototype.return_i_clas = function (name){
	var return_i;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_i = j;
	}
	return return_i;
}