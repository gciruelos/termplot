#include "command.h"

#define CMDS_SIZE 1

struct{
  char name[10];
  void (*func)(char * arg);
} cmds[CMDS_SIZE] = {{"plot", add_function}};


void run_command(char * command){
  int cmd = -1;

  int i;
  for(i = 0; i<CMDS_SIZE; i++){
    if(strstr(command, cmds[i].name) != NULL){
      cmd = i;
      break;
    }
  }

  char * args = NULL;
  if(cmd >= 0){
    args = command + strspn(command, cmds[cmd].name);
  }
  while(isspace(*args)) args++;

  if(cmd == 0){
    cmds[cmd].func(args);
  }

}

