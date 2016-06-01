#ifndef PLOT
#define PLOT

#include <stdio.h>

#include "options.h"
#include "parser.h"
#include "ui.h"

#define MAX_FUNCTIONS 16


enum {EXPLICIT, IMPLICIT};

struct function {
    expr f;
    expr g;
    unsigned char type;
    unsigned char valid;
} functions[MAX_FUNCTIONS];

void replot_functions(void);
void plot_function(expr e, int index);
void plot_implicit(expr e1, expr e2, int index);
void add_plot(char* cmd);

void draw_axis(void);
void draw_axis_numbers(void);

void init_plotter(void);
void clean_plotter(void);


#endif
