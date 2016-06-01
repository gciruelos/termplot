void start_ui() {
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

void end_ui() {
  if (curses_started && !isendwin()) {
    delwin(win);
    endwin();
    refresh();
  }
}

inline int w_getch() {
  return getch();
}

inline void set_terminal_size() {
  getmaxyx(stdscr, options.height, options.width);
}

inline void prepare_paint() {
  curs_set(1);
}

inline void paint_string(struct buffer_entry* b) {
  int color = (b->fg_color == BW ? BW : (b->fg_color - 2) % 16 + 1);
  attron(COLOR_PAIR(color));
  mvaddstr(b->y, b->x, b->buf);
  attroff(COLOR_PAIR(color));
}

inline void finish_paint(int is_cmd) {
  curs_set(is_cmd ? 1 : 0);
  if (is_cmd) {
    clrtoeol();
    move(options.height - 1, cursor);
  }
  refresh();
}

inline void term_clear() {
  clear();
}

inline void term_refresh() {
  refresh();
}
