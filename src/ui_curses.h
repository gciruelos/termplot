#include <stdlib.h>
#include <ncurses.h>


#include "options.h"
#include "parser.h"

typedef struct plot_t{
  double (*f)(double);
  bool valid;
} plot;

plot plots[32]; 


WINDOW * win;
bool curses_started;

void end_curses();
void start_curses();


void draw_axis(int width, int height);

