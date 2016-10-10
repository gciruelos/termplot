#include "command.h"

#include <stdlib.h>
#include <string.h>

void nothing(__attribute__((unused)) char* arg) {
}
void quit(__attribute__((unused)) char* arg) {
  options.quit = 1;
}

struct {
  char name[10];
  void (*func)(char* arg);
} cmds[] = {
  { .name = "nop",    .func = nothing },
  { .name = "plot",   .func = add_plot },
  { .name = "remove", .func = remove_plot },
  { .name = "quit",   .func = quit },
  { .name = "q",      .func = quit }
};

void run_command(void) {
  char* cmdptr = &command[1]; /* Medio cabeza. */
  int cmd = 0;
  for (unsigned int i = 0; i < CMDS_NUM; i++) {
    if (strstr(cmdptr, cmds[i].name) != NULL) {
      cmd = i;
      break;
    }
  }
  d_print("cmd: %d - %s\n", cmd, cmds[cmd].name);

  char* args = cmdptr + strspn(cmdptr, cmds[cmd].name);

  while (isspace(*args)) {
    args++;
  }
  cmds[cmd].func(args);
}

void input_command(void) {
  int ch;
  unsigned int i, current = command_history.last + 1;

  for (i = 0; i < CMD_SIZE; i++) {
    command[i] = '\0';
  }

  command[0] = ':';
  command[1] = '\0';
  cursor = 1;
  update_cmd();

  while ((ch = w_getch(&options)) != ENTER) {
    if (ch == 127) { /* backspace */
      i = cursor - 1;
      while (command[i]) {
        command[i] = command[i + 1];
        i++;
      }
      cursor--;
    } else if (ch == KEY_DC) { /* delete */
      i = cursor;
      while (command[i]) {
        command[i] = command[i + 1];
        i++;
      }
    } else if (ch == KEY_UP) {
      if (current != command_history.first) {
        current = (current - 1) % CMD_HIST;
        strncpy(command, command_history.commands[current], CMD_SIZE);
        cursor = strlen(command);
      }
    } else if (ch == KEY_DOWN) {
      if (current < command_history.last) {
        current = (current + 1) % CMD_HIST;
        strncpy(command, command_history.commands[current], CMD_SIZE);
        cursor = strlen(command);
      } else {
        command[1] = '\0';
        cursor = 1;
        if (current == command_history.last) {
          current = (current + 1) % CMD_HIST;
        }
      }
    } else if (ch == KEY_LEFT) {
      cursor--;
    } else if (ch == KEY_RIGHT) {
      if(command[cursor]) cursor++;
    } else {
      i = strlen(command) + 1;
      while (i > cursor) {
        command[i] = command[i - 1];
        i--;
      }
      command[cursor++] = ch;
    }

    update_ui();
    d_print("%d, %d\n", command_history.first, current);
    update_cmd();
    if(cursor==0) break;
  }

  if (strlen(command) > 1) {
    command_history.last = (command_history.last + 1) % CMD_HIST;
    /*if((command_history.last+1)%CMD_HIST == command_history.first) command_history.first = (command_history.first+1)%CMD_HIST;*/
    strncpy(command_history.commands[command_history.last], command, CMD_SIZE);
    run_command();
  }
}

