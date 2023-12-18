/* Copyright (C) 2023 bkil.hu
Refer to the GNU GPL v2 in LICENSE for terms */

static int
__attribute__((nonnull))
snprinti(char *s, size_t n, int i) {
  if (n == 1) {
    *s = '\0';
    return 0;
  }
  if (n < 1) {
    return 0;
  }
  if (i < 0) {
    *s = '-';
    return 1 + snprinti(s + 1, n - 1, -i);
  }
  int r = i / 10;
  int k = 0;
  if (r) {
    k = snprinti(s, n, r);
    if (k < 0) {
      return k;
    }
    s += k;
    n -= (size_t)k;
  }
  if (n > 1) {
    *(s++) = (char)('0' + (i % 10));
  }
  if (n > 0) {
    *(s++) = '\0';
  }
  return k + 1;
}
