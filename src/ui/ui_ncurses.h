#ifndef UI_NCURSES
#define UI_NCURSES

#include <ncurses.h>

#include "../structs.h"

#define BW 0
#define ENTER 10
#define FG_WHITE BW
#define BG_BLACK BW

WINDOW* win;
bool curses_started;

void start_ui(void);
void end_ui(void);
int w_getch(struct options_t* options);
void set_terminal_size(struct options_t* options);
void prepare_paint(void);
void paint_string(struct buffer_entry* b);
void finish_paint(int cmd_length, unsigned int cursor, struct options_t opts);
void term_clear(void);
void term_refresh(void);
bool should_redraw(void);

#endif
