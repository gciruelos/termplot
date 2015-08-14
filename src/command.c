#include "command.h"

void nothing(char * arg){;}

void quit(char * arg){
  options.quit = 1;
}

struct{
  char name[10];
  void (*func)(char * arg);
} cmds[] = {{"nop", nothing},
            {"plot", add_plot},
            {"quit", quit},
            {"q", quit}
           };

void run_command(){
  char * cmdptr = &command[1]; /*medio cabeza*/
  int cmd = 0, i;
  for(i = 0; i<CMDS_NUM; i++){
    if(strstr(cmdptr, cmds[i].name) != NULL){
      cmd = i;
      break;
    }
  }

  /* d_print("cmd: %d - %s\n", cmd, cmds[cmd].name); */

  char* args =  NULL;
  args = cmdptr + strspn(cmdptr, cmds[cmd].name);
  
  while(isspace(*args)) args++;

  cmds[cmd].func(args);
}



void input_command(){
  int ch;
  unsigned int i, current = hist_last+1;

  for(i = 0; i<CMD_SIZE; i++) command[i] = '\0';

  command[0] = ':';
  command[1] = '\0';
  cursor = 1;
  update_cmd();

  while((ch = w_getch()) != 10){
    if(ch == 127){ /* backspace */
      i = cursor-1;
      while(command[i]){
        command[i] = command[i+1];
        i++;
      }
      cursor--;
    } else if(ch == KEY_DC){ /* delete */
      i = cursor;
      while(command[i]){
        command[i] = command[i+1];
        i++;
      }
    } else if(ch == KEY_UP){  
      if(current!=hist_first){
        current = (current-1)%CMD_HIST;
        strcpy(command, command_history[current]);
        cursor = strlen(command);
      }
    } else if(ch == KEY_DOWN){
      if(current<hist_last){
        current = (current+1)%CMD_HIST;
        strcpy(command, command_history[current]);
        cursor = strlen(command);
      } else{
        command[1] = '\0';
        cursor = 1;
        if(current == hist_last) current = (current+1)%CMD_HIST;
      }
    }else if(ch == KEY_LEFT){
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
 
    update_ui();
    d_print("%d, %d\n", hist_first, current);
    update_cmd(); 
    if(cursor==0) break;
  }

  if(strlen(command)>1){ 
    hist_last = (hist_last+1)%CMD_HIST;
    /*if((hist_last+1)%CMD_HIST == hist_first) hist_first = (hist_first+1)%CMD_HIST;*/
    strcpy(command_history[hist_last], command);
    run_command();
  }
}


