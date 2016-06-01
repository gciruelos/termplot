#include <stdio.h>

#include "parser.h"

double _neg(double a) { return -a; }
double _add(double a1, double a2) { return a1 + a2; }
double _sub(double a1, double a2) { return a1 - a2; }
double _mul(double a1, double a2) { return a1 * a2; }
double _div(double a1, double a2) { return a1 / a2; }
double _mod(double a1, double a2) { return fmod(a1, a2); }

struct op_s ops[] = {
  {.function.un = _neg,
    .prec = 10, .assoc = ASSOC_RIGHT, .unary = 1, .op = '_'},
  {.function.bin = pow,
    .prec =  9, .assoc = ASSOC_RIGHT, .unary = 0, .op = '^'},
  {.function.bin = _mul,
    .prec =  8, .assoc = ASSOC_LEFT, .unary = 0, .op = '*'},
  {.function.bin = _div,
    .prec =  8, .assoc = ASSOC_LEFT, .unary = 0, .op = '/'},
  {.function.bin = _mod,
    .prec =  8, .assoc = ASSOC_LEFT, .unary = 0, .op = '%'},
  {.function.bin = _add,
    .prec =  5, .assoc = ASSOC_LEFT, .unary = 0, .op = '+'},
  {.function.bin = _sub,
    .prec =  5, .assoc = ASSOC_LEFT, .unary = 0, .op = '-'},
};


struct func_s funcs[] = {
  {sin, "sin"},
  {cos, "cos"},
  {tan, "tan"},
  {sqrt, "sqrt"},
  {floor, "floor"},
  {ceil, "ceil"},
  {fabs, "abs"},
  {log, "ln"},
  {log, "log"},
  {log10, "log10"}
};


struct const_s consts[]= {
  {M_E, "e"},
  {M_PI, "pi"}
};


void assign(struct op_s* op, char opch) {
  unsigned int i;
  for (i = 0; i < OPS_NUM; i++) {
    if (ops[i].op == opch) {
      *op = ops[i];
    }
  }
  /* op? op, op. op op op op. op! */
}


unsigned int next_token(const char* expr, token* res) {
  unsigned int idx = 0, i;

  /* Look for functions. */
  for(i = 0; i < FUNCS_NUM; i++) {
    if (strstr(expr, funcs[i].name) == expr) {
      d_print(funcs[i].name);

      res->type = FUNC;

      res->data.func.f = funcs[i].f;
      strcpy(res->data.func.name, funcs[i].name);

      idx += strlen(funcs[i].name);
      return idx;
    }
  }


  /* Look for constants. */
  for (i = 0; i < CONSTS_NUM; i++) {
    if (strstr(expr, consts[i].name) == expr) {
      d_print(consts[i].name);

      res->type = CONST;

      res->data.n = consts[i].n;
      strcpy(res->data.cst.name, consts[i].name);

      idx += strlen(consts[i].name);
      return idx;
    }
  }


  /* Look for operators. */
  for (i = 0; i < OPS_NUM; i++) {
    if (*expr == ops[i].op) {
      res->type = OP;
      assign(&(res->data.op), *expr);
      idx++;
      return idx;
    }
  }


  if (isdigit(expr[idx])) {
    res->type = NUM;
    res->data.n = 0;
    while (isdigit(expr[idx])) {
      res->data.n *= 10;
      res->data.n += (int) (expr[idx] - '0');
      idx++;
    }

    if (expr[idx] == '.') {
      idx++;
      double d = 10.0;
      while (isdigit(expr[idx])) {
        res->data.n += ((int) (expr[idx] - '0')) / d;
        d *= 10.0;
        idx++;
      }
    }
    return idx;
  }


  switch (*expr) {
    case '(':
      res->type = PARL;
      idx++;
      break;
    case ')':
      res->type = PARR;
      idx++;
      break;
    case 'x':
      res->type = VARX;
      idx++;
      break;
    case 'y':
      res->type = VARY;
      idx++;
      break;
    default:
      res->type = _ERR;
      idx++;
      break;
  }
  return idx;
}


expr parse(const char* in) {
  char * eq = malloc(sizeof(char)*100);
  int next = 0;
  token ** queue = malloc(sizeof(token*)*100);
  int queue_last = -1;
  token * stack[100];
  int stack_top = -1;

  int parse_error = 0;

  token * last_tok = NULL;

  unsigned int forward = 0;

  struct op_s o1, o2;

  while (*in != '\0') {
    token * tok = malloc(sizeof(token));

    forward = next_token(in, tok);
    while(forward) {
      eq[next++] = *(in++);
      forward--;
    }

    /* Check if - is unary or binary. */
    if (tok->type == OP && tok->data.op.op == '-') {
      if (last_tok == NULL || last_tok->type == PARL || last_tok->type == OP) {
        assign(&(tok->data.op), '_');
      }
    }

    switch (tok->type) {
      case NUM:
      case CONST:
      case VARX:
      case VARY:
        queue[++queue_last] = tok;
        break;

      case FUNC:
        stack[++stack_top] = tok;
        break;  /* Function token. */

      case SEP:
        break; /* Function argument separator. */

      case OP:
        o1 = tok->data.op;
        while (stack_top >= 0 && stack[stack_top]->type == OP) {
          o2 = stack[stack_top]->data.op;
          if ((o1.assoc == ASSOC_LEFT && o1.prec <= o2.prec) ||
              (o1.assoc == ASSOC_RIGHT && o1.prec < o2.prec)) {
            queue[++queue_last] = stack[stack_top--];
          } else break;
        }
        stack[++stack_top] = tok;
        break;

      case PARL:
        stack[++stack_top] = tok;
        break;

      case PARR:
        while (stack_top >= 0 && stack[stack_top]->type != PARL) {
          queue[++queue_last] = stack[stack_top--];
        }
        if (stack_top < 0) {
          parse_error = 1;
        } else if (stack[stack_top]->type == PARL) {
          free(stack[stack_top]);
          stack_top--;
        }

        if (stack_top>=0 && stack[stack_top]->type == FUNC) {
          queue[++queue_last] = stack[stack_top--];
        }
        break;
      case _ERR:
        parse_error = 1;

    }
    last_tok = tok;
  }

  while (stack_top >= 0) {
    queue[++queue_last] = stack[stack_top--];
  }

  eq[next] = '\0';

  expr res;
  res.parsed = queue;
  res.size = queue_last + 1;
  res.str = eq;

  if (parse_error) {
    d_print("Parse error: %s\n", in); 
  }

  if (check_expr(res) != 0) {
    delete_expr(&res);
  }

  return res;
}

double eval(const expr e, double x, double y) {
  double stack[100];
  int stack_top = -1;

  unsigned int i;
  for (i = 0; i < e.size; i++) {
    token * t = e.parsed[i];
    if (t->type == NUM || t->type == CONST) {
      stack[++stack_top] = t->data.n;
    } else if (t->type == VARX) {
      stack[++stack_top] = x;
    } else if (t->type == VARY) {
      stack[++stack_top] = y;
    } else if (t->type == OP) {
      struct op_s o = t->data.op;
      if (o.unary) {
        double a = stack[stack_top];

        stack[stack_top] = o.function.un(a);
      } else {
        double a1 = stack[stack_top - 1];
        double a2 = stack[stack_top];

        stack[--stack_top] = o.function.bin(a1, a2);
      }
    } else if (t->type == FUNC) {
      struct func_s f = t->data.func;
      double a = stack[stack_top];
      stack[stack_top] = f.f(a);
    }
  }

  return stack[0];
}


int check_expr(const expr e) {
  unsigned int stack = 0, i;

  int expr_error = 0;

  for (i = 0; i < e.size; i++) {
    token * t = e.parsed[i];
    switch (t->type) {
      case NUM:
      case CONST:
      case VARX:
      case VARY:
        stack++;
        break;
      case OP:
        if(!t->data.op.unary) stack--;
        break;
      case FUNC:
        break;
      default:
        expr_error = 1;
    }
  }

  return (stack != 1) || expr_error;
}

void delete_expr(expr* d) {
  if (d->parsed) {
    unsigned int i;
    for (i = 0; i < d->size; i++) {
      free(d->parsed[i]);
      d->parsed[i] = NULL;
    }
    free(d->parsed);
    d->parsed = NULL;
  }
  if (d->str) {
    free(d->str);
    d->str = NULL;
  }
  d->size = 0;
}


void prnt_token(token tok) {
  if (tok.type == NUM) {
    printf("{NUM %.2f}", tok.data.n);
  } else if (tok.type == CONST) {
    printf("{CONST %s}", tok.data.cst.name);
  } else if (tok.type == OP) {
    printf("{OP %c}", tok.data.op.op);
  } else if (tok.type == VARX) {
    printf("{VAR X}");
  } else if (tok.type == VARY) {
    printf("{VAR Y}");
  } else if (tok.type == FUNC) {
    printf("{FUNC %s}", tok.data.func.name);
  } else if (tok.type == PARL) {
    printf("{PARL (}");
  } else if (tok.type == PARR) {
    printf("{PARR )}");
  } else {
    printf("{WHAT %d}", tok.type);
  }
}


void print_caca(token** s, int sz) {
  int j;
  for (j = 0; j < sz; j++) {
    printf("#");
    prnt_token(*s[j]);
  }
  printf("\n");
}
/*
   int main(){
   char e[] = "x^2";
   expr a = parse(e);
   print_caca(a.parsed, a.size);
   printf("%f\n", eval(a, 1.2));
   delete_expr(a);
   return 0;
   }
   */
