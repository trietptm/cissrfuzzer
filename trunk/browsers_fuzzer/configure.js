/* запускать start.html. ќн запускает test2.html  */

var run = [];
//    #1. document.documentElement.firstChild.nextSibling = xyz
run[0] = false;
//    #2. document.documentElement.firstChild.nextSibling.funct() - HTMLElement.prototype.next = function()
run[1] = false;
/*    #3.
    #document.documentElement.firstChild.nextSibling.event
    #window.onload = loaded;
    #function loaded() {
    #
*/
run[2] = false;
//    #4. getElementById, getElementsByTagName (return [])
run[3] = false;
//    #5. getAttribute, setAttribute
run[4] = false;
//    #6. innerHTML
run[5] = false;
//    #7. document.createElementNS( 'http://www.w3.org/1999/xhtml', elem ), document.createElement( elem );
run[6] = true;
//    #8. .appendChild
run[7] = false;
//    #9. .insertBefore
run[8] = false;
// выполнить все 9
var run_all = false;



//  оличество тестов
var number_of_tests = 50;

//  оличество максимально открытых вкладок
var number_of_tabs = 11;

var browser = "webkit"; // or "firefox"

// закрыть окно после удачного выполнени€ 
var close_after = true;


