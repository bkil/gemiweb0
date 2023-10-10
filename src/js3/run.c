#include "vm.h" /* Parser_new Parser_eval Parser_free off_t2size_t */
#include <stdio.h> /* fputs stderr */
#include <stdlib.h> /* size_t */
#include <sys/mman.h> /* mmap munmap */
#include <sys/types.h> /* open fstat */
#include <sys/stat.h> /* open fstat */
#include <fcntl.h> /* open */
#include <unistd.h> /* close fstat */

#define MAINERR (-3)

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

  char *prog = mmap(NULL, len, PROT_READ, MAP_SHARED, fd, 0);
  if (prog == (void*)-1) {
    perror("mmap failed of script");
    close(fd);
    return MAINERR;
  }

  struct Parser *p = Parser_new();
  int ret = Parser_eval(p, prog, len, 1);
  Parser_free(p);

  if (munmap(prog, len) < 0) {
    perror("munmap failed");
    ret = MAINERR;
  }
  if (close(fd) < 0) {
    perror("close failed");
    ret = MAINERR;
  }

  return ret;
}
