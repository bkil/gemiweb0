#include "string.h" /* strdup */
#include "vm.h"

static int
__attribute__((nonnull, warn_unused_result))
getCycles0(Object *o, int backtrack) {
  if (o->ref == -2) {
    return 1;
  } else if (o->ref == -1) {
    return 0;
  }
  if (backtrack != (o->ref >> 30)) {
    return 0;
  }
  o->ref ^= 1 << 30;

  int savedRef = o->ref;
  o->ref = -2;
  int c = 0;

  switch (o->t) {
    case MapObject:
    case ArrayObject: {
      List *it = o->V.m;
      while (it) {
        if (getCycles0(it->value, backtrack)) {
          c = 1;
          break;
        }
        it = it->next;
      }
      break;
    }

    case FunctionJs:
      c = getCycles0(o->V.j.scope, backtrack);
      break;

    case UndefinedObject:
    case IntObject:
    case StringObject:
    case ConstStringObject:
    case FunctionNative:
    case MethodNative:
    case NullObject:
    case NanObject:
    case Prototype:
    default:
      break;
  }
  o->ref = savedRef;
  return c;
}

static int
__attribute__((pure, nonnull, warn_unused_result))
getCycles(Object *o) {
  int c = getCycles0(o, 0);
  if (getCycles0(o, 1)) {}
  return c;
}

static void
List_free(List *list);

static void
__attribute__((nonnull))
Object_free(Object *o) {
  if (o->ref) {
    if (o->ref > 0) {
      o->ref--;
    }
    return;
  }

  switch (o->t) {
    case StringObject:
      free(o->V.s.s);
      break;
    case ConstStringObject:
      if (o->V.c.h) {
        Object_free(o->V.c.h);
      }
      break;
    case MapObject:
    case ArrayObject:
    case Prototype:
      List_free(o->V.m);
      break;
    case FunctionJs:
      Object_free(o->V.j.scope);
      Object_free(o->V.j.p.h);
      break;
    case UndefinedObject:
    case IntObject:
    case FunctionNative:
    case MethodNative:
    case NullObject:
    case NanObject:
    default:
      {}
  }
  free(o);
}

static Object *
__attribute__((returns_nonnull, nonnull))
Object_ref(Object *o) {
  if (o->ref >= 0) {
    o->ref++;
  }
  return o;
}

static Object *
__attribute__((returns_nonnull, warn_unused_result, nonnull))
Object_clone(Object *o) {
  if (o->t != MapObject) {
    return Object_ref(o);
  }

  List *it = o->V.m;
  Object *d = MapObject_new();
  while (it) {
    d->V.m = List_new(d->V.m, strdup(it->key), Object_ref(it->value));
    it = it->next;
  }
  return d;
}

static void
List_free(List *list) {
  List *n;
  while (list) {
    n = list->next;
    if (list->key) {
      free(list->key);
    }
    if (list->value) {
      Object_free(list->value);
    }
    free(list);
    list = n;
  }
}

void
__attribute__((nonnull))
Parser_free(Parser *p) {
  List_free(p->objectPrototype->V.m);
  p->objectPrototype->V.m = 0;
  List_free(p->arrayPrototype->V.m);
  p->arrayPrototype->V.m = 0;
  List_free(p->stringPrototype->V.m);
  p->stringPrototype->V.m = 0;
  Object_free(p->vars);
  free(p);
}
