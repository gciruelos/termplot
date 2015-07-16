#ifndef PARSER
#define PARSER

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define OPS_SIZE 9

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

enum token_t{
  NUM,
  VAR,
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
    struct op_s op;
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
double eval(const expr e, double x);
void delete_expr(expr *  d);

#endif
