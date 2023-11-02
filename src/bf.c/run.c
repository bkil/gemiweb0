#include "vm.h" /* Parser_eval Parser_free Parser_new */

#include <fcntl.h> /* open */
#include <stdio.h> /* fputs stderr */
#include <stdlib.h> /* free size_t */
#include <string.h> /* memcpy */
#include <sys/mman.h> /* mmap munmap */
#include <sys/stat.h> /* fstat open */
#include <sys/types.h> /* fstat off_t open */
#include <unistd.h> /* close fstat */

#define MAINERR (-3)

static size_t
__attribute__((warn_unused_result, used))
off_t2size_t(off_t x) {
  if (x < 0) {
    return 0;
  }
  return (size_t)x;
}

int
main(int argc, char **argv) {
  if (argc != 2) {
    fputs("usage: [main.js]\n", stderr);
    return MAINERR;
  }

  const int fd = open(argv[1], 0);
  if (fd < 0) {
    perror("open failed of script");
    return MAINERR;
  }

  struct stat sb;
  if (fstat(fd, &sb) < 0) {
    perror("stat failed of script");
    close(fd);
    return MAINERR;
  }
  size_t len = off_t2size_t(sb.st_size);

  char *file = mmap(NULL, len, PROT_READ, MAP_SHARED, fd, 0);
  if (file == (void*)-1) {
    perror("mmap failed of script");
    close(fd);
    return MAINERR;
  }

  char *prog = malloc(len + 1);
  memcpy(prog, file, len);
  prog[len] = 0;

  if (munmap(file, len) < 0) {
    perror("munmap failed");
    free(prog);
    return MAINERR;
  }
  if (close(fd) < 0) {
    perror("close failed");
    free(prog);
    return MAINERR;
  }

  struct Parser *p = Parser_new();
  int ret = Parser_eval(p, prog, 0, 0, 1);
  free(prog);
  Parser_free(p);

  return ret;
}
