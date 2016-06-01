#ifndef UI_NCURSES
#define UI_NCURSES

#include <ncurses.h>

#include "../structs.h"
#include "../ui.h"

#define BW 0
#define ENTER 10
#define FG_WHITE BW
#define BG_BLACK BW

WINDOW* win;
bool curses_started;

void start_ui();
void end_ui();
int w_getch();
void set_terminal_size();
void prepare_paint();
void paint_string(struct buffer_entry* b);
void finish_paint();
void term_clear();
void term_refresh();

#endif
