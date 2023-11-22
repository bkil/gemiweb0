#include "vm.h"

#include <string.h> /* memset strlen strncmp */
#include <stdio.h> /* EOF fgetc fputc fputs stderr stdout */
#include <stdlib.h> /* free malloc realloc size_t */

enum RuleT {
  None = 0,
  Literal,
  Seq,
  Or,
  Atleast1,
  Atleast0,
  Call,
  Fun,
  FunForce,
  Local
};

typedef struct Locals {
  const char *savedPos;
} Locals;

typedef struct Lit {
  const size_t len;
  const char s[];
} Lit;

struct Parser;

typedef int (*FunProto)(struct Parser *p);

struct Rule;

struct Rule {
  const enum RuleT t;
  const union {
    const Lit *literal;
    const struct Rule *seq;
    const struct Rule *or;
    const struct Rule *atleast1;
    const struct Rule *atleast0;
    const struct Rule **call;
    const FunProto fun;
    const FunProto funForce;
    const struct Rule *local;
  } V;
};

typedef struct Rule Rule;

typedef struct Parser {
  const char *prog;
  const char *inp;
  size_t inpSize;
  int *v;
  size_t vSize;
  char *out;
  size_t outSize;
  const char *err;
  int *lhs;
  Locals *locals;
  int i;
  int j;
  int lastinpj;
  int debug;
  int nest;

} Parser;

#define LIT(a) (const Rule){.t = Literal, \
  .V.literal = \
    &(const union { \
      const Lit l; \
      const struct {const size_t len; const char s[sizeof(a)];} u;\
    }){.u.len = sizeof(a) - 1, .u.s = a}\
    .l}
#define SEQ(...) (const Rule){.t = Seq, .V.seq = (const Rule[]){__VA_ARGS__, {.t = None}}}
#define OR(...) (const Rule){.t = Or, .V.or = (const Rule[]){__VA_ARGS__, {.t = None}}}
#define ATLEAST1(a) (const Rule){.t = Atleast1, .V.atleast1 = &a}
#define ATLEAST0(a) (const Rule){.t = Atleast0, .V.atleast0 = &a}
#define CALL(a) (const Rule){.t = Call, .V.call = &a}
#define FUN(a) (const Rule){.t = Fun, .V.fun = &a}
#define FUNFORCE(a) (const Rule){.t = FunForce, .V.fun = &a}
#define LOCAL(a) (const Rule){.t = Local, .V.local = &a}

static int
__attribute__((nonnull, warn_unused_result))
setError(Parser *p, const char *message) {
  p->err = message;
  return 0;
}

static int
__attribute__((nonnull, warn_unused_result))
parse(Parser *p, const Rule *rule, size_t limit) {
  if (p->err) {
    return 0;
  }
  if (limit-- <= 0) {
    return setError(p, "internal error: grammar recursion depth exceeded");
  }

  switch (rule->t) {
    case Literal: {
      const Lit *l = rule->V.literal;
      if (strncmp(p->prog, l->s, l->len)) {
        return 0;
      }
      p->prog += l->len;
      return 1;
    }

    case Seq: {
      const Rule *r = rule->V.seq;
      for (; r->t != None; r++) {
        if (!parse(p, r, limit)) {
          return 0;
        }
      }
      return 1;
    }

    case Or: {
      const Rule *r = rule->V.or;
      for (; r->t != None; r++) {
        if (parse(p, r, limit)) {
          return 1;
        }
      }
      break;
    }

    case Atleast1: {
      const Rule *r = rule->V.atleast1;
      if (parse(p, r, limit)) {
        while (parse(p, r, limit)) {
        }
        return 1;
      }
      break;
    }

    case Atleast0:
      while (parse(p, rule->V.atleast0, limit)) {
      }
      return 1;

    case Call: {
      return parse(p, *rule->V.call, limit);
    }

    case Fun:
      if (p->nest) {
        return 1;
      }
    case FunForce:
      return (*rule->V.fun)(p);

    case Local: {
      Locals *savedLocals = p->locals;
      Locals l = {.savedPos = 0};
      p->locals = &l;
      int ok = parse(p, rule->V.local, limit);
      p->locals = savedLocals;
      return ok;
    }

    case None:
    default:
      return setError(p, "internal error: tried to apply non-Object rule");
  }
  return 0;
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
g_newArray(Parser *p) {
  p->vSize = 0;
  p->v = realloc(p->v, p->vSize);
  return 1;
}

static int
g_arrayPlus(Parser *p) {
  if (!resize(p)) {
    return 0;
  }
  p->v[p->i]++;
  return 1;
}

static int
g_arrayMinus(Parser *p) {
  if (!resize(p)) {
    return 0;
  }
  p->v[p->i]--;
  return 1;
}

static int
g_input(Parser *p) {
  if (!resize(p)) {
    return 0;
  }
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
  return 1;
}

static int
g_lhsSet_i(Parser *p) {
  p->lhs = &p->i;
  return 1;
}

static int
g_lhsSet_j(Parser *p) {
  p->lhs = &p->j;
  return 1;
}

static int
g_lhsPut0(Parser *p) {
  *p->lhs = 0;
  return 1;
}

static int
g_lhsInc(Parser *p) {
  (*p->lhs)++;
  return 1;
}

static int
g_lhsDec(Parser *p) {
  (*p->lhs)--;
  return 1;
}

static int
g_whileBefore(Parser *p) {
  p->locals->savedPos = p->prog;
  return 1;
}

static int
g_whileEnter(Parser *p) {
  if (!resize(p)) {
    return 0;
  }
  if (!p->v[p->i]) {
    p->locals->savedPos = 0;
    p->nest++;
  }
  return 1;
}

static int
g_whileEndForce(Parser *p) {
  if (!p->locals->savedPos) {
    p->nest--;
  } else if (!p->nest) {
    if (!resize(p)) {
      return 0;
    }
    if (p->v[p->i]) {
      p->prog = p->locals->savedPos;
    }
  }
  return 1;
}

static int
g_write(Parser *p) {
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
  return 1;
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
  const Rule whitespace = ATLEAST0(
    OR(
      LIT(" "),
      LIT("\t"),
      LIT("\n")
    )
  );

  const Rule *p_statements = 0;
  const Rule statement = SEQ(
    whitespace,
    OR(
      SEQ(
        OR(
          SEQ(
            LIT("i"),
            FUN(g_lhsSet_i)
          ),
          SEQ(
            LIT("j"),
            FUN(g_lhsSet_j)
          )
        ),
        OR(
          SEQ(
            LIT("=0"),
            FUN(g_lhsPut0)
          ),
          SEQ(
            LIT("++"),
            FUN(g_lhsInc)
          ),
          SEQ(
            LIT("--"),
            FUN(g_lhsDec)
          )
        )
      ),
      SEQ(
        LIT("var "),
        OR(
          LIT("v"),
          LIT("i"),
          LIT("j")
        )
      ),
      SEQ(
        LIT("v"),
        OR(
          SEQ(
            LIT("=new Array"),
            FUN(g_newArray)
          ),
          SEQ(
            LIT("[i]="),
            OR(
              SEQ(
                LIT("(v[i]|0)"),
                OR(
                  SEQ(
                    LIT("+"),
                    FUN(g_arrayPlus)
                  ),
                  SEQ(
                    LIT("-"),
                    FUN(g_arrayMinus)
                  )
                ),
                LIT("1")
              ),
              SEQ(
                LIT("form.text.value.charCodeAt(j)|0"),
                FUN(g_input)
              )
            )
          )
        )
      ),
      LOCAL(
        ATLEAST1(
          SEQ(
            FUN(g_whileBefore),
            LIT("while(v[i]){"),
            FUN(g_whileEnter),
            CALL(p_statements),
            LIT("}"),
            FUNFORCE(g_whileEndForce)
          )
        )
      ),
      SEQ(
        OR(
          LIT("console.log"),
          LIT("document.write")
        ),
        LIT("(String.fromCharCode(v[i]))"),
        FUN(g_write)
      )
    ),
    whitespace
  );

  const Rule moreStatements = SEQ(LIT(";"), statement);

  const Rule statements = SEQ(
    statement,
    ATLEAST0(
      moreStatements
    )
  );
  p_statements = &statements;

  p->prog = prog;
  p->inp = inp;
  p->inpSize = inp ? strlen(inp) : 0;
  p->outSize = 1;
  p->out = out ? calloc(1, p->outSize) : 0;
  p->err = 0;
  p->i = -1;
  p->j = -1;
  p->lastinpj = -1;
  p->debug = debug;
  p->lhs = 0;
  p->locals = 0;
  p->nest = 0;

  ok = parse(p, &statements, 100);
  if (p->err) {
    ok = 0;
  } else if (ok && *p->prog) {
    ok = setError(p, "unmatched root rule");
  }

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
