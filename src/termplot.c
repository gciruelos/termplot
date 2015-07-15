#include <stdio.h>
#include "ui_curses.h"
#include "options.h"
#include "plot.h"

int main(int argc, char* argv[]){
  start_curses();
  init_ui();
  init_structs();
  init_plotter();
  
  int x;
  while (true) {
    clear();

    set_terminal_size();
    
    draw_axis();
    replot_functions();

    x = input();
    if(x == -1) break;
    
    refresh();
  } 

  clean_plotter();
  clean_ui();
  end_curses(); 

  return 0;
}
