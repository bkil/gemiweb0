/* Copyright (C) 2023 bkil.hu
Refer to the GNU GPL v2 in LICENSE for terms */

#ifndef _include_vm_impl_h
#define _include_vm_impl_h

#include "vm.h"

typedef struct MutStr {
  char *s;
  size_t len;
  size_t storage;
  unsigned char concats;
} MutStr;

typedef struct Str {
  char *s;
  size_t len;
} Str;

struct Object;

typedef struct Id {
  const char *s;
  size_t len;
  struct Object *h;
} Id;

typedef struct Mmap {
  char *s;
  size_t len;
  int fd;
} Mmap;

struct List;

typedef struct List {
  struct List *next;
  char *key;
  struct Object *value;
} List;

typedef struct Prog {
  const char *s;
  const char *end;
  struct Object *h;
} Prog;

typedef struct JsFun {
  Prog p;
  struct Object *scope;
} JsFun;

typedef struct Object *(*Native)(struct Parser *, List *);
typedef struct Object *(*MethodFun)(struct Parser *, struct Object *, List *);

enum ObjectV {
  UndefinedObject,
  IntObject,
  StringObject,
  ConstStringObject,
  MmapString,
  MapObject,
  FunctionJs,
  FunctionNative,
  MethodNative,
  NullObject,
  ArrayObject,
  NanObject,
  DateObject,
  Prototype
};

typedef struct Object {
  int ref;
  enum ObjectV t;
  union {
    int i;
    Str s;
    MutStr u;
    Id c;
    Mmap mm;
    List *m;
    JsFun j;
    Native f;
    MethodFun a;
    long d;
  } V;
} Object;

typedef struct Parser {
  Prog prog;
  Object *ret;
  Object *thrw;
  Object *vars;

  Object *objectPrototype;
  Object *arrayPrototype;
  Object *stringPrototype;
  Object **stringConcatLhs;
  Object *onStdinData;
  Object *onStdinEnd;
  Object *onTimeout;
  Object *connClient;
  Object *connOptions;
  Object *onConnData;
  Object *onConnEnd;
  Object *onConnError;
  long int timeoutMs;

  const char *err;
  Id errName;
  const char *parseErr;

  size_t stringConcatOldLen;
  size_t stringConcatOldStorage;
  size_t stringConcatOldOfs;
  int sock;
  int debug;
  int nest;
  int needSemicolon;
  unsigned char stringConcatOldConcat;

  char parseErrChar;
} Parser;

#endif
