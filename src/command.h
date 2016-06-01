#include <string.h>
#include <ctype.h>

#include "debug.h"
#include "options.h"
#include "plot.h"
#include "ui.h"

#define CMDS_NUM sizeof(cmds)/sizeof(cmds[0])
#define CMD_HIST 10
#define CMD_SIZE 500

char * command_history[CMD_HIST];
unsigned int hist_last, hist_first;
// Kind of bounded stack.

char command[CMD_SIZE];
unsigned int cursor;

void run_command(void);
void input_command(void);
