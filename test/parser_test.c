#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/parser.h"

#define EPSILON 1e-10
#define ASSERT_SIM(x,y) \
  if (((x) != (y)) && (fabs((x) - (y)) / (x) >= EPSILON)) { \
    printf("Expected value: %f\n  Actual value: %f\n", y, x); \
    assert(0); \
  }

double random_(void) {
  double x = rand() / (RAND_MAX + 1.);
  return x * rand();
}

double f1(double x) { return x * x + 1; }
double f2(double x) { return pow(sin(x), 4); }
double f3(double x) { return pow(2, pow(sin(x),2)); }
double f4(double x) { return pow(x - 2, 2) + 1; }
double f5(double x) { return x + 1. / x; }
double f6(double x) { return -pow(x, 2); }

struct parser_test {
  double (*f)(double x);
  char* str;
};

struct parser_test test1[] = {
  { .f = f1, .str = "x^2+1" },
  { .f = f2, .str = "sin(x)^4" },
  { .f = f3, .str = "2^(sin(x)^2)" },
  { .f = f4, .str = "(x-2)^2 + 1" },
  { .f = f5, .str = "x + x^(-1)" },
  { .f = f6, .str = "-x^2" },
  { .f = NULL, .str = "" },
};

void parse_1(void) {
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

// To test using american fuzzy lop.
void parse_afl(const char* filename) {
  FILE * fp;
  fp = fopen(filename, "r");
  int nchars = 100;
  int bytes_read;
  char* input_string = (char *) malloc(nchars + 1);
  expr e;
  
  while (fgets(input_string, nchars, fp)) {
    bytes_read = strlen(input_string);
    
    if (bytes_read == 0) {
      continue;
    } else if (input_string[0] == '>') {
      e = parse(input_string + 1);
    } else if (input_string[0] == '-') {
      delete_expr(&e);
    } else if (input_string[0] == 'e') {
      char* space = strchr(input_string + 1, ' ');
      char* errx;
      char* erry;
      float x = strtof(input_string + 1, &errx);
      float y = strtof(space + 1, &erry);
      if ((errx == input_string + 1) || (erry == space + 1)) {
        continue;
      }
      printf("Read: x = %f y = %f\n", x, y);
      ASSERT_SIM(eval(e, x, 0), y);
    } else {
      continue;
    }

  }
  free(input_string);
}

