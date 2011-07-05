var bad_strings = ["A" * 255, "A" * 256, "A" * 257, "%x" * 255, "%n" * 255 , "%s" * 255, "%s%n%x%d" * 255, "%s" * 255, "%s" * 255, "%.1024d", "%.2048d", "%.4096d", "%.8200d", "%99999999999s", "%99999999999d", "%99999999999x", "%99999999999n", "%99999999999s" * 255, "%99999999999d" * 255, "%99999999999x" * 255, "%99999999999n" * 255, "%08x" * 100, "%%20s" * 255,"%%20x" * 255,"%%20n" * 255,"%%20d" * 255, "%#0123456x%08x%x%s%p%n%d%o%u%c%h%l%q%j%z%Z%t%i%e%g%f%a%C%S%08x%%#0123456x%%x%%s%%p%%n%%d%%o%%u%%c%%h%%l%%q%%j%%z%%Z%%t%%i%%e%%g%%f%%a%%C%%S%%08x"];
var bad_double = [1.7E-308, 1.7E-307, 1.7E+308, 1.7E+307, 0, 1, 2];
var bad_float = [3.4E-38, 3.4E-37, 3.4E+38, 3.4E+37, 0, 1, 2];
var bad_unsigned_short = [0,65535, 1, 2, 65534, 65533];
var bad_unsigned_int8 = [0,254, 1, 2, 255];
var bad_int8 = [0,-127, 1,-1, 2,-2, 127, 126, -126];
var bad_short = [0,-1, 1, 2, -2, -32768, -32767, -32766, 32768, 32767, 32766];
var bad_unsigned_long = [0, 4294967295,0,65535, 1, 2, 65534, 65533,4294967294,4294967293];
var bad_long = [-2147483648 ,-2147483647, 2147483647, 2147483646, 0, 1, 2, 65534, 65533];
var bad_boolean = [0,1,-1];
var bad_long_long = [9223372036854775807, 0, 1, 2, 9223372036854775806, -9223372036854775807, -9223372036854775806];
var bad_unsigned_long_long = [18446744073709551615,0, 1, 2,18446744073709551614];
var bad_int = [2147483647, 0, -1, 1, 2, -2, 2147483646, -2147483647, -2147483646];
var type_array = ["short", "unsignedshort", "longlong", "unsignedlonglong", "long", "unsignedlong", "DOMString", "boolean", "float", "double", "int"];
var blacklist_type = ["Document", "Node", "Element", "SVGSVGElement"];
var tags = ['address', 'applet', 'area', 'a', 'base', 'basefont', 'big;', 'blockquote', 'body', 'br', 'b', 'caption',
'center', 'cite', 'code', 'dd', 'dfn', 'dir', 'div', 'dl', 'dt', 'em', 'font', 'form', 'h1', 'h2', 'h3', 'h4', 
'h5', 'h6', 'head', 'hr', 'html', 'img', 'input', 'isindex', 'i', 'kbd', 'link', 'li', 'map', 'menu', 'meta',
'ol', 'option', 'param', 'pre', 'p', 'samp', 'script', 'select', 'small', 'strike', 'strong', 'style', 
'sub', 'sup', 'table', 'td', 'textarea', 'th', 'title', 'tr', 'tt', 'ul', 'u', 'var']
var special_words = ['name', 'id', 'email', 'phone', 'data', '*'];

attr = ['class','value','name','data'];
//webkit
var list_event_element = ['onabort','onblur','onchange','onclick','oncontextmenu','ondblclick','ondrag',
'ondragend','ondragenter','ondragleave','ondragover','ondragstart','ondrop','onerror','onfocus',
'oninput','oninvalid','onkeydown','onkeypress','onkeyup','onload','onmousedown','onmousemove',
'onmouseout','onmouseover','onmouseup','onmousewheel','onscroll','onselect','onsubmit',
'onbeforecut','oncut','onbeforecopy','oncopy','onbeforepaste','onpaste','onreset','onsearch',
'onselectstart', 'ontouchstart', 'ontouchmove', 'ontouchend', 'ontouchcancel', 'onwebkitfullscreenchange'];

var list_event_element_special = ['onclick','onerror','onkeydown','onkeypress','onkeyup','onload','onmousedown','onmousemove',
'onmouseout','onmouseover','onmouseup','onmousewheel','onscroll'];