#ifndef UI_CURSES
#define UI_CURSES
#include <stdlib.h>
#include <ncurses.h>
#include <stdio.h>

#include "options.h"
#include "command.h"


#define BW 0


WINDOW * win;
bool curses_started;

void end_curses();
void start_curses();

void init_ui();
void clean_ui();


void update_ui();

int input();
void input_command();



void set_terminal_size();

void wprintf(int y, int x, unsigned int color, char * fmt, ...);
#endif
