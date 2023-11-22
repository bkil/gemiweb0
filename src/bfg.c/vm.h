#ifndef _include_vm_h
#define _include_vm_h

struct Parser;

__attribute__((malloc, returns_nonnull, warn_unused_result))
struct Parser *Parser_new(void);

__attribute__((nonnull(1, 2), warn_unused_result))
int Parser_eval(struct Parser *p, const char *prog, const char *inp, char **out, int debug);

__attribute__((nonnull))
void Parser_free(struct Parser *p);

#endif
