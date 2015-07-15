#include "plot.h"

void add_function(char * cmd){
  struct function new;
  new.f = parse(cmd);
  new.valid = 1;

  int i;
  for(i = 0; i<MAX_FUNCTIONS; i++){
    if(!functions[i].valid){
      functions[i] = new;
      break;
    }
  }
}




void replot_functions(){
  int i;
  for(i = 0; i<MAX_FUNCTIONS; i++){
    if(functions[i].valid)
      plot_function(functions[i].f, i);
  }
}

void plot_function(expr e, int index){
  static double epsilon = 0.001;
  static double threshold = 4.0; // derivative threshold, "4 is big"


  int height = options.height;
  int width = options.width;

  int x, y;
  double x_, y_;
  double dx_;

  double dx_zoom = options.y_zoom/options.x_zoom;


  int color = index%16 + 1;

  for(x = 0; x<width; x++){
    x_ = options.x_center + options.x_zoom * (x - width/2);
    y_ = eval(e, x_);

    y = height/2 + (options.y_center - y_)/options.y_zoom;

    dx_ = (eval(e, x_+epsilon)-eval(e, x_))/epsilon;

    if(dx_ < dx_zoom/threshold &&  dx_ > -dx_zoom/threshold ){
      wshowchc(y+1, x, color, '_');
    } else if(dx_ > dx_zoom/threshold && dx_ < dx_zoom*threshold){
      wshowchc(y, x, color, '/');
    } else if(dx_ < -dx_zoom/threshold && dx_ > -dx_zoom*threshold){
      wshowchc(y, x, color, '\\');
    } else{
      wshowchc(y, x, color, '|');
    }
  }


  show_function_list(index, color, e.str);
}

void delete_function(unsigned int i){
  if(i < MAX_FUNCTIONS){
    if(functions[i].valid){
     delete_expr(functions[i].f);
     functions[i].valid = 0;
    }
  }
}

void init_plotter(){
  unsigned int i;
  for(i = 0; i<MAX_FUNCTIONS; i++){
    functions[i].valid = 0;
  }
}

void clean_plotter(){
  unsigned int i;
  for(i = 0; i<MAX_FUNCTIONS;i++){
    delete_function(i);
  }
}



