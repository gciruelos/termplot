#ifndef UI
#define UI

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "options.h"
#include "structs.h"
#ifndef INCL_TERMBOX
  #include "ui/ui_ncurses.h"
#else
  #include "ui/ui_termbox.h"
#endif

void init_ui(void);
void clean_ui(void);
int input(void);
void wcprintf(int y, int x, unsigned int fg_color, unsigned int bg_color,
              char* fmt, ...);
void update_cmd(void);
void update_ui(void);

#endif
