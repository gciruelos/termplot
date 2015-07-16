#ifndef PLOT
#define PLOT

#include "options.h"
#include "parser.h"
#include "ui.h"

#include <stdio.h>

#define MAX_FUNCTIONS 32

struct function{
  expr f;
  int valid;
} functions[MAX_FUNCTIONS];


void replot_functions();
void plot_function(expr e, int index);
void add_function(char * cmd);

void draw_axis();

void init_plotter();
void clean_plotter();


#endif
