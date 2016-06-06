#ifndef PLOT
#define PLOT

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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


double test_interval(const expr* e1, const expr* e2, 
    double x1, double x2, double y1, double y2, double* x_min, double* y_min);
bool cut(const expr* e1, const expr* e2, 
    double x1, double x2, double y1, double y2);

void replot_functions(void);
void plot_function(expr e, int index);
void plot_implicit(expr e1, expr e2, int index);
void add_plot(char* cmd);

void draw_axis(void);
void draw_axis_numbers(void);

void show_options(void);

void init_plotter(void);
void clean_plotter(void);


#endif
