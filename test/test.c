#include "../src/parser.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EPSILON 0.0001

#define ASSERT_SIM(x,y) if(fabs((x)-(y))>=EPSILON){printf("Expected value: %f\n  Actual value: %f\n",y,x); assert(0);}

double random_(){
  double x = rand() / (RAND_MAX + 1.);
  return x*rand();
}


double f1(double x){return x*x+1;}
double f2(double x){return pow(sin(x),4);}
double f3(double x){return pow(2,pow(sin(x),2));}
double f4(double x){return pow(x-2, 2)+1;}

void parse1(){
  unsigned int i;
  expr e;
  double x;

  e = parse("x^2+1");
  for(i = 0; i<1000; i++){
    x = random_();
    ASSERT_SIM(eval(e, x, 0), f1(x));
  }

  e = parse("sin(x)^4");
  for(i = 0; i<1000; i++){
    x = random_();
    ASSERT_SIM(eval(e, x, 0), f2(x));
  }

  e = parse("2^(sin(x)^2)");
  for(i = 0; i<1000; i++){
    x = random_();
    ASSERT_SIM(eval(e, x, 0), f3(x));
  }

  e = parse("(x-2)^2 + 1");
  for(i = 0; i<1000; i++){
    x = random_();
    ASSERT_SIM(eval(e, x, 0), f4(x));
  }
}


double c1(double x){return M_PI;}
double c2(double x){return M_PI + x;}
double c3(double x){return sin(M_PI + x);}
double c4(double x){return M_PI + sin(x);}

void parse_const(){
  unsigned int i;
  expr e;
  double x;

  e = parse("pi");
  for(i = 0; i<1000; i++){
    x = random_();
    ASSERT_SIM(eval(e, x, 0), c1(x));
  }

  e = parse("pi + x");
  for(i = 0; i<1000; i++){
    x = random_();
    ASSERT_SIM(eval(e, x, 0), c2(x));
  }

  e = parse("sin(pi + x)");
  for(i = 0; i<1000; i++){
    x = random_();
    ASSERT_SIM(eval(e, x, 0), c3(x));
  }

  e = parse("pi + sin(x)");
  for(i = 0; i<1000; i++){
    x = random_();
    ASSERT_SIM(eval(e, x, 0), c4(x));
  }
}

int main(){
  parse1();
  parse_const();
}

