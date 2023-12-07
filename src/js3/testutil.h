#ifndef _include_testutil_h
#define _include_testutil_h

#include <stdbool.h> /* true false bool */

void setDebug(bool debug);
void __attribute__((nonnull(1))) t3(const char *code, int expect, const char *name);
void __attribute__((nonnull)) testEventLoop(const char *prepare, const char *after, int expect);
void __attribute__((nonnull)) t(const char *code, int expect);
void __attribute__((nonnull)) te(const char *prepare, const char *after, int expect);
int exitWithErrorCount(const char *kind);

#endif
