#include "command.h"

void nothing(char * arg){;}

struct{
  char name[10];
  void (*func)(char * arg);
} cmds[CMDS_NUM] = {{"nop", nothing},
                     {"plot", add_function}};


void run_command(char * command){
  int cmd = 0, i;
  for(i = 0; i<CMDS_NUM; i++){
    if(strstr(command, cmds[i].name) != NULL){
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



void input_command(){
  int ch;
  int i = 0;
  int height = options.height;
  wprintf(height-1, 0, BW, ":");
  update_ui();
  char command[500]; 

  while((ch = w_getch()) != 10){
    if(ch == 127){ //backspace
      i--;
      wprintf(height-1, i+1, BW, " ");
      wprintf(height-1, i+1, BW, "");
    } else if(ch == KEY_UP){
    } else{
      wprintf(height-1, i+1, BW, "%c", ch);
      command[i] = ch;
      i++;
    }
    update_ui();
  }
  command[i] = '\0'; 



  run_command(command);
}



