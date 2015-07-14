#include "ui_curses.h"

/*  
 *  Terminal to Reals
 *  -----------------
 *
 *  x -> options.x_center + options.x_zoom * (x - width/2));
 *  y -> options.y_center + options.y_zoom * (height/2-y));
 *     
 *
 *  Reals to Terminal
 *  -----------------
 *  
 *  Inverses of the ones before
 *
 */

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
  int x_0 = width/2  - options.x_center/options.x_zoom;
  int y_0 = height/2 + options.y_center/options.y_zoom;
  
  for(y = 0; y<height; y++){
    mvprintw(y, x_0, "|");
  }
   
  for(x = 0; x<width; x++){
   mvprintw(y_0, x, "-");
  }
  mvprintw(y_0, x_0, "+");

  for(x = 0; x<width; x+=10){ 
   mvprintw(y_0+1, x, "%.3f", options.x_center + options.x_zoom * (x - width/2));
  }

  for(y = 0; y<height; y+=3){ 
   mvprintw(y, x_0+1, " %.3f", options.y_center + options.y_zoom * (height/2-y));
  }

}

