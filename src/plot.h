#ifndef PLOT
#define PLOT

#include "options.h"
#include "parser.h"

#include <unistd.h>
#include <ncurses.h>

struct function{
  expr f;
  int valid;
} functions[32];




void replot_functions(int width, int height);
void plot_function(expr e, int width, int height);
void add_function(char * cmd);
#endif
