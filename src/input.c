#include "input.h"


void input_command(int height){
  int ch;
  int i = 0;
  mvprintw(height-1, 0, ":");

  char command[500]; 

  while((ch = getch()) != 10){
    if(ch == 127){
      i--;
      mvprintw(height-1, i+1, " ");
      mvprintw(height-1, i+1, "");
    } else{
      mvprintw(height-1, i+1, "%c", ch);
      command[i] = ch;
      i++;
    }
  }
  command[i] = '\0';
}


int input_action(int height){
  static double zoom_factor = 0.1;

  int ch = getch();
  switch(ch){
    case ERR: return -2;
    case 'q': return -1;
    case 'z':
    case '+':
      options.x_zoom -= options.x_zoom*zoom_factor;
      options.y_zoom -= options.y_zoom*zoom_factor;
      break;
    case 'x':
    case '-':
      options.x_zoom += options.x_zoom*zoom_factor/(1-zoom_factor);
      options.y_zoom += options.y_zoom*zoom_factor/(1-zoom_factor);
      break;
    case KEY_UP:
      options.y_center += options.y_zoom;
      break;
    case KEY_DOWN:
      options.y_center -= options.y_zoom;
      break;
    case KEY_RIGHT:
      options.x_center += options.x_zoom;
      break;
    case KEY_LEFT:
      options.x_center -= options.x_zoom;
      break;
    case ':':
      input_command(height);
      break;
  }

  return 0; // everyting went fine
}

