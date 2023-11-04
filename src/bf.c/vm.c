#include "vm.h"

#include <string.h> /* memset strlen strncmp */
#include <stdio.h> /* EOF fgetc fputc fputs stderr stdout */
#include <stdlib.h> /* atoi free malloc realloc size_t */

typedef struct Parser {
  const char *prog;
  const char *inp;
  size_t inpSize;
  int *v;
  size_t vSize;
  char *out;
  size_t outSize;
  const char *err;
  const char *errDetails;
  int i;
  int j;
  int lastinpj;
  int debug;
} Parser;

static int
__attribute__((nonnull, warn_unused_result))
setError(Parser *p, const char *message) {
  p->err = message;
  return 0;
}

static int
__attribute__((nonnull, warn_unused_result))
accept(Parser *p, const char *s) {
  size_t len = strlen(s);
  if (!strncmp(p->prog, s, len)) {
    p->prog += len;
    while (*p->prog && (*p->prog < 33)) {
      p->prog++;
    }
    return 1;
  }
  return 0;
}

static int
__attribute__((nonnull, warn_unused_result))
expect(Parser *p, const char *s) {
  if (accept(p, s)) {
    return 1;
  }
  p->errDetails = s;
  return setError(p, "parser expected different substring");
}

static int
__attribute__((nonnull, warn_unused_result))
resize(Parser *p) {
  if (!p->v) {
    return setError(p, "v[] array uninitialized");
  }
  if (p->i < 0) {
    return setError(p, "unsupported negative i array index");
  }

  if (p->i >= (int)p->vSize) {
    size_t n = (size_t)p->i * 5 / 4 + 1;
    p->v = realloc(p->v, n * sizeof(p->v[0]));
    memset(p->v + p->vSize, 0, (n - p->vSize) * sizeof(p->v[0]));
    p->vSize = n;
  }
  return 1;
}

static int
__attribute__((nonnull, warn_unused_result))
parseAssignment(Parser *p) {
  if (accept(p, "v")) {
    if (accept(p, "=new Array")) {
      p->vSize = 0;
      p->v = realloc(p->v, p->vSize);
    } else {
      if (!resize(p)) {
        return 0;
      }
      if (accept(p, "[i]=(v[i]|0)")) {
        if (accept(p, "+1")) {
          p->v[p->i]++;
        } else if (expect(p, "-1")) {
          p->v[p->i]--;
        } else {
          return 0;
        }
      } else if (expect(p, "[i]=form.text.value.charCodeAt(j)|0")) {
        if (p->j < 0) {
          return setError(p, "j uninitialized");
        }
        if (p->j != p->lastinpj + 1) {
          return setError(p, "form.text.value needs to be iterated in sequence and once");
        }
        p->lastinpj = p->j;

        if (p->inp) {
          p->v[p->i] = (p->j >= 0) && (p->j < (int)p->inpSize) ? p->inp[p->j] : 0;
        } else {
          int ch = fgetc(stdin);
          p->v[p->i] = ch == EOF ? 0 : ch;
        }
      } else {
        return 0;
      }
    }

  } else {
    int *idx;
    if (accept(p, "i")) {
      idx = &p->i;
    } else if (expect(p, "j")) {
      idx = &p->j;
    } else {
      return 0;
    }

    if (accept(p, "=0")) {
      *idx = 0;
    } else if (accept(p, "++")) {
      (*idx)++;
    } else if (expect(p, "--")) {
      (*idx)--;
    } else {
      return 0;
    }
  }
  return 1;
}

static int
parseBody(Parser *p);

static int
__attribute__((nonnull, warn_unused_result))
parseStatement(Parser *p) {
  if (accept(p, "while(v[i])")) {
    const char *begin = p->prog;
    do {
      p->prog = begin;
      if (!resize(p)) {
        return 0;
      }
      if (p->v[p->i]) {
        if (!parseBody(p)) {
          return 0;
        }
      } else {
        int nest;
        if (!expect(p, "{")) {
          return 0;
        }
        for (nest = 1; nest; p->prog++) {
          nest += *p->prog == '{' ? 1 : *p->prog == '}' ? -1 : 0;
        }
        break;
      }
    } while (1);

  } else if (accept(p, "console.log(String.fromCharCode(v[i]))") ||
      accept(p, "document.write(String.fromCharCode(v[i]))")) {
    if (!resize(p)) {
      return 0;
    }
    if (p->out) {
      p->outSize++;
      p->out = realloc(p->out, p->outSize * sizeof(p->out[0]));
      p->out[p->outSize - 2] = (char)p->v[p->i];
    } else {
      fputc(p->v[p->i], stdout);
    }
  } else if (accept(p, "var ") && (accept(p, "i") || accept(p, "j") || expect(p, "v"))) {
  } else {
    return parseAssignment(p);
  }
  return 1;
}

static int
__attribute__((nonnull, warn_unused_result))
parseStatements(Parser *p) {
  int o = parseStatement(p);
  while (o && *p->prog) {
    o = expect(p, ";") && parseStatement(p);
  }
  return o;
}

static int
__attribute__((nonnull, warn_unused_result))
parseBody(Parser *p) {
  int o = expect(p, "{") && parseStatement(p);
  while (o && accept(p, ";")) {
    o = parseStatement(p);
  }
  return o && expect(p, "}");
}

static void
__attribute__((nonnull))
showError(Parser *p) {
  if (p->debug) {
    const char *s = p->prog;
    size_t len;

    fputs("error: ", stderr);
    if (p->err) {
      fputs(p->err, stderr);
      if (p->errDetails) {
        fputs(" ( '", stderr);
        fputs(p->errDetails, stderr);
        fputs("' )", stderr);
      }
    }
    fputs("\n", stderr);

    for (len = 32; len-- && *s; s++) {
      fputc(*s, stderr);
    }
    fputs("\n", stderr);
  }
}

Parser *
Parser_new(void) {
  Parser *p = malloc(sizeof(*p));
  p->v = 0;
  p->vSize = 0;
  return p;
}

void
Parser_free(Parser *p) {
  if (p->v) {
    free(p->v);
  }
  free(p);
}

int
Parser_eval(Parser *p, const char *prog, const char *inp, char **out, int debug) {
  int ok;
  p->prog = prog;
  p->inp = inp;
  p->inpSize = inp ? strlen(inp) : 0;
  p->outSize = 1;
  p->out = out ? calloc(1, p->outSize) : 0;
  p->err = 0;
  p->errDetails = 0;
  p->i = -1;
  p->j = -1;
  p->lastinpj = -1;
  p->debug = debug;

  ok = parseStatements(p);
  if (p->out) {
    p->out[p->outSize - 1] = 0;
    *out = p->out;
    p->out = 0;
  }

  if (!ok) {
    showError(p);
    return -1;
  }
  return p->v && (p->i >= 0) && (p->i < (int)p->vSize) ? p->v[p->i] : 0;
}
