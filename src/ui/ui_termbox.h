#ifndef UI_TERMBOX
#define UI_TERMBOX

#include <termbox.h>

#include "../structs.h"
#include "../ui.h"

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
