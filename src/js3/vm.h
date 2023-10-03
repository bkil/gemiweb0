#ifndef _include_vm_h
#define _include_vm_h

#include <stdlib.h> // size_t
#include <limits.h> // INT_MIN INT_MAX

typedef struct Id {
  const char *s;
  size_t len;
} Id;

typedef struct Str {
  char *s;
  size_t len;
} Str;

typedef struct Object Object;

typedef struct List List;

typedef struct Parser Parser;

typedef struct List {
  List *next;
  char *key;
  Object *value;
} List;

typedef struct JsFun {
  const char *cs;
  Object *scope;
} JsFun;

typedef Object *(*Native)(Parser *, List *);
typedef Object *(*MethodFun)(Parser *, Object *, List *);

typedef struct Method {
  MethodFun f;
  Object *self;
} Method;

enum ObjectV {
  UndefinedObject,
  IntObject,
  StringObject,
  ConstStringObject,
  MapObject,
  FunctionJs,
  FunctionNative,
  MethodNative,
  NullObject,
  ArrayObject,
  NanObject
};

typedef struct Object {
  int ref;
  enum ObjectV t;
  union {
    int i;
    Str s;
    Id c;
    List *m;
    JsFun j;
    Native f;
    Method a;
  };
} Object;

typedef struct Parser {
  const char *prog;
  const char *progEnd;
  const char *parseErr;
  char parseErrChar;

  int debug;
  int nest;
  int needSemicolon;
  Object *ret;
  Object *thrw;
  Object *vars;
  const char *err;
  Id errName;
} Parser;

Parser *Parser_new(void);
int Parser_eval(Parser *p, const char *prog, size_t len, int debug);
void Parser_free(Parser *p);

static inline size_t
off_t2size_t(off_t x) {
  if (x < 0) {
    return 0;
  }
  return (size_t)x;
}

static inline int
off_t2int(off_t x) {
  if ((x < INT_MIN) || (x > INT_MAX)) {
    return 0;
  }
  return (int)x;
}

#endif
