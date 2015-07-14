#include "plot.h"

void add_function(char * cmd){
  struct function new;
  new.f = parse(cmd);
  new.valid = 1;

  int i;
  for(i = 0; i<32; i++){
    if(!functions[i].valid){
      functions[i] = new;
      break;
    }
  }
}




void replot_functions(int width, int height){

  int i;
  for(i = 0; i<32; i++){
    if(functions[i].valid)
      plot_function(functions[i].f, width, height);
  }
}

void plot_function(expr e, int width, int height){
  
  static double epsilon = 0.001;
  static double threshold = 4.0; // derivative threshold, "4 is big"

  int x, y;
  double x_, y_;
  double dx_;

  double dx_zoom = options.y_zoom/options.x_zoom;

  for(x = 0; x<width; x++){
    x_ = options.x_center + options.x_zoom * (x - width/2);
    y_ = eval(e, x_);

    y = height/2 + (options.y_center - y_)/options.y_zoom;

    dx_ = (eval(e, x_+epsilon)-eval(e, x_))/epsilon;

    if(dx_ < dx_zoom/threshold &&  dx_ > -dx_zoom/threshold ){
      mvprintw(y+1, x, "_");
    } else if(dx_ > dx_zoom/threshold && dx_ < dx_zoom*threshold){
      mvprintw(y, x, "/");
    } else if(dx_ < -dx_zoom/threshold && dx_ > -dx_zoom*threshold){
      mvprintw(y, x, "\\");
    } else{
      mvprintw(y, x, "|");
    }
  }
}

