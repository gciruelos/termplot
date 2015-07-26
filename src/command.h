#include <string.h>
#include <ctype.h>

#include "options.h"
#include "plot.h"
#include "ui.h"

#include "debug.h"


#define CMDS_NUM 5
#define CMD_HIST 10
#define CMD_SIZE 500

char * command_history[CMD_HIST];
unsigned int hist_last, hist_first;
// kind of bounded stack

char command[CMD_SIZE];
unsigned int cursor;

void run_command();
void input_command();



