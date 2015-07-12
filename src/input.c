#include "input.h"

void input_command(int height){
  int ch;
  int i = 1;
  mvprintw(height-1, 0, ":");
  while((ch = getch()) != 10){
    if(ch == 127){
      i--;
      mvprintw(height-1, i, " ");
      mvprintw(height-1, i, "");
    } else{
      mvprintw(height-1, i, "%c", ch);
      i++;
    }
  }
}


int input_action(int height){
  static double zoom_factor = 0.1;

  int ch = getch();
  if (ch == ERR) return -2;
  else if(ch == 'q') return -1;
  else if(ch == 'z' || ch == '+'){
    options.x_zoom -= options.x_zoom*zoom_factor;
    options.y_zoom -= options.y_zoom*zoom_factor;
  } else if(ch == 'x' || ch == '-'){
    options.x_zoom += options.x_zoom*zoom_factor/(1-zoom_factor);
    options.y_zoom += options.y_zoom*zoom_factor/(1-zoom_factor);
  } else if(ch == KEY_UP){
    options.y_center += options.y_zoom;
  } else if(ch == KEY_DOWN){
    options.y_center -= options.y_zoom;
  } else if(ch == KEY_RIGHT){
    options.x_center += options.x_zoom;
  } else if(ch == KEY_LEFT){
    options.x_center -= options.x_zoom;
  } else if(ch == ':'){
    input_command(height);
  }

  return 0; // everyting went fine
}

