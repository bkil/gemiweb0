/* Copyright (C) 2023 bkil.hu
Refer to the GNU GPL v2 in LICENSE for terms */

#ifndef _include_vm_h
#define _include_vm_h

#ifdef SMALLBIN
# define _inline_
#else
# define _inline_ inline __attribute__((used))
#endif

#include <stdlib.h> /* size_t */
#include <limits.h> /* INT_MIN INT_MAX */
#include <sys/types.h> /* off_t */

struct Parser;

__attribute__((malloc, returns_nonnull, warn_unused_result))
struct Parser *Parser_new(void);

__attribute__((nonnull, warn_unused_result))
int Parser_eval(struct Parser *p, const char *prog, size_t len, int debug);

__attribute__((nonnull))
void Parser_free(struct Parser *p);

__attribute__((nonnull, warn_unused_result))
int Parser_eventLoop(struct Parser *p, const char *prog, size_t len, int debug);

_inline_
static size_t
__attribute__((warn_unused_result))
off_t2size_t(off_t x) {
  if (x < 0) {
    return 0;
  }
  return (size_t)x;
}

_inline_
static int
__attribute__((warn_unused_result))
off_t2int(off_t x) {
  if ((x < INT_MIN) || (x > INT_MAX)) {
    return 0;
  }
  return (int)x;
}

#endif
