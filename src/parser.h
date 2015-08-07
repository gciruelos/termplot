#ifndef PARSER
#define PARSER

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define CONSTS_NUM 2
#define OPS_NUM 9
#define FUNCS_NUM 10

#include "debug.h"

enum {ASSOC_NONE=0, ASSOC_LEFT, ASSOC_RIGHT};


struct op_s {
  union{
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

enum token_t{
  NUM,
  CONST,
  VARX,
  VARY,
  OP,
  PARL,
  PARR,
  FUNC,
  SEP,
  _ERR
};

typedef struct tok_t{
  union {
    double n;
    struct const_s cst;
    struct op_s op;
    struct func_s func;
  } data;
  enum token_t type;
} token;

typedef struct expr_t{
  token ** parsed;
  char * str;
  unsigned int size;
} expr;

int check_expr(const expr e);
expr parse(const char * in);
double eval(const expr e, double x, double y);
void delete_expr(expr *  d);



#endif
