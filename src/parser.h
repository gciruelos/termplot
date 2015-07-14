#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#define OPS_SIZE 9


enum {ASSOC_NONE=0, ASSOC_LEFT, ASSOC_RIGHT};


double eval_neg(double a){return -a;}
double eval_add(double a1, double a2){return a1+a2;}
double eval_sub(double a1, double a2){return a1-a2;}
double eval_mul(double a1, double a2){return a1*a2;}
double eval_div(double a1, double a2){return a1/a2;}



struct op_s {
  char op;
  int prec;
  int assoc;
  int unary;
  union{
    double (*bin)(double a1, double a2);
    double (*un)(double a);
  } function;
  } ops[OPS_SIZE]={
  {'_', 10, ASSOC_RIGHT, 1, eval_neg},
  {'^', 9, ASSOC_RIGHT, 0, NULL},
  {'*', 8, ASSOC_LEFT, 0, eval_mul},
  {'/', 8, ASSOC_LEFT, 0, eval_div},
  {'%', 8, ASSOC_LEFT, 0, NULL},
  {'+', 5, ASSOC_LEFT, 0, eval_add},
  {'-', 5, ASSOC_LEFT, 0, eval_sub},
};

enum token_t{
  NUM,
  VAR,
  OP,
  PARL,
  PARR,
  ERR
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
} expr;

