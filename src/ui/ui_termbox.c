#include "ui_termbox.h"

void start_ui(void) {
  tb_init();
}

void end_ui(void) {
  tb_shutdown();
}

inline int w_getch(void) {
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

inline void set_terminal_size(void) {
  options.height = tb_height();
  options.width = tb_width();
}

inline void prepare_paint(void) {
}

inline void paint_string(struct buffer_entry* b) {
  int x = b->x;
  int y = b->y;
  for (int i = 0; b->buf[i] != '\0'; i++) {
    tb_change_cell(x, y, b->buf[i], b->fg_color, b->bg_color);
    x++;
  }
}

inline void finish_paint(int cmd_length) {
  if (cmd_length) {
    struct buffer_entry b = {
      .x = cmd_length,
      .y = options.height - 1,
      .buf = " ",
      .fg_color = FG_WHITE,
      .bg_color = BG_BLACK
    };
    for (int i = 0; i < options.width - 1 - cmd_length; i++) {
      paint_string(&b);
      b.x++;
    }
    tb_set_cursor(cursor, options.height - 1);
  } else {
    tb_set_cursor(TB_HIDE_CURSOR, TB_HIDE_CURSOR);
  }
  tb_present();
}

inline void term_clear(void) {
  tb_clear();
}

inline void term_refresh(void) {
  tb_present();
}
