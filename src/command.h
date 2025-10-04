#pragma once
#include <ctype.h>

#include "debug.h"
#include "options.h"
#include "plot.h"
#include "ui.h"

#define CMDS_NUM sizeof(cmds)/sizeof(cmds[0])
#define CMD_HIST 10
#define CMD_SIZE 500

struct {
  // Kind of bounded stack.
  char* commands[CMD_HIST];
  unsigned int last;
  unsigned int first;
} command_history;

char command[CMD_SIZE];
unsigned int cursor;

void run_command(void);
void input_command(void);
