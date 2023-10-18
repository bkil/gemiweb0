#include "string.h" /* strnlen strdup strndup getline; strlen strcmp strncmp strncpy strstr */
#include "vm-impl.h"

#include <stdio.h> /* fputs fputc putchar stdout stderr getline */
#include <malloc.h> /* malloc free */
#include <stdlib.h> /* atoi size_t */

static void
__attribute__((nonnull))
putsn(const char *s, size_t len, FILE *out) {
  while (len-- && *s) {
    fputc(*(s++), out);
  }
}

static void
__attribute__((nonnull))
showProg(Parser *p) {
  const size_t left = off_t2size_t(p->prog.end - p->prog.s);
  putsn(p->prog.s, left < 32 ? left : 32, stderr);
  fputs("\n", stderr);
}

#ifdef SMALLBIN
# include "vm-smallbin.c"
# define NEEDLEAK

#else

# include <stdio.h> /* snprintf */

static int
__attribute__((nonnull))
snprinti(char *s, size_t n, int i) {
  return snprintf(s, n, "%d", i);
}

# ifdef SIMPLE
#  define NEEDLEAK
# endif
#endif

#ifdef NEEDLEAK
# define getCycles(o) (0)
# define Object_ref(o) (o)
# define Object_clone(o) (o)
# define mfree(o) while(0) {}
# define Object_free(o) while(0) {}
# define List_free(l) while(0) {}

void
__attribute__((const))
Parser_free(Parser *p) {
}

# else

static Object *MapObject_new(void);
List *List_new(List *next, char *key, Object *value);
# define mfree(o) free(o)

# include "vm-free.c"
#endif

static void
__attribute__((nonnull))
clearErr(Parser *p) {
  p->parseErr = 0;
  p->parseErrChar = 0;
}

static Object *
__attribute__((nonnull(1)))
setRunError(Parser *p, const char *message, const Id *id) {
  p->err = message;
  p->errName = id ? *id : (Id){0};
  return 0;
}

#ifdef NEEDLEAK
static
#endif
List *
__attribute__((malloc, returns_nonnull, warn_unused_result, nonnull(3)))
List_new(List *next, char *key, Object *value) {
  List *l = malloc(sizeof(*l));
  l->next = next;
  l->key = key;
  l->value = value;
  return l;
}

static Object undefinedObject = {.ref = -1, .t = UndefinedObject, .V.i = 0};
static Object nullObject = {.ref = -1, .t = NullObject, .V.i = 0};
static Object nanObject = {.ref = -1, .t = NanObject, .V.i = 0};
static Object emptyString = {.ref = -1, .t = ConstStringObject, .V.c = {.len = 0, .s = ""}};

static Object *
__attribute__((malloc, returns_nonnull, warn_unused_result))
IntObject_new(int x) {
  Object *o = malloc(sizeof(*o));
  o->ref = 0;
  o->t = IntObject;
  o->V.i = x;
  return o;
}

static Object *
__attribute__((malloc, returns_nonnull, warn_unused_result))
StringObject_new_str(Str s) {
  Object *o = malloc(sizeof(*o));
  o->ref = 0;
  o->t = StringObject;
  o->V.s = (Str){.s = s.s, .len = s.len};
  return o;
}

static Object *
__attribute__((malloc, returns_nonnull, warn_unused_result))
StringObject_new_const(Id s) {
  Object *o = malloc(sizeof(*o));
  o->ref = 0;
  o->t = ConstStringObject;
  o->V.c = (Id){.s = s.s, .len = s.len, .h = s.h ? Object_ref(s.h) : 0};
  return o;
}

static Object *
__attribute__((malloc, returns_nonnull, warn_unused_result, nonnull))
StringObject_new(const char *s) {
  Object *o = malloc(sizeof(*o));
  o->ref = 0;
  o->t = ConstStringObject;
  o->V.c = (Id){.s = s, .len = strlen(s), .h = 0};
  return o;
}

static Object *
__attribute__((malloc, returns_nonnull, warn_unused_result))
StringObject_new_char(char c) {
  Str s = {.s = 0, .len = 1};
  s.s = malloc(2);
  s.s[0] = c;
  s.s[1] = 0;
  return StringObject_new_str(s);
}

static Object *
__attribute__((malloc, returns_nonnull, warn_unused_result, nonnull))
FunctionJs_new(Parser *p) {
  Object *o = malloc(sizeof(*o));
  o->ref = 0;
  o->t = FunctionJs;
  o->V.j = (JsFun){.p = {.s = p->prog.s, .end = p->prog.end, .h = Object_ref(p->prog.h)}, .scope = Object_clone(p->vars)};
  return o;
}

static Object *
__attribute__((malloc, returns_nonnull, warn_unused_result))
FunctionNative_new(Native f) {
  Object *o = malloc(sizeof(*o));
  o->ref = 0;
  o->t = FunctionNative;
  o->V.f = f;
  return o;
}

static Object *
__attribute__((malloc, returns_nonnull, warn_unused_result))
MethodNative_new(MethodFun a) {
  Object *o = malloc(sizeof(*o));
  o->ref = 0;
  o->t = MethodNative;
  o->V.a = a;
  return o;
}

static
Object *
__attribute__((malloc, returns_nonnull, warn_unused_result))
MapObject_new(void) {
  Object *o = malloc(sizeof(*o));
  o->ref = 0;
  o->t = MapObject;
  o->V.m = 0;
  return o;
}

static
Object *
__attribute__((malloc, returns_nonnull, warn_unused_result))
Prototype_new(void) {
  Object *o = malloc(sizeof(*o));
  o->ref = 0;
  o->t = Prototype;
  o->V.m = 0;
  return o;
}

static Object *
__attribute__((malloc, returns_nonnull, warn_unused_result))
ArrayObject_new(void) {
  Object *o = malloc(sizeof(*o));
  o->ref = 0;
  o->t = ArrayObject;
  o->V.m = 0;
  return o;
}

static void
__attribute__((nonnull(2, 3)))
Map_set(List **list, char *key, Object *value) {
  if (!list) {
    return;
  }
  List *it = *list;
  while (it && it->key) {
    if (!strcmp(key, it->key)) {
      Object_free(it->value);
      it->value = Object_ref(value);
      mfree(key);
      return;
    }
    it = it->next;
  }
  *list = List_new(*list, key, Object_ref(value));
}

static void
__attribute__((nonnull(2, 3)))
Map_set_const(List **list, const char *s, Object *value) {
  Map_set(list, strdup(s), value);
}

static void
__attribute__((nonnull(2, 3)))
Map_set_id(List **list, Id *id, Object *value) {
  Map_set(list, strndup(id->s, id->len), value);
}

static int
__attribute__((pure, nonnull, warn_unused_result))
strncmpEq(Id id, const char *s) {
  return !strncmp(id.s, s, id.len) && !s[id.len];
}

static List *
__attribute__((pure, warn_unused_result))
Map_get(List *list, Id id) {
  List *it = list;
  while (it && it->key && it->value) {
    if (strncmpEq(id, it->key)) {
      return it;
    }
    it = it->next;
  }

  if (!id.len) {
    return 0;
  }
  it = Map_get(list, (Id){.s = "", .len = 0});
  if (!it || (it->value->t != MapObject)) {
    return 0;
  }
  return Map_get(it->value->V.m, id);
}

static List *
__attribute__((pure, warn_unused_result))
Map_get_str(List *list, Str s) {
  return Map_get(list, (Id){.s = s.s, .len = s.len});
}

static int
__attribute__((pure, warn_unused_result))
List_length(List *list) {
  int n = 0;
  for (; list; list = list->next, n++) {}
  return n;
}

static int
__attribute__((pure, nonnull, warn_unused_result))
isString(Object *o) {
  return (o->t == StringObject) || (o->t == ConstStringObject);
}

static int
__attribute__((pure, nonnull, warn_unused_result))
isStringEq(Object *a, Object *b) {
  return isString(a) && isString(b) && (a->V.c.len == b->V.c.len) && (!strncmp(a->V.c.s, b->V.c.s, a->V.c.len));
}

static Object *
__attribute__((returns_nonnull, warn_unused_result, nonnull(1, 2)))
String_indexOf(Parser *p, Object *self, List *l) {
  Object *a = l ? l->value : &undefinedObject;
  if (!isString(a)) {
    return &undefinedObject;
  }
  char *haystack = strndup(self->V.c.s, self->V.c.len);
  char *needle = strndup(a->V.c.s, a->V.c.len);
  char *start = strstr(haystack, needle);
  int index = start ? off_t2int(start - haystack + 1) - 1 : -1;
  mfree(haystack);
  mfree(needle);
  return IntObject_new(index);
}

static char
__attribute__((pure, nonnull, warn_unused_result))
String_getCharCode(Object *self, Object *x) {
  int i = x->t == IntObject ? x->V.i : 0;
  return (i >= 0) && (i < (int)self->V.c.len) ? self->V.c.s[i] : -1;
}

static Object *
__attribute__((returns_nonnull, warn_unused_result, nonnull(1, 2)))
String_charCodeAt(Parser *p, Object *self, List *l) {
  char c = String_getCharCode(self, l ? l->value : &undefinedObject);
  return c < 0 ? &nanObject : IntObject_new(c);
}

static Object *
__attribute__((returns_nonnull, warn_unused_result, nonnull))
String_charAt_obj(Object *self, Object *x) {
  char c = String_getCharCode(self, x);
  return c < 0 ? &emptyString : StringObject_new_char(c);
}

static Object *
__attribute__((returns_nonnull, warn_unused_result, nonnull(1, 2)))
String_charAt(Parser *p, Object *self, List *l) {
  return String_charAt_obj(self, l ? l->value : &undefinedObject);
}

static int
__attribute__((pure, nonnull, warn_unused_result))
isTrue(Object *o) {
  return ((o->t == IntObject) && o->V.i) || (isString(o) && o->V.c.len) || (o->t == MapObject) || (o->t == ArrayObject) || (o->t == FunctionJs) || (o->t == FunctionNative) || (o->t == MethodNative);
}

static Object *
__attribute__((nonnull, warn_unused_result))
Object_toString(Object *o) {
  switch (o->t) {
    case IntObject: {
      char *s = malloc(16);
      int len = snprinti(s, 16, o->V.i);
      if ((len > 0) && (len < 16)) {
        return StringObject_new_str((Str){.s = s, .len = (size_t)len});
      } else {
        mfree(s);
        break;
      }
    }

    case UndefinedObject:
      return StringObject_new("undefined");

    case StringObject:
      return Object_ref(o);

    case ConstStringObject:
      return Object_ref(o);

    case MapObject:
    case Prototype:
      return StringObject_new("Object");

    case ArrayObject:
      return StringObject_new("Array");

    case FunctionJs:
      return StringObject_new("Function");

    case FunctionNative:
      return StringObject_new("Native");

    case MethodNative:
      return StringObject_new("Method");

    case NullObject:
      return StringObject_new("null");

    case NanObject:
      return StringObject_new("NaN");

    default: {}
  }
  return 0; /* unreachable unless memory corruption */
}

static Object *
__attribute__((nonnull, warn_unused_result))
typeOf(Object *o) {
  switch (o->t) {
    case IntObject:
    case NanObject:
      return StringObject_new("number");

    case UndefinedObject:
      return StringObject_new("undefined");

    case StringObject:
    case ConstStringObject:
      return StringObject_new("string");

    case MapObject:
    case ArrayObject:
    case NullObject:
    case Prototype:
      return StringObject_new("object");

    case FunctionJs:
    case FunctionNative:
    case MethodNative:
      return StringObject_new("function");

    default:
      return 0; /* unreachable unless memory corruption */
  }
}

static Object *
__attribute__((nonnull, warn_unused_result))
String_concat(Object *t1, Object *t2) {
  if (!isString(t1) || !isString(t2)) {
    return 0;
  }
  const size_t n = t1->V.s.len;
  const size_t m = t2->V.s.len;
  char *s = malloc(n + m + 1);
  strncpy(s, t1->V.s.s, n);
  strncpy(s + n, t2->V.s.s, m + 1);
  return StringObject_new_str((Str){.s = s, .len = n + m});
}


static int
__attribute__((nonnull, warn_unused_result))
accept(Parser *p, char c) {
  if ((p->prog.s < p->prog.end) && (*p->prog.s == c)) {
    p->prog.s++;
    return 1;
  }
  return 0;
}

static int
__attribute__((nonnull, warn_unused_result))
expect(Parser *p, char c) {
  if (accept(p, c)) {
    return 1;
  }
  p->parseErr = "expected different character";
  p->parseErrChar = c;
  return 0;
}

static int
__attribute__((nonnull))
skipWs(Parser *p) {
  int ret = 0;
  while (1) {
    while ((p->prog.s < p->prog.end) && ((*p->prog.s == ' ') || (*p->prog.s == '\n'))) {
      p->prog.s++;
      ret = 1;
    }
    if ((p->prog.end - p->prog.s < 2) || (*p->prog.s != '/')) {
      break;
    }
    if (p->prog.s[1] == '/') {
      p->prog.s += 2;
      ret = 1;
      while ((p->prog.s < p->prog.end) && (*p->prog.s != '\n')) {
        p->prog.s++;
      }
    } else if (p->prog.s[1] == '*') {
      p->prog.s += 2;
      ret = 1;
      while (p->prog.s < p->prog.end) {
        if ((p->prog.end - p->prog.s >= 2) && (*p->prog.s == '*') && (p->prog.s[1] == '/')) {
          p->prog.s += 2;
          break;
        }
        p->prog.s++;
      }
    } else {
      break;
    }
  }
  return ret;
}

static int
__attribute__((nonnull, warn_unused_result))
acceptWs(Parser *p, char c) {
  skipWs(p);
  return accept(p, c);
}

static int
__attribute__((nonnull, warn_unused_result))
expectWs(Parser *p, char c) {
  skipWs(p);
  return expect(p, c);
}

static int
__attribute__((nonnull, warn_unused_result))
parseId(Parser *p, Id *id) {
  skipWs(p);
  const char *s = p->prog.s;
  char c = s < p->prog.end ? *s : 0;
  if ((c == '_') || ((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z'))) {
    do {
      s++;
      c = s < p->prog.end ? *s : 0;
    } while ((c == '_') || ((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || ((c >= '0') && (c <= '9')));
  }
  size_t len = off_t2size_t(s - p->prog.s);
  if (len) {
    *id = (Id){.s = p->prog.s, .len = len, .h = p->prog.h};
    p->prog.s += len;
    return 1;
  }
  p->parseErr = "expected keyword or identifier";
  return 0;
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseIntLit(Parser *p) {
  skipWs(p);

  const char *s = p->prog.s;
  char c = s < p->prog.end ? *s : 0;
  if (c == '-') {
    s++;
    c = s < p->prog.end ? *s : 0;
  }
  const char *digitStart = s;
  while ((c >= '0') && (c <= '9')) {
    s++;
    c = s < p->prog.end ? *s : 0;
  }
  size_t len = off_t2size_t(s - p->prog.s);
  size_t digits = off_t2size_t(s - digitStart);
  if (!digits || (c == '_') || (c == '.') || ((c >= 'A' && (c <= 'Z'))) || ((c >= 'a') && (c <= 'z'))) {
    return 0;
  }

  if (p->nest) {
    p->prog.s = s;
    return &undefinedObject;
  }
  int x;
  if (s < p->prog.end) {
    x = atoi(p->prog.s);
  } else {
    char *t = strndup(p->prog.s, len);
    x = atoi(t);
    mfree(t);
  }
  p->prog.s = s;
  return IntObject_new(x);
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseStringLit(Parser *p) {
  skipWs(p);
  char c;
  if (!acceptWs(p, c = '\'') && !acceptWs(p, c = '"')) {
    return 0;
  }
  Id id = {.s = p->prog.s, .len = 0, .h = p->prog.h};
  while ((p->prog.s < p->prog.end) && (*p->prog.s != c) && (*p->prog.s != '\\')) {
    p->prog.s++;
    id.len++;
  }
  if (!expectWs(p, c)) {
    return 0;
  }
  if (p->nest) {
    return &undefinedObject;
  }
  return StringObject_new_const(id);
}

static Object *
parseExpr(Parser *p);

static Object *
__attribute__((nonnull, warn_unused_result))
parseIndex(Parser *p) {
  skipWs(p);
  if (accept(p, '[')) {
    Object *o = parseExpr(p);
    if (o) {
      if (expectWs(p, ']')) {
        return o;
      }
      Object_free(o);
    }
  } else if (accept(p, '.')) {
    Id id;
    if (parseId(p, &id)) {
      return StringObject_new_const(id);
    }
    p->parseErr = "expecting field name";
  }
  return 0;
}

static Object *
parseBody(Parser *p);

static Object *
parseBlock(Parser *p);

static Object *
__attribute__((nonnull(1), warn_unused_result))
parseFunction(Parser *p, List *arg) {
  if (!acceptWs(p, ')')) {
    Id id;
    do {
      if (!parseId(p, &id)) {
        return 0;
      }
      if (!p->nest) {
        if (arg) {
          Map_set_id(&p->vars->V.m, &id, arg->value);
          arg = arg->next;
        } else {
          Map_set_id(&p->vars->V.m, &id, &undefinedObject);
        }
      }
    } while (acceptWs(p, ','));
    if (!expectWs(p, ')')) {
      return 0;
    }
  }
  return parseBody(p);
}

static Object *
__attribute__((nonnull(1, 2), warn_unused_result))
invokeFun(Parser *p, Object *o, List *args, Object *self) {
  if (o->t == FunctionJs) {
    Prog ret = p->prog;
    p->prog = o->V.j.p;
    Object *caller = p->vars;
    p->vars = MapObject_new();
    if (self) {
      Map_set_const(&p->vars->V.m, "this", self);
    }
    Map_set_const(&p->vars->V.m, "", o->V.j.scope);

    Object *res = parseFunction(p, args);
    Object_free(p->vars);
    p->vars = caller;

    if (p->ret) {
      res = p->ret;
      p->ret = 0;
    }
    if (res) {
      p->prog = ret;
      return res;
    }
  } else if (o->t == FunctionNative) {
    return (*o->V.f)(p, args);
  } else if ((o->t == MethodNative) && self) {
    return (*o->V.a)(p, self, args);
  } else {
    return setRunError(p, "not a function", 0);
  }
  return 0;
}

static Object *
__attribute__((nonnull(1), warn_unused_result))
parseRHS(Parser *p, List **parent, Object *key, List *e, Object *got, Object *self) {
  skipWs(p);

  const char *prog = p->prog.s;
  if (accept(p, '=') && !accept(p, '=')) {
    if (!key) {
      return setRunError(p, "expected a writable left hand side", 0);
    }
    if (!p->nest && e && (e->value->t == Prototype)) {
      return setRunError(p, "overwriting prototype unsupported", 0);
    }
    Object *r = 0;
    if ((r = parseExpr(p))) {
      if (!p->nest) {
        if (e) {
          Object_free(e->value);
          e->value = Object_ref(r);
        } else {
          *parent = List_new(*parent, strndup(key->V.s.s, key->V.s.len), Object_ref(r));
        }
        if (getCycles(r)) {
          if (e) {
            e->value = &undefinedObject;
          } else {
            (*parent)->value = &undefinedObject;
          }
          Object_free(r);
          Object_free(r);
          return setRunError(p, "reference cycles unsupported", 0);
        }
      }
    }
    return r;
  }
  p->prog.s = prog;

  Object *o = Object_ref(e ? e->value : got ? got : &undefinedObject);
  List *args = 0, *argsEnd = 0;
  if (accept(p, '(')) {
    if (!acceptWs(p, ')')) {
      do {
        Object *arg = parseExpr(p);
        if (!arg) {
          Object_free(o);
          List_free(args);
          return 0;
        }
        if (p->nest) {
          Object_free(arg);
        } else {
          List *l = List_new(0, 0, arg);
          if (argsEnd) {
            argsEnd->next = l;
          } else {
            args = l;
          }
          argsEnd = l;
        }
      } while (acceptWs(p, ','));
      if (!expectWs(p, ')')) {
        Object_free(o);
        List_free(args);
        return 0;
      }
    }
    if (p->nest) {
      Object_free(o);
      List_free(args);
      return &undefinedObject;
    }
    Object *f = o;
    o = invokeFun(p, f, args, self);
    Object_free(f);
    List_free(args);
  }

  return o;
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseSTerm(Parser *p, Id *id) {
  List **parent = &p->vars->V.m;
  Object *key = &undefinedObject;
  List *e = 0;
  Object *field = 0;
  Object *self = 0;

  if (p->nest) {
    parent = 0;
  } else if (!(e = Map_get(*parent, *id))) {
    return setRunError(p, "undefined variable", id);
  }

  Object *i;
  while ((i = parseIndex(p))) {
    if (p->nest) {
      Object_free(i);
    } else {
      if (key) {
        Object_free(key);
        key = 0;
      }
      if (e) {
        if (field) {
          Object_free(field);
        }
        field = Object_ref(e->value);
      }
      if (!field) {
        Object_free(i);
        return setRunError(p, "undefined object field", id);
      }
      self = field;
      field = 0;
      if (isString(self)) {
        if (isString(i)) {
          if (strncmpEq(i->V.c, "length")) {
            field = IntObject_new((int)self->V.c.len);
            Object_free(self);
            self = 0;
          } else {
            e = Map_get_str(p->stringPrototype->V.m, i->V.s);
            if (e) {
              field = Object_ref(e->value);
            } else {
              Object_free(self);
              self = 0;
            }
          }
        } else {
          field = String_charAt_obj(self, i);
          Object_free(self);
          self = 0;
        }
        Object_free(i);
        e = 0;

      } else if ((self->t == MapObject) || (self->t == ArrayObject) || (self->t == Prototype)) {
        parent = &self->V.m;
        key = Object_toString(i);
        Object_free(i);
        if (!key) {
          Object_free(self);
          return setRunError(p, "can't convert index to string", id);
        }
        if ((self->t == ArrayObject) && strncmpEq(key->V.c, "length")) {
          field = IntObject_new(List_length(self->V.m));
          Object_free(key);
          key = 0;
          e = 0;
          Object_free(self);
          self = 0;
        } else {
          Object *proto = self->t == MapObject ? p->objectPrototype : p->arrayPrototype;
          e = Map_get_str(*parent, key->V.s);
          if (e) {
            Object_free(self);
            self = 0;
          } else {
            e = Map_get_str(proto->V.m, key->V.s);
            if (e) {
              field = Object_ref(e->value);
              Object_free(key);
              key = 0;
              e = 0;
            } else {
              Object_free(self);
              self = 0;
            }
          }
        }

      } else {
        Object_free(self);
        Object_free(i);
        return setRunError(p, "not indexable", id);
      }
    }
  }
  if (p->err || p->parseErr) {
    return 0;
  }
  i = parseRHS(p, parent, key, e, field, self);
  if (key) {
    Object_free(key);
  }
  if (field) {
    Object_free(field);
  }
  if (self) {
    Object_free(self);
  }
  return i;
}

static Object *
parseTerm(Parser *p);

static Object *
__attribute__((nonnull, warn_unused_result))
parseITerm(Parser *p, Id *id) {
  if (strncmpEq(*id, "new")) {
    skipWs(p);
    if (!parseId(p, id)) {
      return 0;
    }
    if (strncmpEq(*id, "Object")) {
      return MapObject_new();
    } else if (strncmpEq(*id, "Array")) {
      return ArrayObject_new();
    }
    return setRunError(p, "can't instantiate class of", id);
  } else if (strncmpEq(*id, "typeof")) {
    Object *o = parseTerm(p);
    if (o && !p->nest) {
      Object *t = typeOf(o);
      Object_free(o);
      return t;
    }
    return o;
  } else if (strncmpEq(*id, "undefined")) {
    return &undefinedObject;
  } else if (strncmpEq(*id, "null")) {
    return &nullObject;
  } else if (strncmpEq(*id, "NaN")) {
    return &nanObject;
  } else if (strncmpEq(*id, "function")) {
    if (!expectWs(p, '(')) {
      return 0;
    }
    Object *o = &undefinedObject;
    if (!p->nest) {
      o = FunctionJs_new(p);
    }
    p->nest++;
    if (!parseFunction(p, 0)) {
      Object_free(o);
      return 0;
    }
    p->nest--;
    return o;
  }
  return parseSTerm(p, id);
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseLTerm(Parser *p) {
  char op = 0;
  Object *o;
  if ((o = parseIntLit(p))) {
    return o;
  } else if ((o = parseStringLit(p))) {
    return o;
  } else if (acceptWs(p, op = '!') || accept(p, op = '~') || accept(p, op = '-')) {
    if (!(o = parseTerm(p))) {
      return 0;
    }
    if (p->nest) {
      return o;
    }
    int v;
    if (op == '-') {
      if (o->t != IntObject) {
        return setRunError(p, "unary minus expects a number", 0);
      }
      v = -o->V.i;
    } else {
      v = op == '!' ? !isTrue(o) : o->t == IntObject ? ~o->V.i : ~isTrue(o);
    }
    Object *b = IntObject_new(v);
    Object_free(o);
    return b;
  } else if (acceptWs(p, '(')) {
    o = parseExpr(p);
    if (!o) {
      return 0;
    }
    if (!expectWs(p, ')')) {
      Object_free(o);
      return 0;
    }
    Object *r = parseRHS(p, 0, 0, 0, o, 0);
    Object_free(o);
    return r;
  }
  p->parseErr = "expected literal, negation, minus or parenthesized expression";
  return 0;
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseTerm(Parser *p) {
  Id id;
  if (parseId(p, &id)) {
    return parseITerm(p, &id);
  } else {
    clearErr(p);
    return parseLTerm(p);
  }
}

static Object *
__attribute__((nonnull(1), warn_unused_result))
parseEExpr(Parser *p, Object *t1) {
  if (!t1) {
    return 0;
  }
  clearErr(p);
  skipWs(p);

  char op;
  if (accept(p, op = '+')) {
  } else if (accept(p, op = '-')) {
  } else if (accept(p, op = '*')) {
  } else if (accept(p, op = '/')) {
  } else if (accept(p, op = '%')) {
  } else if (accept(p, op = '^')) {
  } else if (accept(p, op = '|')) {
    if (accept(p, '|')) {
      op = 'O';
    }
  } else if (accept(p, op = '&')) {
    if (accept(p, '&')) {
      op = 'A';
    }
  } else if (accept(p, op = '<')) {
    if (accept(p, '<')) {
      op = 'L';
    } else if (accept(p, '=')) {
      op = 'l';
    }
  } else if (accept(p, op = '>')) {
    if (accept(p, '>')) {
      if (accept(p, '>')) {
        op = 'r';
      } else {
        op = 'R';
      }
    } else if (accept(p, '=')) {
      op = 'g';
    }
  } else if (accept(p, op = '=')) {
    if (!expect(p, '=') || !expect(p, '=')) {
      Object_free(t1);
      return 0;
    }
  } else if (accept(p, op = '!')) {
    if (!expect(p, '=') || !expect(p, '=')) {
      Object_free(t1);
      return 0;
    }
  } else {
    return t1;
  }

  int sh = 0;
  int isBool = 1;
  switch (op) {
    case 'A':
      sh = !isTrue(t1);
      break;
    case 'O':
      sh = isTrue(t1);
      break;
    default:
      isBool = 0;
  }
  if (sh) {
    p->nest++;
  }

  Object *t2 = parseTerm(p);
  if (!t2) {
    Object_free(t1);
    return 0;
  }

  if (p->nest) {
    if (sh) {
      p->nest--;
    }
    Object_free(t2);
    return t1;
  }

  if (isBool) {
    Object_free(t1);
    switch (op) {
      case 'O':
        return t2;
      case 'A':
        return t2;
      default:
        Object_free(t2);
        return 0;
    }
  } else if ((t1->t == IntObject) && (t1->t == t2->t)) {
    int x = t1->V.i;
    int y = t2->V.i;
    Object_free(t1);
    Object_free(t2);
    switch (op) {
      case '+':
        return IntObject_new(x + y);
      case '-':
        return IntObject_new(x - y);
      case '*':
        return IntObject_new(x * y);
      case '/':
        return IntObject_new(x / y);
      case '%':
        return IntObject_new(x % y);
      case '^':
        return IntObject_new(x ^ y);
      case '|':
        return IntObject_new(x | y);
      case '&':
        return IntObject_new(x & y);
      case 'R':
        return IntObject_new(x >> y);
      case 'r':
        return IntObject_new((int)((unsigned int)x >> y));
      case 'L':
        return IntObject_new(x << y);
      case '<':
        return IntObject_new(x < y);
      case 'l':
        return IntObject_new(x <= y);
      case '>':
        return IntObject_new(x > y);
      case 'g':
        return IntObject_new(x >= y);
      case '=':
        return IntObject_new(x == y);
      case '!':
        return IntObject_new(x != y);
      default: {}
    }
    return 0;
  } else if ((op == '=') || (op == '!')) {
    int b = isStringEq(t1, t2) || (((t1->t == NullObject) || (t1->t == UndefinedObject)) && (t1->t == t2->t));
    Object_free(t1);
    Object_free(t2);
    return IntObject_new((op == '=') ? b : !b);
  } else if (op == '+') {
    Object *s = 0;
    if (isString(t1)) {
      s = t2;
      t2 = Object_toString(s);
      Object_free(s);
    } else if (isString(t2)) {
      s = t1;
      t1 = Object_toString(s);
      Object_free(s);
    }
    if (s) {
      Object *o = String_concat(t1, t2);
      Object_free(t1);
      Object_free(t2);
      return o;
    }
  }
  Object_free(t1);
  Object_free(t2);
  return setRunError(p, "unknown operand types for expression", 0);
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseIExpr(Parser *p, Id *id) {
  return parseEExpr(p, parseITerm(p, id));
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseLExpr(Parser *p) {
  return parseEExpr(p, parseLTerm(p));
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseExpr(Parser *p) {
  Id id;
  if (parseId(p, &id)) {
    return parseIExpr(p, &id);
  } else {
    clearErr(p);
    return parseLExpr(p);
  }
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseWhile(Parser *p) {
  if (!expectWs(p, '(')) {
    return 0;
  }

  const char *begin = p->prog.s;
  Object *o;
  int cond = 1;
  do {
    p->prog.s = begin;
    if (!(o = parseExpr(p)) || !expect(p, ')')) {
      return 0;
    }
    if (!p->nest) {
      if (!isTrue(o)) {
        p->nest++;
        cond = 0;
      }
    }
    Object_free(o);
    if (!(o = parseBlock(p))) {
      return 0;
    }
    Object_free(o);
    if (!cond) {
      p->nest--;
    }
  } while (!p->nest && cond);
  return &undefinedObject;
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseFor(Parser *p) {
  if (!expectWs(p, '(')) {
    return 0;
  }

  Id itName, word;
  Object *e;
  if (!parseId(p, &itName) || !parseId(p, &word) || !strncmpEq(word, "in") || !(e = parseExpr(p))) {
    return 0;
  }
  if (!p->nest && (e->t != MapObject)) {
    Object_free(e);
    return setRunError(p, "for can only iterate on Object", &itName);
  }
  if (!expectWs(p, ')')) {
    return 0;
  }

  List *l = e->V.m;
  int isEmpty = !l;
  if (isEmpty) {
    p->nest++;
  }

  skipWs(p);
  const char *begin = p->prog.s;
  do {
    p->prog.s = begin;
    Object *caller = 0;
    Object *o;
    if (!p->nest) {
      caller = p->vars;
      p->vars = MapObject_new();
      Map_set_const(&p->vars->V.m, "", caller);
      Map_set_id(&p->vars->V.m, &itName, o = StringObject_new(l->key));
      Object_free(o);
    }

    o = parseBody(p);
    if (caller) {
      Object_free(p->vars);
      p->vars = caller;
      l = l->next;
    }
    if (!o) {
      Object_free(e);
      return 0;
    }
    Object_free(o);
  } while (!p->nest && l);

  if (isEmpty) {
    p->nest--;
  }
  Object_free(e);
  return &undefinedObject;
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseIf(Parser *p) {
  Object *o;
  if (!expectWs(p, '(') || !(o = parseExpr(p))) {
    return 0;
  }
  int cond = !p->nest && isTrue(o);
  if (!cond) {
    p->nest++;
  }
  Object_free(o);
  if (!expectWs(p, ')') || !(o = parseBlock(p))) {
    return 0;
  }
  Object_free(o);
  if (!cond) {
    p->nest--;
  }

  const char *saved = p->prog.s;
  Id id;
  if (!parseId(p, &id)) {
    clearErr(p);
    return &undefinedObject;
  }

  if (!strncmpEq(id, "else")) {
    p->prog.s = saved;
    return &undefinedObject;
  }
  if (cond) {
    p->nest++;
  }
  if (!(o = parseBlock(p))) {
    return 0;
  }
  Object_free(o);
  if (cond) {
    p->nest--;
  }
  return &undefinedObject;
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseStatement(Parser *p) {
  Object *o = 0;
  Id id;
  p->needSemicolon = 1;

  if (parseId(p, &id)) {
    if (strncmpEq(id, "if")) {
      o = parseIf(p);
    } else if (strncmpEq(id, "while")) {
      o = parseWhile(p);
    } else if (strncmpEq(id, "for")) {
      o = parseFor(p);
    } else if (strncmpEq(id, "try")) {
      if (!(o = parseBody(p))) {
        return 0;
      }
      Object_free(o);
      if (!parseId(p, &id) || !strncmpEq(id, "catch") || !expectWs(p, '(') || !parseId(p, &id) || !expectWs(p, ')')) {
        return 0;
      }
      if (p->nest && p->thrw) {
        p->nest--;

        Object *caller = 0;
        if (!p->nest) {
          caller = p->vars;
          p->vars = MapObject_new();
          Map_set_const(&p->vars->V.m, "", caller);
          Map_set_id(&p->vars->V.m, &id, p->thrw);
        }
        Object_free(p->thrw);
        p->thrw = 0;
        if ((o = parseBody(p))) {
          Object_free(o);
          o = &undefinedObject;
        }
        if (caller) {
          Object_free(p->vars);
          p->vars = caller;
        }
      } else {
        p->nest++;
        if ((o = parseBody(p))) {
          Object_free(o);
          o = &undefinedObject;
        }
        p->nest--;
      }
    } else if (strncmpEq(id, "var")) {
      if (parseId(p, &id)) {
        if (acceptWs(p, '=')) {
          o = parseExpr(p);
        } else {
          o = &undefinedObject;
        }
        if (o) {
          if (!p->nest) {
            Map_set_id(&p->vars->V.m, &id, o);
          }
          Object_free(o);
          o = &undefinedObject;
        }
      }
    } else if (strncmpEq(id, "function")) {
      if (parseId(p, &id) && expectWs(p, '(')) {
        if (!p->nest) {
          Object *f = FunctionJs_new(p);
          Map_set_id(&p->vars->V.m, &id, f);
          Object_free(f);
        }
        p->nest++;
        if ((o = parseFunction(p, 0))) {
          p->nest--;
        }
      }
    } else if (strncmpEq(id, "return")) {
      if ((o = parseExpr(p)) && !p->nest) {
        p->ret = o;
        o = 0;
      }
    } else if (strncmpEq(id, "throw")) {
      if ((o = parseExpr(p)) && !p->nest) {
        p->thrw = o;
        p->nest++;
        o = &undefinedObject;
      }
    } else {
      o = parseIExpr(p, &id);
    }
  } else {
    clearErr(p);
    o = parseLExpr(p);
  }
  return o;
}

static int
__attribute__((pure, nonnull, warn_unused_result))
haveMore(Parser *p) {
  return !p->parseErr && (p->prog.s < p->prog.end);
}

static int
__attribute__((nonnull, warn_unused_result))
parseRequiredSemicolon(Parser *p) {
  skipWs(p);
  if (p->needSemicolon) {
    if (expect(p, ';')) {
      p->needSemicolon = 0;
    } else {
      return 0;
    }
  } else {
    if (accept(p, ';')) {
      p->needSemicolon = 0;
    }
  }
  return 1;
}

static void
__attribute__((nonnull))
parseOptionalSemicolon(Parser *p) {
  if (acceptWs(p, ';')) {
    p->needSemicolon = 0;
  }
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseStatements(Parser *p) {
  p->needSemicolon = 0;
  Object *o = &undefinedObject;
  skipWs(p);
  while (o && haveMore(p)) {
    Object_free(o);
    if (!parseRequiredSemicolon(p)) {
      return 0;
    }
    o = parseStatement(p);
    if (o) {
      parseOptionalSemicolon(p);
      skipWs(p);
    }
  }
  return o;
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseBodyInner(Parser *p) {
  p->needSemicolon = 0;
  Object *o;
  while (!acceptWs(p, '}')) {
    if (!parseRequiredSemicolon(p) || !(o = parseStatement(p))) {
      return 0;
    }
    Object_free(o);
    parseOptionalSemicolon(p);
  }
  p->needSemicolon = 0;
  return &undefinedObject;
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseBody(Parser *p) {
  if (!expectWs(p, '{')) {
    return 0;
  }
  return parseBodyInner(p);
}

static Object *
__attribute__((nonnull, warn_unused_result))
parseBlock(Parser *p) {
  if (acceptWs(p, '{')) {
    return parseBodyInner(p);
  }
  Object *o = parseStatement(p);
  parseOptionalSemicolon(p);
  return o;
}

static Object *
__attribute__((returns_nonnull, warn_unused_result, nonnull(1)))
Console_log(Parser *p, List *l) {
  Object *e = l ? l->value : &undefinedObject;
  Object *os = Object_toString(e);
  if (os) {
    putsn(os->V.s.s, os->V.s.len, stdout);
    Object_free(os);
  } else {
    fputs("?", stdout);
  }
  return &undefinedObject;
}

static Object *
__attribute__((returns_nonnull, warn_unused_result, nonnull(1)))
String_fromCharCode(Parser *p, List *l) {
  Object *e = l ? l->value : &undefinedObject;
  char c = 0;
  if ((e->t == IntObject) && (e->V.i >= 0) && (e->V.i < 128)) {
    c = (char)e->V.i;
  }
  return StringObject_new_char(c);
}

static Object *
__attribute__((nonnull(1), warn_unused_result))
process_stdin_on(Parser *p, List *l) {
  if (!l || !l->next || !isString(l->value) || !strncmpEq(l->value->V.c, "data")) {
    return 0;
  }
  size_t all = 0;
  Str s = {.s = 0};
  ssize_t len = getline(&s.s, &all, stdin);
  Object *arg;
  len--;
  if (len < 0) {
    mfree(s.s);
    arg = &undefinedObject;
  } else {
    s.len = (size_t)len;
    arg = StringObject_new_str(s);
  }
  List *args = List_new(0, 0, arg);
  Object *o = invokeFun(p, l->next->value, args, 0);
  List_free(args);
  return o;
}

static Object *
__attribute__((returns_nonnull, warn_unused_result, nonnull(1)))
global_isNaN(Parser *p, List *l) {
  return IntObject_new(l ? l->value->t == NanObject : 0);
}

static void
__attribute__((nonnull))
addField(Object *o, const char *key, Object *v) {
  Map_set_const(&o->V.m, key, v);
  Object_free(v);
}

static void
__attribute__((nonnull))
addFunction(Object *o, const char *key, Native f) {
  addField(o, key, FunctionNative_new(f));
}

static void
__attribute__((nonnull))
addMethod(Object *o, const char *key, MethodFun a) {
  addField(o, key, MethodNative_new(a));
}

static Object *
global_eval(Parser *p, List *l);

static Object *
global_eval2(Parser *p, List *l);

static Object *
__attribute__((nonnull, returns_nonnull, warn_unused_result))
addPrototype(Object *parent) {
  Object *o = Prototype_new();
  addField(parent, "prototype", o);
  return o;
}

Parser *
Parser_new(void) {
  Parser *p = malloc(sizeof(*p));
  p->vars = MapObject_new();

  Object *con = MapObject_new();
  addFunction(con, "log", &Console_log);
  addField(p->vars, "console", con);

  Object *s = MapObject_new();
  addFunction(s, "fromCharCode", &String_fromCharCode);
  p->stringPrototype = addPrototype(s);
  addMethod(p->stringPrototype, "indexOf", &String_indexOf);
  addMethod(p->stringPrototype, "charCodeAt", &String_charCodeAt);
  addMethod(p->stringPrototype, "charAt", &String_charAt);
  addField(p->vars, "String", s);

  Object *o = MapObject_new();
  p->objectPrototype = addPrototype(o);
  addField(p->vars, "Object", o);

  Object *a = MapObject_new();
  p->arrayPrototype = addPrototype(a);
  addField(p->vars, "Array", a);

  Object *ps = MapObject_new();
  addFunction(ps, "on", &process_stdin_on);
  Object *pr = MapObject_new();
  addField(pr, "stdin", ps);
  addField(p->vars, "process", pr);

  addFunction(p->vars, "isNaN", &global_isNaN);
  addFunction(p->vars, "eval", &global_eval);
  addFunction(p->vars, "eval2", &global_eval2);
  return p;
}

static Parser *
__attribute__((malloc, returns_nonnull, warn_unused_result, nonnull))
Parser_new_vars(Object *vars) {
  Parser *p = Parser_new();
  addField(vars, "", p->vars);
  p->vars = Object_ref(vars);
  return p;
}

static void
__attribute__((nonnull))
showParseError(Parser *p) {
  if (p->debug) {
    fputs("parse error: ", stderr);
    if (p->parseErr) {
      fputs(p->parseErr, stderr);
      if (p->parseErrChar) {
        fputs(" ( '", stderr);
        fputc(p->parseErrChar, stderr);
        fputs("' )", stderr);
      }
    }
    fputs("\n", stderr);
    showProg(p);
  }
}

static void
__attribute__((nonnull))
showRunError(Parser *p) {
  if (p->debug) {
    fputs("runtime error: ", stderr);
    if (p->err) {
      fputs(p->err, stderr);
      if (p->errName.s) {
        fputs(" - ", stderr);
        putsn(p->errName.s, p->errName.len, stderr);
      }
    }
    fputs("\n", stderr);
    showProg(p);
  }
}

static Object *
__attribute__((nonnull, warn_unused_result))
Parser_evalString(Parser *p, Object *prog) {
  p->prog = (Prog){.s = prog->V.c.s, .end = prog->V.c.s + prog->V.c.len, .h = prog};
  p->err = 0;
  p->nest = 0;
  p->ret = 0;
  p->thrw = 0;
  p->needSemicolon = 0;
  clearErr(p);

  return parseStatements(p);
}

static Object *
__attribute__((nonnull, warn_unused_result))
Parser_evalWithThrow(Parser *p, Object *prog) {
  Object *o = Parser_evalString(p, prog);
  Object *thrw = 0;
  if (p->ret) {
    Object_free(p->ret);
    p->ret = 0;
    if (!p->thrw) {
      thrw = StringObject_new("eval: return outside function");
    }
  } else if (!o && !p->thrw) {
    if (p->parseErr || !p->err) {
      thrw = StringObject_new("eval: parse error");
      showParseError(p);
    } else {
      thrw = StringObject_new("eval: runtime error");
      showRunError(p);
    }
  }
  clearErr(p);
  setRunError(p, 0, 0);
  if (thrw) {
    p->thrw = thrw;
    p->nest++;
    if (o) {
      Object_free(o);
    }
    o = &undefinedObject;
  }
  return o;
}

static Object *
__attribute__((nonnull(1), warn_unused_result))
global_eval(Parser *p, List *l) {
  if (!l || !isString(l->value)) {
    return setRunError(p, "expecting String argument", 0);
  }
  Prog prog = p->prog;
  Object *o = Parser_evalWithThrow(p, l->value);
  p->prog = prog;
  return o;
}

static Object *
__attribute__((nonnull(1), warn_unused_result))
global_eval2(Parser *p, List *l) {
  if (!l || (l->value->t != MapObject) || !l->next || !isString(l->next->value)) {
    return setRunError(p, "expecting an Object and a String argument", 0);
  }
  Parser *q = Parser_new_vars(l->value);
  q->debug = p->debug;
  Object *o = Parser_evalWithThrow(q, l->next->value);
  if (q->thrw) {
    p->thrw = q->thrw;
    p->nest++;
  }
  Parser_free(q);
  if (!o) {
    o = &undefinedObject;
  }
  return o;
}

int
Parser_eval(Parser *p, const char *prog, size_t len, int debug) {
  p->debug = debug;
  Object *s = StringObject_new_const((Id){.s = prog, .len = len, .h = 0});
  Object *o = Parser_evalString(p, s);
  addField(p->vars, "", s);

  if (o) {
    int ret;
    if (p->thrw) {
      if (p->debug) {
        Object *os = Object_toString(p->thrw);
        fputs("runtime error: exception\n", stderr);
        putsn(os->V.s.s, os->V.s.len, stderr);
        Object_free(os);
        fputs("\n", stderr);
      }
      Object_free(p->thrw);
      p->thrw = 0;
      ret = -2;
    } else {
      ret = o->t != IntObject ? isTrue(o) : o->V.i > 0 ? o->V.i : 0;
    }
    Object_free(o);
    return ret;
  }

  if (p->ret) {
    Object_free(p->ret);
    p->ret = 0;
    if (p->debug) {
      fputs("runtime error: return outside function", stderr);
    }
    return -2;
  }

  if (p->thrw) {
    Object_free(p->thrw);
    p->thrw = 0;
  }
  if (p->parseErr || !p->err) {
    showParseError(p);
    return -1;
  } else {
    showRunError(p);
    return -2;
  }
}
