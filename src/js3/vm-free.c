#include "vm.h"
#include <string.h> // strdup

static int
getCycles(Object *o) {
  if ((o->t != MapObject) && (o->t != ArrayObject) && (o->t != FunctionJs) && (o->t != MethodNative)) {
    return 0;
  } else if (o->ref == -2) {
    return 1;
  } else if (o->ref < 0) {
    return 0;
  }

  int savedRef = o->ref;
  o->ref = -2;
  int c = 0;

  if ((o->t == MapObject) || (o->t == ArrayObject)) {
    List *it = o->m;
    while (it) {
      c += getCycles(it->value);
      it = it->next;
    }
  } else if (o->t == FunctionJs) {
    c = getCycles(o->j.scope);
  } else if (o->t == MethodNative) {
    c = getCycles(o->a.self);
  }

  o->ref = savedRef;
  return c;
}

static void
List_free(List *list);

static void
Object_free(Object *o) {
  if (o->ref) {
    if (o->ref > 0) {
      o->ref--;
    }
    return;
  }

  if (o->t == StringObject) {
    free(o->s.s);
  } else if (o->t == ConstStringObject) {
    if (o->c.h) {
      Object_free(o->c.h);
    }
  } else if ((o->t == MapObject) || (o->t == ArrayObject)) {
    List_free(o->m);
  } else if (o->t == FunctionJs) {
    Object_free(o->j.scope);
    Object_free(o->j.p.h);
  } else if (o->t == MethodNative) {
    Object_free(o->a.self);
  }
  free(o);
}

static Object *
Object_ref(Object *o) {
  if (o->ref >= 0) {
    o->ref++;
  }
  return o;
}

static Object *
Object_clone(Object *o) {
  if (o->t != MapObject) {
    return Object_ref(o);
  }

  List *it = o->m;
  Object *d = MapObject_new();
  while (it) {
    d->m = List_new(d->m, strdup(it->key), Object_ref(it->value));
    it = it->next;
  }
  return d;
}

static void
List_free(List *list) {
  List *n;
  while (list) {
    n = list->next;
    free(list->key);
    if (list->value) {
      Object_free(list->value);
    }
    free(list);
    list = n;
  }
}

void
Parser_free(Parser *p) {
  Object_free(p->vars);
  free(p);
}
