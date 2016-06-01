#include "ui_termbox.h"

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

inline void paint_string(struct buffer_entry* b) {
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
