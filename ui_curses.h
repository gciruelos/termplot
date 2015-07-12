#include <stdlib.h>
#include <ncurses.h>


#include "options.h"

WINDOW * win;
bool curses_started;

void end_curses();
void start_curses();
void draw_axis(int width, int height);
