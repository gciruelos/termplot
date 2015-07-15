#include "command.h"

#define CMDS_SIZE 2

void nothing(char * arg){;}

struct{
  char name[10];
  void (*func)(char * arg);
} cmds[CMDS_SIZE] = {{"nop", nothing},
                     {"plot", add_function}};


void run_command(char * command){
  int cmd = 0;

  int i;
  for(i = 0; i<CMDS_SIZE; i++){
    
    d_print("searching command: %d - %s\n", cmd, cmds[i].name);
    if(strstr(command, cmds[i].name) != NULL){

      d_print("found! %d - %s\n", cmd, cmds[i].name);
      cmd = i;
      break;
    }
  }

  d_print("cmd: %d - %s\n", cmd, cmds[cmd].name);

  char * args = NULL;
  args = command + strspn(command, cmds[cmd].name);
  
  while(isspace(*args)) args++;

  cmds[cmd].func(args);
  

}

