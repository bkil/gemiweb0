#include "include.h" /* strdup */
#include <stdio.h> /* perror */
#include <sys/mman.h> /* munmap */
#include <unistd.h> /* close */
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
    case MmapString:
    case FunctionNative:
    case MethodNative:
    case NullObject:
    case NanObject:
    case DateObject:
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
    case MmapString:
      /* coverage:file */
      if (munmap(o->V.mm.s, o->V.mm.len) < 0) {
        /* coverage:no */
        perror("munmap failed");
        /* /coverage:no */
      }
      if (close(o->V.mm.fd) < 0) {
        /* coverage:no */
        perror("mmap close failed");
        /* /coverage:no */
      }
      break;
      /* /coverage:file */
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
    case DateObject:
    default:
      {}
  }
  free(o);
}

static void
Object_freeMaybe(Object *o) {
  if (o) {
    Object_free(o);
  }
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
    /* coverage:no */
    return Object_ref(o);
    /* /coverage:no */
  }

  Object *d = MapObject_new();
  d->V.m = o->V.m;
  o->V.m = List_new(0, 0, Object_ref(d));
  return d;
}

static void
List_free(List *list) {
  while (list) {
    if (list->key) {
      free(list->key);
    }
    Object_free(list->value);
    List *n = list->next;
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
  if (p->onTimeout) {
    /* coverage:smoke */
    Object_free(p->onTimeout);
    /* /coverage:smoke */
  }
  if (p->onStdinData) {
    /* coverage:smoke */
    Object_free(p->onStdinData);
    /* /coverage:smoke */
  }
  /* coverage:net */
  Object_freeMaybe(p->connClient);
  Object_freeMaybe(p->connOptions);
  Object_freeMaybe(p->onConnData);
  Object_freeMaybe(p->onConnEnd);
  Object_freeMaybe(p->onConnError);
  /* /coverage:net */
  if (p->sock != -1) {
    /* coverage:unreachable */
    shutdown(p->sock, SHUT_RDWR);
    close(p->sock);
    /* /coverage:unreachable */
  }
  Object_free(p->vars);
  free(p);
}
