#include <stdio.h> // fputs putchar stdout printf
#include "vm-debug.h"

// TODO
static void
putsn(const char *s, size_t len) {
  while (len-- && *s) {
    fputc(*(s++), stdout);
  }
}

static void
printObject2(Object *o, int nest) {
  for (int i = 0; i < nest; i++) {
    putchar(' ');
  }
  printf("r=%d, t=%d", o->ref, o->t);
  if (o->ref < -1) {
    puts("");
    return;
  }
  if (nest > 4) {
    fputs("...\n", stdout);
    return;
  }
  if (o->t == MapObject) {
    puts("");
    List *it = o->m;
    while (it) {
      for (int i = 0; i < nest; i++) {
        putchar(' ');
      }
      putchar('.');
      fputs(it->key ? it->key : "(null)", stdout);
      if (it->value) {
        putchar('\n');
        printObject2(it->value, nest + 1);
      } else {
        fputs(" (null entry)\n", stdout);
      }
      it = it->next;
    }
    return;
  }

  putchar(' ');
  switch (o->t) {
    case UndefinedObject:
      fputs("undefined", stdout);
      break;

    case IntObject: {
      printf("%d", o->i);
      break;
    }

    case StringObject:
      putchar('s');
      putchar(':');
      putsn(o->s.s, o->s.len);
      break;

    case ConstStringObject:
      putchar('c');
      putchar(':');
      putsn(o->c.s, o->c.len);
      break;

    case FunctionJs:
      printf("Function(%p,%p)", o->j.cs, (void *)o->j.scope);
      break;

    case FunctionNative:
      printf("Native(%lx)", (size_t)o->f);
      break;

    default: {}
  }
  putchar('\n');
}

void __attribute__((const))
printObject(Object *o) {
  puts("-printObject");
  printObject2(o, 0);
}
