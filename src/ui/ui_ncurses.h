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

void start_ui(void);
void end_ui(void);
int w_getch(void);
void set_terminal_size(void);
void prepare_paint(void);
void paint_string(struct buffer_entry* b);
void finish_paint(int cmd_length);
void term_clear(void);
void term_refresh(void);

#endif
