#ifndef UI
#define UI

#ifndef INCL_TERMBOX
  #include <ncurses.h>
#else
  #include <termbox.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "options.h"

#define BW 0

struct buffer_entry {
  char* buf;
  int x;
  int y;
  unsigned int fg_color;
  unsigned int bg_color;
};

void init_ui();
void clean_ui();
int input();
void wcprintf(int y, int x, unsigned int fg_color, unsigned int bg_color,
              char* fmt, ...);
void update_cmd();
void update_ui();

/* INTERFACE FUNCTIONS */
void start_ui();
void end_ui();
int w_getch();
void set_terminal_size();
void prepare_paint();
void paint_string(const struct buffer_entry* b);
void finish_paint();
void term_clear();
void term_refresh();

#ifndef INCL_TERMBOX
  /* CURSES FUNCTIONS */
  WINDOW* win;
  bool curses_started;
  #define ENTER 10
  #define FG_WHITE BW
  #define BG_BLACK BW
#else
  #define ERR 0
  #define KEY_UP TB_KEY_ARROW_UP 
  #define KEY_DOWN TB_KEY_ARROW_DOWN
  #define KEY_RIGHT TB_KEY_ARROW_RIGHT
  #define KEY_LEFT TB_KEY_ARROW_LEFT
  #define KEY_DC TB_KEY_DELETE
  #define ENTER TB_KEY_ENTER
  #define FG_WHITE TB_WHITE
  #define BG_BLACK TB_DEFAULT
#endif

#endif
