#ifndef PARSER
#define PARSER

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define OPS_SIZE 9


enum {ASSOC_NONE=0, ASSOC_LEFT, ASSOC_RIGHT};


struct op_s {
  union{
    double (*bin)(double a1, double a2);
    double (*un)(double a);
  } function;
  int prec;
  int assoc;
  int unary;
  char op;
};

enum token_t{
  NUM,
  VAR,
  OP,
  PARL,
  PARR,
  _ERR
};

typedef struct tok_t{
  union {
    int i;
    double d;
    struct op_s op;
  } data;
  enum token_t type;
} token;

typedef struct expr_t{
  token ** parsed;
  unsigned int size;
  char * str;
} expr;

expr parse(const char * in);
double eval(expr e, double x);
void delete_expr(expr d);

#endif
