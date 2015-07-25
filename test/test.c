#include "../src/parser.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EPSILON 0.0001

#define ASSERT_SIM(x,y) if(fabs((x)-(y))>=EPSILON){printf("Expected value:%f\n  Actual value: %f\n"); assert(0);}

double random_(){
  double x = rand() / (RAND_MAX + 1.);
  return x*rand();
}


double f1(double x){return x*x+1;}
double f2(double x){return pow(sin(x),4);}
double f3(double x){return pow(2,pow(sin(x),2));}

void parse1(){
  unsigned int i;
  expr e;
  double x;

  e = parse("x^2+1");
  for(i = 0; i<1000; i++){
    x = random_();
    ASSERT_SIM(eval(e, x), f1(x));
  }

  e = parse("sin(x)^4");
  for(i = 0; i<1000; i++){
    x = random_();
    ASSERT_SIM(eval(e, x), f2(x));
  }

  e = parse("2^(sin(x)^2)");
  for(i = 0; i<1000; i++){
    x = random_();
    ASSERT_SIM(eval(e, x), f3(x));
  }

}


int main(){
  parse1();


}

