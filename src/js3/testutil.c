#include "vm.h"
#include "testutil.h"
#include <stdio.h> /* fprintf */
#include <string.h> /* strlen */

#define print(format, ...) fprintf(stderr, format, ##__VA_ARGS__)

static unsigned int _errorCount = 0;
static unsigned int _okCount = 0;
static bool _debug = false;

static int
__attribute__((nonnull, warn_unused_result))
runTestCase(const char *prog, bool debug) {
  struct Parser *p = Parser_new();
  int res = Parser_eval(p, prog, strlen(prog), debug);
  Parser_free(p);
  return res;
}

static int
__attribute__((nonnull, warn_unused_result))
runTestEventLoop(const char *prepare, const char *after, bool debug) {
  struct Parser *p = Parser_new();
  int res = Parser_eval(p, prepare, strlen(prepare), debug);
  if (res >= 0) {
    res = Parser_eventLoop(p, after, strlen(after), debug);
  }
  Parser_free(p);
  return res;
}

void
testEventLoop(const char *prepare, const char *after, int expect) {
  if (_debug) {
    print("=testing: \"%s\" ;; \"%s\"\n", prepare, after);
  }
  int res = runTestEventLoop(prepare, after, _debug);
  if (res != expect) {
    if (_debug) {
      print(" -fail: got %d, expected %d\n", res, expect);
    } else {
      print("fail: \"%s\" ;; \"%s\": got %d, expected %d\n", prepare, after, res, expect);
      if (runTestEventLoop(prepare, after, true)) {}
    }
    _errorCount++;
  } else {
    _okCount++;
  }
}

void
t3(const char *code, int expect, const char *name) {
  const char *title = name ? name : code;
  if (_debug) {
    print("=testing: %s\n", title);
  }
  int res = runTestCase(code, _debug);
  if (res != expect) {
    if (_debug) {
      print(" -fail: got %d, expected %d\n", res, expect);
    } else {
      print("fail: \"%s\": got %d, expected %d\n", title, res, expect);
      if (runTestCase(code, true)) {}
    }
    _errorCount++;
  } else {
    _okCount++;
  }
}

void
t(const char *code, int expect) {
  t3(code, expect, 0);
}

void
te(const char *prepare, const char *after, int expect) {
  testEventLoop(prepare, after, expect);
}

int
exitWithErrorCount(const char *kind) {
  if (_errorCount) {
    print("%d %s test(s) failed\n", _errorCount, kind);
  } else {
    print("All %d %s tests successful%s\n", _okCount, kind, "");
  }
  return _errorCount ? 1 : 0;
}

void
setDebug(bool debug) {
  _debug = debug;
}
