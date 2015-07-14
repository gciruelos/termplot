#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "ui_curses.h"
#include "options.h"
#include "input.h"
#include "plot.h"

double square(double x){ return x*x;}


int main(int argc, char* argv[]){
  start_curses();
  init_structs();
  init_plotter();

  int row,col;
  int x;
  while (true) {
    clear();

    getmaxyx(stdscr,row,col); 
    
    draw_axis(col, row-1);

    replot_functions(col, row-1);

    x = input_action(row);
    if(x == -1) break;
    
    refresh();
  } 

  end_curses();
  clean_plotter();
}
