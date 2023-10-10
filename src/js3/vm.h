#ifndef _include_vm_h
#define _include_vm_h

#include <stdlib.h> // size_t
#include <limits.h> // INT_MIN INT_MAX
#include <sys/types.h> // off_t

struct Object;

typedef struct Id {
  const char *s;
  size_t len;
  struct Object *h;
} Id;

typedef struct Prog {
  const char *s;
  const char *end;
  struct Object *h;
} Prog;

typedef struct Str {
  char *s;
  size_t len;
} Str;

struct List;

typedef struct List {
  struct List *next;
  char *key;
  struct Object *value;
} List;

typedef struct JsFun {
  Prog p;
  struct Object *scope;
} JsFun;

struct Parser;

typedef struct Object *(*Native)(struct Parser *, List *);
typedef struct Object *(*MethodFun)(struct Parser *, struct Object *, List *);

typedef struct Method {
  MethodFun f;
  struct Object *self;
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
  } V;
} Object;

typedef struct Parser {
  Prog prog;
  Object *ret;
  Object *thrw;
  Object *vars;

  const char *err;
  Id errName;
  const char *parseErr;

  int debug;
  int nest;
  int needSemicolon;

  char parseErrChar;
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
