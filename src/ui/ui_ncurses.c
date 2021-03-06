#include "ui_ncurses.h"

#include <stdlib.h>

void start_ui(void) {
  if (curses_started) {
    refresh();
  } else {
    win = initscr();
    start_color();
    cbreak();
    noecho();
    intrflush(stdscr, false);
    keypad(stdscr, true);
    atexit(end_ui);
    curses_started = true;
  }

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      init_pair(j * 16 + i, i, j); /* bg * 16 + fg */
    }
  }
}

void end_ui(void) {
  if (curses_started && !isendwin()) {
    delwin(win);
    endwin();
    refresh();
  }
}

inline int w_getch(struct options_t* options) {
  (void) options;
  return getch();
}

void set_terminal_size(struct options_t* options) {
  getmaxyx(stdscr, options->height, options->width);
}

inline void prepare_paint(void) {
  curs_set(1);
}

inline void paint_string(struct buffer_entry* b) {
  int color = (b->fg_color == BW ? BW : (b->fg_color - 2) % 16 + 1);
  attron(COLOR_PAIR(color));
  mvaddstr(b->y, b->x, b->buf);
  attroff(COLOR_PAIR(color));
}

void finish_paint(int cmd_length, unsigned int cursor, struct options_t opts) {
  curs_set(cmd_length ? 1 : 0);
  if (cmd_length) {
    clrtoeol();
    move(opts.height - 1, cursor);
  }
  refresh();
}

inline void term_clear(void) {
  clear();
}

inline void term_refresh(void) {
  refresh();
}

inline bool should_redraw(void) {
  return false;
}
