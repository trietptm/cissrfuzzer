/* function return random element from "local_array" */
function randint(local_array) {
	return Math.floor(Math.random() * (local_array.length));
};
/* Examples of function, that return clone of object. But it isn't copy methods */
/*
function clone(obj)
{
return jQuery.extend(true, obj);
}
*/
/*
function clone(object)
{
    if (typeof(object) != "object") return object;
    var newObject = object.constructor();
    for (objectItem in object) {
        newObject[objectItem] = clone(object[objectItem]);
    }
    return newObject;
}
*/
/*
function clone(obj) {
   var key, clone2 = {};
   for(key in obj) if(obj.hasOwnProperty(key)) clone2[key] = obj[key];
   return clone2;
}
*/
/*
function clone(o) {
var c = {};
 if(!o || 'object' !== typeof o)  {
   return o;
 }
 varc = 'function' === typeof o.pop ? [] : {};
 var p, v;
 for(p in o) {
 if(o.hasOwnProperty(p)) {
  v = o[p];
  if(v && 'object' === typeof v) {
    c[p] = clone(v);
  }
  else {
    c[p] = v;
  }
 }
}
 return c;
}
*/
// var c = clone(o);
/* Function return random bad variable with type "type" */
function getvalue(type) {
	function randint(local_array) {
		return Math.floor(Math.random() * (local_array.length));
	}

	var result = "";
	switch (type) {
		case "PRInt8":
			result = String(bad_int8[randint(bad_int8)])
			break
		case "PRUint8":
			result = String(bad_unsigned_int8[randint(bad_unsigned_int8)])
			break
		case "short":
		case "PRInt16":		
			result = String(bad_short[randint(bad_short)]);
			break
		case "unsignedshort":
		case "PRUint16":		
			result = String(bad_unsigned_short[randint(bad_unsigned_short)])
			break
		case "longlong":
		case "PRInt64":		
			result = String(bad_long_long[randint(bad_long_long)])
			break
		case "unsignedlonglong":
		case "PRUint64":		
			result = String(bad_unsigned_long_long[randint(bad_unsigned_long_long)])
			break
		case "long":
			result = String(bad_long[randint(bad_long)])
			break
		case "unsignedlong":
		case "PRUint32":		
			result = String(bad_unsigned_long[randint(bad_unsigned_long)])
			break
		case "double":
			result = String(bad_double[randint(bad_double)])
			break
		case "float":
			result = String(bad_float[randint(bad_float)])
			break
		case "int":
		case "PRInt32":		
			result = String(bad_int[randint(bad_int)])
			break
		case "boolean":
		case "nsresult":	
		case "HRESULT":
		case "IUnknown":		
			result = String(bad_boolean[randint(bad_boolean)])
			break			
		case "DOMString":
		case "ACString":
		case "AUTF8String":
		case "wstring":
		case "string":
		case "wchar":
		case "PRUnichar":
		case "charPtr":
		case "BSTR":
			result = "\"" + String(bad_strings[randint(bad_strings)]) + "\""
			break
		default:
			result = null;
	}
	return result;
}
