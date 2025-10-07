#pragma once
#include <ctype.h>

#include "debug.h"
#include "options.h"
#include "plot.h"
#include "ui.h"

#define CMDS_NUM sizeof(cmds)/sizeof(cmds[0])
#define CMD_HIST 10
#define CMD_SIZE 500

typedef struct command_history_t {
  // Kind of bounded stack.
  char* commands[CMD_HIST];
  unsigned int last;
  unsigned int first;
} command_history_t;

extern command_history_t command_history;

extern char command[CMD_SIZE];
extern unsigned int cursor;

void run_command(void);
void input_command(void);
