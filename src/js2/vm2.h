#ifndef _include_vm2_h
#define _include_vm2_h

#include <stdlib.h> // size_t

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

typedef Object *(*Native)(Parser *p, Object *);

enum ObjectV {
  UndefinedObject,
  IntObject,
  StringObject,
  ConstStringObject,
  MapObject,
  FunctionJs,
  FunctionNative,
  NullObject,
  ArrayObject
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
  };
} Object;

typedef struct Parser {
  const char *prog;
  const char *parseErr;
  char parseErrChar;

  int nest;
  int needSemicolon;
  Object *ret;
  Object *thrw;
  Object *vars;
  const char *err;
  Id errName;
} Parser;

Parser *Parser_new(void);
int Parser_eval(Parser *p, const char *prog);
void Parser_free(Parser *p);

#endif
