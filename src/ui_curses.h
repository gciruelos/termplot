#include <stdlib.h>
#include <ncurses.h>


#include "options.h"
#include "command.h"

WINDOW * win;
bool curses_started;

void end_curses();
void start_curses();



int input();
void input_command();

void draw_axis();


void set_terminal_size();

//show char with color
void wshowchc(int y, int x, int color, char ch);
void show_function_list(int index, int color, char * str); 

