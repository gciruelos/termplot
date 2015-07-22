#include "command.h"

void nothing(char * arg){;}

struct{
  char name[10];
  void (*func)(char * arg);
} cmds[CMDS_NUM] = {{"nop", nothing},
                    {"plot", add_function}};


void run_command(){
  char * cmdptr = &command[1]; //medio cabeza
  int cmd = 0, i;
  for(i = 0; i<CMDS_NUM; i++){
    if(strstr(cmdptr, cmds[i].name) != NULL){
      cmd = i;
      break;
    }
  }

  d_print("cmd: %d - %s\n", cmd, cmds[cmd].name);

  char * args = NULL;
  args = cmdptr + strspn(cmdptr, cmds[cmd].name);
  
  while(isspace(*args)) args++;

  cmds[cmd].func(args);
}



void input_command(){
  int ch;
  unsigned int i;

  for(i = 0; i<500;i++) command[i] = '\0';

  command[0] = ':';
  command[1] = '\0';
  cursor = 1;
  update_cmd();

  while((ch = w_getch()) != 10){
    if(ch == 127){ // backspace
      i = cursor-1;
      while(command[i]){
        command[i] = command[i+1];
        i++;
      }
      cursor--;
    } else if(ch == KEY_DC){ // delete
      i = cursor;
      while(command[i]){
        command[i] = command[i+1];
        i++;
      }
    } else if(ch == KEY_UP){
    } else if(ch == KEY_LEFT){
      cursor--;
    } else if(ch == KEY_RIGHT){
      if(command[cursor]) cursor++;
    } else{
      i = strlen(command)+1; 
      while(i>cursor){
        command[i] = command[i-1];
        i--;
      }
      command[cursor++] = ch;
    }
    update_cmd(); 
    if(cursor==0) break;
  }
  
  if(strlen(command)>1) run_command();
}


