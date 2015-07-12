#include <stdlib.h>
#include <stdbool.h>

#include "ui_curses.h"
#include "options.h"


int input_action(){
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
    options.x_center += options.x_zoom;
  }


  return 0; // everyting went fine
}



int main(int argc, char* argv[]){
  start_curses();
  init_structs();

  int row,col;
  int x;
  while (true) {
    clear();


    getmaxyx(stdscr,row,col);

    draw_axis(col, row);

    x = input_action();
    if(x == -1) break;
    
    refresh();
  } 

  end_curses();
}
