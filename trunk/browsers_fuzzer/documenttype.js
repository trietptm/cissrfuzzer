/* documenttype_s for new documenttype_s */
/* Create new empty documenttype_s */
function documenttype_() {
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
documenttype_.prototype.add_sleep_object = function(this_type, this_name)
{
	this.dynamic == true;
	this.dynamic_name.push(this_name);
	this.dynamic_type.push(this_type);
};
/* Generate "document" */
documenttype_.prototype.generate = function () {
	this.add_functions ("hasFeature", ["DOMString", "DOMString"], ["feature", "version"]);
	this.add_functions ("createDocumentType", ["DOMString", "DOMString", "DOMString"], ["qualifiedName", "publicId", "systemId"]);
	this.add_functions ("createDocument", ["DOMString", "DOMString", "DocumentType"], ["namespaceURI", "qualifiedName", "doctype"]);
};
/* Add name */
documenttype_.prototype.init_name = function (name_parameter) {
	this.name = name_parameter;
};
/* Add attributes */
documenttype_.prototype.add_attribute = function (name_attribute, type_attribute) 
{
	var new_documenttype_ = new attr;
	new_documenttype_.add(name_attribute, type_attribute);
	this.all_atrib.push(new_documenttype_);
};
/* Add attribute-function */
documenttype_.prototype.add_attribute_function = function (name_attribute) 
{
	var new_documenttype_ = new attr_func;
	new_documenttype_.add(name_attribute);
	this.all_atr_func.push(new_documenttype_);
};
/* Add functions(methods) */
documenttype_.prototype.add_functions = function (name_function, fun_type, fun_name)
{
	var new_func = new func;
	new_func.ini_name(name_function);
	new_func.init_attribute(fun_name, fun_type);
	this.all_func[this.num_func] = new_func;
	this.num_func ++;
};
/* Add object */
documenttype_.prototype.add_object = function (name_object)
{
	var new_documenttype_ = new documenttype_;
	new_documenttype_.init_name(name_object);
	this.all_object[this.num_object] = new_documenttype_;
	this.num_object ++;
}
documenttype_.prototype.add_object_type = function (type_object, name_object)
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

	this.all_object[this.num_object] = new_clas;
	this.num_object ++;
}
/* Return name of documenttype_s */
documenttype_.prototype.ret_name = function () {
	return this.name;
}
/* Return attributes */
documenttype_.prototype.get_attribute = function () {
	var result = [];
	for(var i = 0; i < this.all_atrib.length; i++ )
	{
		result.push(this.all_atrib[i].ret_str());
	}
	return result;
}
/* Return functions */
documenttype_.prototype.get_function = function () {
	var result = [];
	for(var i = 0; i < this.num_func; i++ )
	{
		result.push(this.all_func[i].ret_str());
	}
	return result;
}
documenttype_.prototype.return_clas = function (name){
	var return_;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_ = this.all_object[j];
	}
	return return_;
}
documenttype_.prototype.return_i_clas = function (name){
	var return_i;
	for (var j=0; j < this.num_object; j++)
	{
		if ( this.all_object[j].name == name) 
			return_i = j;
	}
	return return_i;
}