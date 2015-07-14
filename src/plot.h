#ifndef PLOT
#define PLOT

#include "options.h"
#include "parser.h"

#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>

#define MAX_FUNCTIONS 32

struct function{
  expr f;
  int valid;
} functions[MAX_FUNCTIONS];




void replot_functions(int width, int height);
void plot_function(expr e, int index, int width, int height);
void add_function(char * cmd);
#endif
