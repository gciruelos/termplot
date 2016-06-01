#ifndef PARSER
#define PARSER

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"

#define CONSTS_NUM sizeof(consts)/sizeof(consts[0])
#define OPS_NUM sizeof(ops)/sizeof(ops[0])
#define FUNCS_NUM sizeof(funcs)/sizeof(funcs[0])
#ifndef M_PI
  #define M_PI 3.14
#endif
#ifndef M_E
  #define M_E 2.79
#endif

enum {ASSOC_NONE=0, ASSOC_LEFT, ASSOC_RIGHT};

struct op_s {
  union {
    double (*bin)(double a1, double a2);
    double (*un)(double a);
  } function;
  unsigned char prec;
  unsigned char assoc;
  unsigned char unary;
  char op;
};

struct func_s {
  double (*f)(double a);
  char name[8];
};

struct const_s {
  double n;
  char name[8];
};

enum token_t {
  NUM,
  CONST,
  VARX,
  VARY,
  OP,
  PARL,
  PARR,
  FUNC,
  SEP,
  _ERR,
  _NONE
};

typedef struct tok_t {
  union {
    double n;
    struct const_s cst;
    struct op_s op;
    struct func_s func;
  } data;
  enum token_t type;
} token;

typedef struct expr_t {
  token ** parsed;
  char * str;
  unsigned int size;
} expr;

int check_expr(const expr e);
expr parse(const char* in);
double eval(const expr e, double x, double y);
void delete_expr(expr*  d);

#endif
