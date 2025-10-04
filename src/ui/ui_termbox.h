#pragma once

#include <termbox.h>
#include <stdbool.h>

#include "../structs.h"

#define BW 0
#define ERR 0
#define KEY_UP TB_KEY_ARROW_UP 
#define KEY_DOWN TB_KEY_ARROW_DOWN
#define KEY_RIGHT TB_KEY_ARROW_RIGHT
#define KEY_LEFT TB_KEY_ARROW_LEFT
#define KEY_DC TB_KEY_DELETE
#define ENTER TB_KEY_ENTER
#define FG_WHITE TB_WHITE
#define BG_BLACK TB_DEFAULT

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

