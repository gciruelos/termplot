#ifndef UI
#define UI

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "options.h"

void init_ui();
void clean_ui();


/* INTERFACE FUNCTIONS */
int input();
void wcprintf(int y, int x, unsigned int color, char* fmt, ...);
void update_cmd();


void set_terminal_size();
void update_ui();
int w_getch();

/* CURSES FUNCTIONS */
#define BW 0
WINDOW* win;
bool curses_started;

void start_ui();
void end_ui();


#endif
