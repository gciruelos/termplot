#include <string.h>
#include <ctype.h>

#include "options.h"
#include "plot.h"
#include "ui.h"

#include "debug.h"


#define CMDS_NUM 2
#define CMD_HIST 10

char * command_history[CMD_HIST];
unsigned int hist_last, hist_first;
// kind of bounded stack


void run_command(char * command);
void input_command();



