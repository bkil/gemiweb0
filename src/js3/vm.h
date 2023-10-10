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

struct Parser *Parser_new(void);
int Parser_eval(struct Parser *p, const char *prog, size_t len, int debug);
void Parser_free(struct Parser *p);

_inline_
static size_t
off_t2size_t(off_t x) {
  if (x < 0) {
    return 0;
  }
  return (size_t)x;
}

_inline_
static int
off_t2int(off_t x) {
  if ((x < INT_MIN) || (x > INT_MAX)) {
    return 0;
  }
  return (int)x;
}

#endif
