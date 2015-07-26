#include <stdio.h>
#include <string.h>
#include "ui.h"
#include "options.h"
#include "plot.h"
#include "debug.h"


int parse_args(int argc, char* argv[]){
    unsigned int i;

    for(i = 1; i<argc; i++){
      if(strcmp(argv[i], "--debug") == 0){
        debug_enabled = 1;
      }
    }
}


int main(int argc, char* argv[]){
  parse_args(argc, argv);
  
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
  } 

  clean_plotter();
  clean_ui();
  return 0;
}
