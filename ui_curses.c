#include "ui_curses.h"

void end_curses() {
  if (curses_started && !isendwin())
    delwin(win);
    endwin();
    refresh();
}

void start_curses() {
  if (curses_started) {
    refresh();
  }
  else {  
    win = initscr();
    start_color(); 
    cbreak();
    noecho();
    intrflush(stdscr, false);
    keypad(stdscr, true);
    atexit(end_curses);
    curses_started = true;
    }
}

void draw_axis(int width, int height){
  int y, x;
  for(y = 0; y<height; y++){
    mvprintw( y, width/2, "|");
  }
   
  for(x = 0; x<width; x++){
   mvprintw(height/2, x, "-");
  }
  mvprintw(height/2, width/2, "+");

  for(x = 0; x<width; x+=10){ 
   mvprintw(height/2+1, x, "%.3f", options.x_center + options.x_zoom * (x - width/2));
  }

  for(y = 0; y<height; y+=3){ 
   mvprintw(y, width/2+1, " %.3f", options.y_center + options.y_zoom * (height/2-y));
  }

}

