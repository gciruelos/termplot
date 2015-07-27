#ifndef PLOT
#define PLOT

#include "options.h"
#include "parser.h"
#include "ui.h"

#include <stdio.h>

#define MAX_FUNCTIONS 16


enum {EXPLICIT, IMPLICIT};


struct function{
  expr f;
  expr g;
  unsigned char type;
  unsigned char valid;
} functions[MAX_FUNCTIONS];


void replot_functions();
void plot_function(expr e, int index);
void plot_implicit(expr e1, expr e2, int index);
void add_plot(char * cmd);

void draw_axis();

void init_plotter();
void clean_plotter();


#endif
