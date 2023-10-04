#include "vm.h"
#include <stdbool.h> // true false bool
#include <stdio.h> // printf puts
#include <string.h> // strlen

#ifdef SMALLBIN
#define SB(x,y) (x)
#else
#define SB(x,y) (y)
#endif

static bool _debug = false;
static unsigned int _errorCount = 0;

static int
test_case(const char *prog, bool debug) {
  Parser *p = Parser_new();
  int ret = Parser_eval(p, prog, strlen(prog), debug);
  Parser_free(p);
  return ret;
}

static void
t3(const char *code, int expect, const char *name) {
  const char *title = name ? name : code;
  if (_debug) {
    printf("=testing: %s\n", title);
  }
  int res = test_case(code, _debug);
  if (res != expect) {
    if (_debug) {
      printf(" -fail: got %d, expected %d\n", res, expect);
    } else {
      printf("fail: %s: got %d, expected %d\n", title, res, expect);
      test_case(code, 1);
    }
    _errorCount++;
  }
}

static void
t(const char *code, int expect) {
  t3(code, expect, 0);
}

int
main(void) {
  t("function fn() { var i; i = 9 }; fn()", 0);
  t("function f() { return 9 }; var i; i = f()", 9);
  t("var i; function f() { return 7; i = 8 }; i = 9; f(); i", 9);
  t("var i; i = 9; function f() { i = 8 }; var g; g = f; i", 9);
  t("function f() { return 9 }; var m; m = new Object; m.a = f; m.a()", 9);
  t("function f() { function g() { return 9 }; return g() }; f()", 9);
  t("function f() { return 9 }; function g() { return f(); }; g()", 9);

  t3(
    "var a; var b; a = 24; b = 42; while (b < a) { a = a - b }; while (a < b) { while (a < b) { b = b - a }; while (b < a) { a = a - b } }; b",
    6,
    "while_gcd"
  );

  t("function f() { return 9 }; f()", 9);
  t("function f() { var i; i = 9; return i }; f()", 9);
  t("var i; i = 9; function f() { return i }; f()", 9);
  t("var i; i = 8; function f() { var i; i = 9; return i }; f()", 9);
  t("var i; i = 9; function f() { var i; i = 8; return i }; f(); i", 9);
  t("function f() { return 5 }; function g() { return 4 }; f() + g()", 9);
  t("function f() { return 9 }; f(8)", 9);
  t("function f(a) { return a + 4 }; f(5)", 9);
  t("function f(a) { return a === undefined }; f()", 1);
  t("function f(a, b) { return a + b }; f(4, 5)", 9);
  t("function f(a, b) { return b > a }; f(4, 5)", 1);
  t("function f(a, b, c) { return (a + b) + c }; f(2, 3, 4)", 9);
  t("function f(a, b, c) { return (c > b) & (b > a) }; f(2, 3, 4)", 1);
  t("function f() { 8 }; f() === undefined", 1);

  t("var s; s = 'a' + 'b'; s === 'ab'", 1);
  t("var s; s = 9 + 'x'; s === '9x'", 1);
  t("var s; s = 'x' + 9; s === 'x9'", 1);
  t("String.fromCharCode(48) === '0'", 1);
  t("var i = String.fromCharCode(undefined); i.charCodeAt(0) === 0", 1);
  t("var i = String.fromCharCode(null); i.charCodeAt(0) === 0", 1);
  t("var i = String.fromCharCode(new Object); i.charCodeAt(0) === 0", 1);
  t("var s = 'a'; s.indexOf('c') === -1", 1);
  t("var s = 'abcd'; s.indexOf('c') === 2", 1);
  t("var s = 'abcd'; s.indexOf('bc') === 1", 1);
  t("var i; i = 9", 9);
  t("var i = 9; i", 9);
  t("!0", 1);
  t("!1", 0);
  t("!''", 1);
  t("!'8'", 0);
  t("!!''", 0);
  t("!!8", 1);
  t("!(0 | 1)", 0);
  t("(~0) === -1", 1);
  t("(~1) === -2", 1);
  t("~(-1) === 0", 1);
  t("~(-2) === 1", 1);
  t("-", -1);
  t("-(-9)", 9);
  t("var i = -9; -i", 9);
  t("-null", -2); // non-conforming
  t("var i; i = 0; i = !i", 1);
  t("var xY_0; xY_0 = 9", 9);
  t("var i; i = 9; i", 9);
  t("var i; i = 2 + 3", 5);
  t("var i; var j;  i = j = 9", 9);
  t("var i; var j; i = j = 9; i", 9);
  t("var i; var j; i = j = 9; j", 9);

  t("var m; m = new Object; m['a']", 0);
  t("var m; m = new Object; m['a'] = 9", 9);
  t("var m; m = new Object; m['a'] = 9; m['a']", 9);
  t("var m; m = new Object; m.a", 0);
  t("var m; m = new Object; m.a = 9; m.a", 9);
  t("var m; m = new Object; m.a === undefined", 1);
  t("var p; var q; p = new Object; q = p; p.a = 9; q.a", 9);
  t("var p; var q; p = new Object; q = new Object; q.p = p; q.p", 1);
  t("var p; var q; p = new Object; p.a = 9; q = new Object; q.p = p; p = q.p; p.a", 9);

  t("var p = new Object; p.a = 9; var q = new Object; q.p = p; q.p.a", 9);
  t("var p = new Object; p.a = 9; var q = new Object; q.r = p; p = new Object; p.q = q; p.q.r.a", 9);
  t("var p = new Object; p.a = 8; var q = new Object; q.r = p; p = new Object; p.q = q; p.q.r.a = 9; p.q.r.a", 9);
  t("var p = new Object; p.a = 8; var q = new Object; q.r = p; p = new Object; p.q = q; p.q.r = 9; p.q.r", 9);
  t("var p = new Object; var v = new Array; v[0] = 9; p.v = v; p.v[0]", 9);
  t("var p = new Object; p.v = new Array; p.v[0] = 9; p.v[0]", 9);
  t("var p = new Object; p.x.y", -2);
  t("var i = 2; i.x", -2);
  t("var i = 2; i.x", -2);
  t("var s = 'c'; s.length.x", -2);
  t("var s = 'c'; s.x", -2);
  t("u.x", -2);
  t("var p = new Object; p.a = 9; var q = new Object; q.p = p; q['p']['a']", 9);

  t("var i; i = 3; while (i) { i = i - 1 }; i", 0);
  t("var i; var j; var k; k = 0; i = 3; while (i) { j = 3; while (j) { k = k + 1; j = j - 1 }; i = i - 1 }; k", 9);
  t("var v; v = new Object; v[1", -1);
  t3(
    "var v; v = new Object; v[0] = 9; v[1] = 8; v[2] = 7; var s; s = ''; var i; i = 0; while (v[i]) { s = s + v[i]; i = i + 1 }; s === '987'",
    1,
    "test_while_concat"
  );

  t("var o = new Object; o.a = 4; o.b = 5; var s = 0; var i; for (i in o) { s = s + o[i]; }; s", 9);
  t("var p = new Object; p.ab = 3; p.cd = 4; var q = new Object; var n = 0; var i; for (i in p) { q[i] = p[i]; n = n + 1; }; (q.ab + q.cd) + n", 9);
  t("var o = new Object; o.a = 4; o.b = 5; var n = 0; var x; try { var i; for (i in o) { n = n + 1; throw 8; } } catch (e) { x = e; }; x + n", 9);
  t("var x = 9; if (0) { var o = 0; var i; for (i in o) { x = x + 1; } }; x", 9);

  t("var v; v = new Array; v[0] === undefined", 1);
  t("var v; v = new Array; v[0] = 9; v[0]", 9);
  t("var v; v = new Array; v.length === 0", 1);
  t("var v; v = new Array; v[0] = 8; v[1] = 7; v.length", 2);
  t("var v; v = new Array; v.length = 1", -2);
  t("var v; v = new Array; v.u === undefined", 1);

  t("var u; while (0) { u = 9 }; u", 0);
  t("while (0) { 9 }", 0);

  t("var i; if (2) { i = 9 }; i", 9);
  t("var i; i = 2; if (i) { i = 9 }; i", 9);
  t("var i; i = 9; if (0) { i = 8 }; i", 9);
  t("var i; if (2) { i = 9 } else { i = 8 }; i", 9);
  t("var i; if (0) { i = 8 } else { i = 9 }; i", 9);
  t("var i; if (2) { i = 8; i = 9 } else { i = 6; i = 7 }; i", 9);
  t("var i; if (0) { i = 6; i = 7 } else { i = 8; i = 9 }; i", 9);
  t("var i; if (2) { if (3) { i = 9 } }; i", 9);
  t("var i; if (2) { if (3) { i = 9 } else { i = 8 } } else { i = 7 }; i", 9);

  t("undefined", 0);
  t("987654321", 987654321);
  t("(9)", 9);
  t("(4 + 5)", 9);
  t("2 + (3 + 4)", 9);
  t("1 + (1 + (3 + 4))", 9);
  t("-9", -9);
  t("5+-3", 2);
  t("2 + 3", 5);
  t("5 - 3", 2);
  t("3 | 6", 7);
  t("2 * 3", 6);
  t("8 / 4", 2);
  t("5 % 3", 2);
  t("5 ^ 6", 3);
  t("9 & 10", 8);
  t("9 && 0", 0);
  t("0 && 9", 0);
  t("8 && 9", 9);
  t("'8' && 9", 9);
  t("(7 && '8') === '8'", 1);
  t("(0 || '8') === '8'", 1);
  t("('8' || 9) === '8'", 1);
  t("9 || 0", 9);
  t("0 || 9", 9);
  t("9 || 8", 9);
  t("var i; i = 8; 1 && (i = 9); i", 9);
  t("var i; i = 9; 0 && (i = 8); i", 9);
  t("var i; i = 8; 0 || (i = 9); i", 9);
  t("var i; i = 9; 1 || (i = 8); i", 9);
  t("14 >> 2", 3);
  t("2 << 2", 8);
  t("2 < 3", 1);
  t("3 < 2", 0);
  t("2 > 3", 0);
  t("3 > 2", 1);
  t("2 <= 3", 1);
  t("3 <= 2", 0);
  t("2 <= 2", 1);
  t("2 >= 3", 0);
  t("3 >= 2", 1);
  t("2 >= 2", 1);
  t("2 === 2", 1);
  t("2 === 3", 0);
  t("2 !== 2", 0);
  t("2 !== 3", 1);
  t("NaN", 0);
  t("NaN !== NaN", 1);
  t("isNaN(NaN)", 1);
  t("isNaN(8)", 0);
  t("undefined === undefined", 1);
  t("undefined !== undefined", 0);
  t("0 === undefined", 0);
  t("0 === '0'", 0);
  t("0 === ''", 0);
  t("0 === new Object", 0);
  t("0 === null", 0);
  t("null", 0);
  t("null === null", 1);
  t("null === undefined", 0);
  t("null !== null", 0);
  t("null !== undefined", 1);
  t("\"xa\" === \"xa\"", 1);
  t("\"xa\" === \"xb\"", 0);
  t("'xa' === 'xa'", 1);
  t("'xa' === 'xb'", 0);
  t("'xa' !== 'xa'", 0);
  t("'xa' !== 'xb'", 1);
  t("var s = ''; s.length === 0", 1);
  t("var s = 'a'; s.length", 1);
  t("var s = 'a'; s.missing", -2);
  t("var s = 'ab'; s.length", 2);
  t("var s = ''; s.length = 1", -2);
  t("var s = 'a'; s.charAt(-1) === ''", 1);
  t("var s = 'a'; isNaN(s.charCodeAt(-1))", 1);
  t("var s = ''; s.charAt(0) === ''", 1);
  t("var s = 'a'; s.charAt(0) === 'a'", 1);
  t("var s = 'abc'; s.charAt(1) === 'b'", 1);
  t("var s = 'abc'; s.charAt(2) === 'c'", 1);
  t("var s = 'abc'; s.charCodeAt(2)", 99);
  t("var s = 'abc'; var f = s.charCodeAt; f(2)", 99);
  t("var s = 'abc'; s.charAt(3) === ''", 1);
  t("var s = 'abc'; isNaN(s.charCodeAt(3))", 1);
  t("var s = 'c'; s.charCodeAt(undefined)", 99);
  t("var s = 'c'; s.charCodeAt(null)", 99);
  t("var s = 'c'; s.charCodeAt(new Object)", 99);
  t("var s = 'c'; s.charAt(undefined) === 'c'", 1);
  t("new Object", 1);
  t("new Array", 1);
  t("''", 0);
  t("'x'", 1);
  t("8; 9", 9);

  t("typeof undefined === 'undefined'", 1);
  t("typeof '' === 'string'", 1);
  t("typeof 8 === 'number'", 1);
  t("var o = new Object; typeof o === 'object'", 1);

  // ES5
  t("var s = 'a'; s[-1] === ''", 1);
  t("var s = ''; s[0] === ''", 1);
  t("var s = 'a'; s[0] === 'a'", 1);
  t("var s = 'abc'; s[1] === 'b'", 1);
  t("var s = 'abc'; s[2] === 'c'", 1);
  t("var s = 'abc'; s[3] === ''", 1);
  t("var s = 'c'; s[undefined] === 'c'", 1);
  t("var s = 'c'; s[null] === 'c'", 1);
  t("var s = 'c'; s[new Object] === 'c'", 1);
  t("var s = 'a'; s[0] = 'x'", -2);

  t("var i; i === undefined", 1);
  t("var i; i = 9", 9);

  t("var i; i = 9; i()", -2);
  t(".error", -1);
  t("u", -2);
  t("u = 9", -2);
  t("return 9", -2);
  t("function f() { var i; i = 9 }; f(); i", -2);
  t("function f() { var i; i = 9; return i }; f(); i", -2);
  t("console.log(9", -1);

  // TODO Object reference cycles
  t("var p; var q; p = new Object; q = new Object; p.q = q; q.p = p; q = p.q; q.p", SB(1, -2));
  t("var p; var q; var t; p = new Object; q = new Object; p.q = q; q.p = p; t = p.q; t.p", SB(1, -2));
  t("var p; var q; var t; p = new Object; q = new Object; p.q = q; q.p = p; q.i = 9; t = q.p; t = t.q; t.i", SB(9, -2));
  t("var p; p = new Object; p.p = p; p = p.p; p.p", SB(1, -2));
  t("var p; var q; p = new Object; q = new Object; p.p = p; p.q = q; q.p = p; q.q = q; q = p.q; q = q.p; q = q.p", SB(1, -2));
  t("var o; var p; var q; o = new Object; p = new Object; q = new Object; o.p = p; p.q = q; q.o = o; o = o.p; o = o.q; o.o", SB(1, -2));
  t("var o; var p; var q; o = new Object; p = new Object; q = new Object; o.p = p; o.q = q; p.q = q; p.o = o; q.p = p; q.o = o; o = o.p; o = o.q; o.o", SB(1, -2));

  // TODO function scope reference cycles
  t("var o; o = new Object; function f() { 9 }; o.f = f", SB(1, -2));
  t("function obj() { var o; o = new Object; o.i = 9; function get() { return o.i }; o.get = get; return o }; var p; p = obj(); p.get()", SB(9, -2));
  t("function obj() { var o; o = new Object; o.i = 8; function inc() { o.i = o.i + 1 }; o.inc = inc; function get() { return o.i }; o.get = get; return o }; var p; p = obj(); p.inc(); p.get()", SB(9, -2));

  // ok
  t("function obj() { var s; s = new Object; s.i = 9; function get() { return s.i }; var m; m = new Object; m.get = get; return m }; var p; p = obj(); p.get()", 9);
  t("function obj() { var s; s = new Object; s.i = 8; function get() { return s.i }; function inc() { s.i = s.i + 1 }; function ret() { var m; m = new Object; m.get = get; m.inc = inc; return m }; return ret() }; var p; p = obj(); p.inc(); p.get()", 9);
  t("function obj() { var s; s = new Object; s.i = 8; function get() { return s.i }; function inc() { s.i = s.i + 1 }; function ret() { var m; m = new Object; m.get = get; m.inc = inc; m.s = s; return m }; return ret() }; var p; p = obj(); p.inc(); p.get(); var t; t = p.s; t.i", 9);

  // TODO function scope by reference
  t("var i; function f() { i = 9 }; f(); i", SB(9, 0));
  t("var i; function f() { i = 9 }; f(); i = 8; f(); i", SB(9, 8));
  t("var i; function f() { i = 9 }; var m; m = new Object; m.a = f; m.a(); i", SB(9, 0));
  t(
    "var i; var j; i = 0; j = 0; function f() { function g() { i = i + 1; return 2; i = i + 8 }; j = g(); i = i + 4 }; f(); i + j",
    SB(7, 0));
  t("function g() { return f(); }; function f() { return 9 }; g()", -2);

  // TODO application
  t("var i; i = (function() { return 9 })(); i", -1);


  t("var i; try { i = 9 } catch (e) { i = 8 }; i", 9);
  t("var i; try { throw 4 } catch (e) { i = 9 }; i", 9);
  t("var i; var j; try { j = 4; throw 3; j = 2 } catch (e) { i = j + 5 }; i", 9);
  t("var i; try { throw 9 } catch (e) { i = e }; i", 9);
  t("var i; try { try { throw 8 } catch (e) { i = 9 } } catch (f) { i = 2 }; i", 9);
  t("var i; try { try { i = 2 } catch (e) { i = 3 }; throw 8 } catch (f) { i = 9 }; i", 9);
  t("function f() { throw 4 }; var i; try { f() } catch (e) { i = 9 }; i", 9);
  t("throw 5", -2);
  t("throw 5; 8", -2);
  t("var i; try { throw 4 } CATCH (e) { i = 2 }", -1);
  t("try { throw 4 } catch (e) { throw 5 }", -2);
  t("var i; try { try { throw 4 } catch (e) { throw 9 } } catch (e) { i = e }; i", 9);

  t("if (1) { 8 } 9", 9);
  t("if (1) { 8 } else { 7 } 9", 9);
  t("while (0) { 8 } 9", 9);
  t("function f() { 8 } 9", 9);
  t("try { 8 } catch (e) { 7 } 9", 9);

  t("7 8", -1);
  t("if (1) { 7 8 }", -1);
  t("if (1) { if (1) { 7 8 } }", -1);
  t("if (1) { if (1) { 6 } 7 8 }", -1);

  t("9;", 9);
  t("9; ", 9);
  t("9;\n ", 9);
  t("if (1) { 8; }", 0);
  t("if (1) { 8; } else { 7; }", 0);
  t("if (0) { 8; } else { 7; }", 0);
  t("if (1) { 8 } 9", 9);
  t("if (1) { 8 } else { 7 } 9", 9);
  t("if (1) { if (1) { 8 } } 9", 9);
  t("if (1) { if (1) { 8 } } else { 8 }", 0);
  t("if (0) { if (1) { 8 } } else { 8 }", 0);
  t("if (1) { 8 } if (1) { 8 }", 0);
  t("if (0) { 8 } if (1) { 8 }", 0);
  t("while (0) { 8; }", 0);
  t("function f() { 8; }", 0);
  t("try { 8; } catch (e) { 7; }", 0);
  t("if (1) { 8 }; else { 7 }", -2);
  t("try { 8 }; catch (e) { 7 }", -1);

  t("if (1) {}", 0);
  t("if (1) {} else {}", 0);
  t("if (1) {} else if (1) {}", 0);
  t("if (0) {} else if (1) {}", 0);
  t("var i; if (1) i = 9; i", 9);
  t("var i; if (0) {} else i = 9; i", 9);
  t("var i; if (0) i = 8; else i = 9; i", 9);
  t("while (0) {}", 0);
  t("function f() {}", 0);
  t("var f; f = function() { return 9 }; f()", 9);
  t("var f; f = function g() { return 9 }; f()", 9);
  t("var f; f = function g() { return 9 }; g()", -2);
  t("try {} catch (e) {}", 0);

  t("", 0);
  t("//", 0);
  t("// ", 0);
  t("//\n", 0);
  t("9//", 9);
  t("9 // x y\n", 9);
  t("//\n9", 9);
  t("// x\n9", 9);
  t("// x\n// y\n9", 9);
  t("var i; i = 9; // x y\n i", 9);
  t("9/**/", 9);
  t("9/* **/", 9);
  t("9/***/", 9);
  t("9/* x */", 9);
  t("9/* /* */", 9);
  t("9/* * / **/", 9);
  t("9 /* x \n y */\n", 9);
  t("/* */9", 9);
  t("/* */\n9", 9);
  t("// /* \n9", 9);
  t("/* // */9", 9);

  t("console.log(' DONE ')", 0);

  if (_errorCount) {
    printf("%d test(s) failed\n", _errorCount);
  } else {
    puts("All tests successful");
  }
  return _errorCount ? 1 : 0;
}
