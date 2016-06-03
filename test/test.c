#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/parser.h"

#define EPSILON 0.0001
#define ASSERT_SIM(x,y) \
  if(fabs((x)-(y))>=EPSILON){ \
    printf("Expected value: %f\n  Actual value: %f\n",y,x); \
  }

double random_(void) {
  double x = rand() / (RAND_MAX + 1.);
  return x * rand();
}

double f1(double x) { return x * x + 1; }
double f2(double x) { return pow(sin(x), 4); }
double f3(double x) { return pow(2, pow(sin(x),2)); }
double f4(double x) { return pow(x - 2, 2) + 1; }
double f5(double x) { return x + 1 / x; }

struct parser_test {
  double (*f)(double x);
  char* str;
};

struct parser_test test1[] = {
  { .f = f1, .str = "x^2+1" },
  { .f = f2, .str = "sin(x)^4" },
  { .f = f3, .str = "2^(sin(x)^2)" },
  { .f = f4, .str = "(x-2)^2 + 1" },
  { .f = f5, .str = "x + x^-1" },
  { .f = NULL, .str = "" },
};

void parse1(void) {
  unsigned int i;
  expr e;
  double x;

  for (int t = 0; test1[t].f != NULL; t++) {
    e = parse(test1[t].str);
    for (i = 0; i < 1000; i++) {
      x = random_();
      ASSERT_SIM(eval(e, x, 0), test1[t].f(x));
    }
    delete_expr(&e);
  }
}

double c1(__attribute__((unused)) double x) { return M_PI; }
double c2(double x) { return M_PI + x; }
double c3(double x) { return sin(M_PI + x); }
double c4(double x) { return M_PI + sin(x); }

void parse_const(void) {
  unsigned int i;
  expr e;
  double x;

  e = parse("pi");
  for (i = 0; i < 1000; i++) {
    x = random_();
    ASSERT_SIM(eval(e, x, 0), c1(x));
  }

  e = parse("pi + x");
  for (i = 0; i < 1000; i++) {
    x = random_();
    ASSERT_SIM(eval(e, x, 0), c2(x));
  }

  e = parse("sin(pi + x)");
  for (i = 0; i < 1000; i++) {
    x = random_();
    ASSERT_SIM(eval(e, x, 0), c3(x));
  }

  e = parse("pi + sin(x)");
  for (i = 0; i < 1000; i++) {
    x = random_();
    ASSERT_SIM(eval(e, x, 0), c4(x));
  }
}

int main(void) {
  parse1();
  parse_const();
}

