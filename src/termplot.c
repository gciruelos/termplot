#include <stdio.h>
#include "ui.h"
#include "options.h"
#include "plot.h"
#include "debug.h"

int main(int argc, char* argv[]){
  init_ui();
  init_structs();
  init_plotter();

  start_debug();
  
  int x;
  while (!options.quit) {
    clear();

    set_terminal_size();
    
    draw_axis();
    replot_functions();

    x = input();
    if(x == -1) break;
    
    refresh();
    d_print("quit: %d\n", options.quit);
  } 

  clean_plotter();
  clean_ui();
  return 0;
}
