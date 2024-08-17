#include "vm.h" /* Parser_eval Parser_free Parser_new */

#include <stdbool.h> /* bool false true */
#include <stdio.h> /* fprintf */
#include <string.h> /* strcmp */
#include <stdlib.h> /* free */

#define print1(format) fprintf(stderr, format)
#define print2(format, a) fprintf(stderr, format, a)
#define print3(format, a, b) fprintf(stderr, format, a, b)
#define print4(format, a, b, c) fprintf(stderr, format, a, b, c)

static bool _debug = false;
static unsigned int _errorCount = 0;

static int
__attribute__((nonnull, warn_unused_result))
test_case(const char *prog, const char *inp, char **out, bool debug) {
  struct Parser *p = Parser_new();
  int ret = Parser_eval(p, prog, inp, out, debug);
  Parser_free(p);
  return ret;
}

static void
__attribute__((nonnull(2, 4, 5)))
tio(const char *name, const char *code, int expectCell, const char *inp, const char *expectOut) {
  const char *title = name ? name : code;
  char *gotOut = 0;
  int fail = 0;
  int res;
  if (_debug) {
    print2("=testing: %s\n", title);
  }
  res = test_case(code, inp, &gotOut, _debug);
  if (res != expectCell) {
    if (_debug) {
      print1(" -fail: got ");
    } else {
      print2("fail: %s: got ", title);
    }
    if (res == -1) {
      print1("failure");
    } else {
      print2("v[i]=%d", res);
    }
    print1(", expected ");
    if (expectCell == -1) {
      print1("failure");
    } else {
      print2("v[i]=%d", expectCell);
    }
    print1("\n");
    fail = 1;
  }

  if (expectOut && strcmp(gotOut, expectOut)) {
    if (_debug) {
      print3(" -fail: got output \"%s\", expected \"%s\"\n", gotOut, expectOut);
    } else {
      print4("fail: %s: got output \"%s\", expected \"%s\"\n", title, gotOut, expectOut);
    }
    fail = 1;
  }
  free(gotOut);
  gotOut = 0;

  if (fail) {
    if (!_debug) {
      if (test_case(code, inp, &gotOut, 1)) {}
      free(gotOut);
      gotOut = 0;
    }
    _errorCount++;
  }
}

static void
__attribute__((nonnull))
t(const char *code, int cell) {
  tio(0, code, cell, "", "");
}

static void
__attribute__((nonnull))
fail(const char *code) {
  tio(0, code, -1, "", "");
}

static void
__attribute__((nonnull(2, 3, 4)))
fio(const char *name, const char *code, const char *inp, const char *expectOut) {
  tio(name, code, -1, inp, expectOut);
}

int
main(void) {
  fail("v[i]=(v[i]|0)+1");
  fail("var i;i=0;v[i]=(v[i]|0)+1");
  fail("var v;v=new Array;v[i]=(v[i]|0)+1");
  fail("while(v[i]){var v}");
  fail("var i;i=0;while(v[i]){var v}");
  fail("var v;v=new Array;while(v[i]){var i}");
  fio(0, "var i;i=0;var v;v=new Array;v[i]=form.text.value.charCodeAt(j)|0", "9", "");
  fio(0, "var i;i=0;var j;j=0;v[i]=form.text.value.charCodeAt(j)|0", "9", "");
  fio(0, "var j;j=0;var v;v=new Array;v[i]=form.text.value.charCodeAt(j)|0", "9", "");
  fail("var i;i=0;document.write(String.fromCharCode(v[i]))");
  fail("var v;v=new Array;document.write(String.fromCharCode(v[i]))");

  /* non-conforming */
  fio(0, "var i;i=0;var j;j=0;var v;v=new Array;v[i]=form.text.value.charCodeAt(j)|0;v[i]=form.text.value.charCodeAt(j)|0",
    "9", "");

  t("var v", 0);
  t("var v;v=new Array", 0);
  t("var i", 0);
  t("var i;i=0", 0);
  t("var j", 0);
  t("var j;j=0", 0);
  t("var i;i=0;var v;v=new Array", 0);
  t("var i;i=0;var v;v=new Array;v[i]=(v[i]|0)+1", 1);
  t("var i;i=0;var v;v=new Array;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)-1", 0);
  t("var i;i=0;var v;v=new Array;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1", 2);
  t("var i;i=0;var v;v=new Array;v[i]=(v[i]|0)+1;i++;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1", 2);
  t("var i;i=0;var v;v=new Array;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;i++;v[i]=(v[i]|0)+1;i--", 2);
  t("var i;i=0;var v;v=new Array;while(v[i]){v[i]=(v[i]|0)-1}", 0);
  t("var i;i=0;var v;v=new Array;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;while(v[i]){v[i]=(v[i]|0)-1}", 0);
  t("var i;i=0;var v;v=new Array;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;while(v[i]){i++;v[i]=(v[i]|0)+1;i--;v[i]=(v[i]|0)-1};i++",
    2);

  /* optional: out of project scope */
  t("  var i  ;  i=0 ; var v ; v=new Array ; while(v[i]){  v[i]=(v[i]|0)-1  }  ", 0);

  tio("3*3",
    "var i;i=0;var v;v=new Array;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;i++;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;i--;while(v[i]){i++;while(v[i]){i++;v[i]=(v[i]|0)+1;i++;v[i]=(v[i]|0)+1;i--;i--;v[i]=(v[i]|0)-1};i++;while(v[i]){i--;v[i]=(v[i]|0)+1;i++;v[i]=(v[i]|0)-1};i--;i--;v[i]=(v[i]|0)-1};i++;i++;i++",
    9, "", "");

  tio(0, "var i;i=0;var j;j=0;var v;v=new Array;v[i]=form.text.value.charCodeAt(j)|0",
    57, "9", "");

  tio("sum input characters",
    "var i;i=0;var j;j=0;var v;v=new Array;v[i]=form.text.value.charCodeAt(j)|0;j++;while(v[i]){while(v[i]){i++;v[i]=(v[i]|0)+1;i--;v[i]=(v[i]|0)-1};v[i]=form.text.value.charCodeAt(j)|0;j++};i++",
    102, "42", "");

  tio(0,
    "var i;i=0;var j;j=0;var v;v=new Array;v[i]=form.text.value.charCodeAt(j)|0;while(v[i]){v[i]=(v[i]|0)+1;document.write(String.fromCharCode(v[i]));j++;v[i]=form.text.value.charCodeAt(j)|0};document.close()",
    0, "42", "53");

/* 52 = '4', 50 = '2' */
  tio("print 42",
    "var i;i=0;var v;v=new Array;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;v[i]=(v[i]|0)+1;document.write(String.fromCharCode(v[i]));v[i]=(v[i]|0)-1;v[i]=(v[i]|0)-1;document.write(String.fromCharCode(v[i]))",
    50, "", "42");

  if (_errorCount) {
    print2("%d test(s) failed\n", _errorCount);
  } else {
    print1("All tests successful\n");
  }
  return _errorCount ? 1 : 0;
}
