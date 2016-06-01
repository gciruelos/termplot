#include "ui.h"

/*
 *  Terminal to Reals
 *  -----------------
 *
 *  x -> options.x_center + options.x_zoom * (x - width / 2));
 *  y -> options.y_center + options.y_zoom * (height / 2 - y));
 *
 *
 *  Reals to Terminal
 *  -----------------
 *
 *  Inverses of the ones before
 *
 */

#define IN_RANGE(x, y) \
  ((x)>=0 && (x)<options.width && (y)>=0 && (y)<options.height)
#define BUFFER_SIZE 1000
#define MAX_LEN 300

struct buffer_entry* print_buffer[BUFFER_SIZE];
unsigned int buffer_next;

inline void update_cmd() {
  prepare_paint();
  struct buffer_entry b = {
    .buf = command,
    .x = 0,
    .y = options.height-1,
    .fg_color = FG_WHITE,
    .bg_color = BG_BLACK
  };
  paint_string(&b);
  finish_paint(1);
}

void wcprintf(int y, int x, unsigned int fg_color, unsigned int bg_color,
              char* fmt, ...) {
  if (IN_RANGE(x,y)) {
    struct buffer_entry* b = print_buffer[buffer_next++];

    va_list args;
    va_start(args, fmt);
    vsprintf(b->buf, fmt, args);
    va_end(args);

    b->y = y;
    b->x = x;
    b->fg_color = fg_color;
    b->bg_color = bg_color;
  }
}


inline int input() {
  static double zoom_factor = 0.1;
  int ch = w_getch();

  switch (ch) {
    case ERR:
      return -2;
    case 'q':
      return -1;
    case 'z':
    case '+':
      options.x_zoom -= options.x_zoom*zoom_factor;
      options.y_zoom -= options.y_zoom*zoom_factor;
      break;
    case 'x':
    case '-':
      options.x_zoom += options.x_zoom*zoom_factor/(1-zoom_factor);
      options.y_zoom += options.y_zoom*zoom_factor/(1-zoom_factor);
      break;
    case KEY_UP:
      options.y_center += options.y_zoom;
      break;
    case KEY_DOWN:
      options.y_center -= options.y_zoom;
      break;
    case KEY_RIGHT:
      options.x_center += options.x_zoom;
      break;
    case KEY_LEFT:
      options.x_center -= options.x_zoom;
      break;
    case ':':
      input_command();
      break;
  }

  return 0;  /* Everyting went fine. */
}

void init_ui() {
  start_ui();

  for (int i = 0; i < BUFFER_SIZE; i++) {
    print_buffer[i] = malloc(sizeof(struct buffer_entry));
    print_buffer[i]->buf = calloc(MAX_LEN, sizeof(char));
  }

  buffer_next = 0;

  hist_last = -1;
  hist_first = 0;
  for (int i = 0; i < CMD_HIST; i++) {
    command_history[i] = calloc(CMD_SIZE, sizeof(char));
  }
}


void clean_ui() {
  int i;

  for (i = 0; i < CMD_HIST; i++) {
    free(command_history[i]);
  }

  for (i = 0; i < BUFFER_SIZE; i++) {
    free(print_buffer[i]->buf);
    print_buffer[i]->buf = NULL;
    free(print_buffer[i]);
    print_buffer[i] = NULL;
  }
  end_ui();
}

inline void update_ui() {
  unsigned int i;
  struct buffer_entry* b;

  prepare_paint();
  for (i = 0; i < buffer_next; i++) {
    b = print_buffer[i];
    paint_string(b);
  }
  buffer_next = 0;
  finish_paint(0);
}

#ifndef INCL_TERMBOX
/* CURSES FUNCTIONS */
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

inline void paint_string(const struct buffer_entry* b) {
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

#else
/* TERMBOX FUNCTIONS */
void start_ui() {
  tb_init();
}

void end_ui() {
  tb_shutdown();
}

inline int w_getch() {
  struct tb_event event;
  while (TB_EVENT_KEY != tb_poll_event(&event)) {
    if (event.type == TB_EVENT_RESIZE) {
      options.height = event.h;
      options.width = event.w;
      tb_clear();
      draw_axis();
      replot_functions();
    }
  }
  return event.ch ? event.ch : event.key;
}

inline void set_terminal_size() {
  options.height = tb_height();
  options.width = tb_width();
}

inline void prepare_paint() {
}

inline void paint_string(const struct buffer_entry* b) {
  int x = b->x;
  int y = b->y;
  for (int i = 0; b->buf[i] != '\0'; i++) {
    tb_change_cell(x, y, b->buf[i], b->fg_color, b->bg_color);
    x++;
  }
}

inline void finish_paint(int is_cmd) {
  if (is_cmd) {
    tb_set_cursor(cursor, options.height - 1);
  } else {
    tb_set_cursor(TB_HIDE_CURSOR, TB_HIDE_CURSOR);
  }
  tb_present();
}

inline void term_clear() {
  tb_clear();
}

inline void term_refresh() {
  tb_present();
}

#endif

