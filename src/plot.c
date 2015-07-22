#include "plot.h"

void add_function(char * cmd){
  struct function new;
  new.f = parse(cmd);
  new.valid = 0;

  if(new.f.size > 0){
    new.valid = 1;
    int i;
    for(i = 0; i<MAX_FUNCTIONS; i++){
      if(!functions[i].valid){
        functions[i] = new;
        break;
      }
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

  int x, y, last_y = 0;
  double x_, y_;
  double dx_;

  double dx_zoom = options.y_zoom/options.x_zoom;


  int color = index%16 + 1;

  for(x = 0; x<width; x++){
    x_ = options.x_center + options.x_zoom * (x - width/2);
    y_ = eval(e, x_);

    y = height/2 + (options.y_center - y_)/options.y_zoom;


    dx_ = (eval(e, x_+epsilon)-eval(e, x_))/epsilon;


/*    if(x>0){
      int yi;
      for(yi = last_y+1; yi<y;y++) wprintf(yi, x, color, "x");
    }
*/
    if(dx_ < dx_zoom/threshold &&  dx_ > -dx_zoom/threshold ){
      wprintf(y+1, x, color, "_");
    } else if(dx_ > dx_zoom/threshold && dx_ < dx_zoom*threshold){
      wprintf(y, x, color, "/");
    } else if(dx_ < -dx_zoom/threshold && dx_ > -dx_zoom*threshold){
      wprintf(y, x, color, "\\");
    } else{
      wprintf(y, x, color, "|");
    }

    last_y = y;
  }

  wprintf(1+index, 0, BW, "%d", index); 
  wprintf(1+index, 2, color, "f(x) = %s", e.str); 

  update_ui();
}


void draw_axis(){
  int h = options.height;
  int w = options.width;

  int y, x;
  int x_0 = w/2 - options.x_center/options.x_zoom;
  int y_0 = h/2 + options.y_center/options.y_zoom; 

  for(y = 0; y<h; y++) wprintf(y, x_0, BW, "|");
  update_ui();
   
  for(x = 0; x<w; x++) wprintf(y_0, x, BW, "-");
  update_ui();
 
  
  
  for(x = 0; x<w; x+=10){
    if(y_0<0){
      wprintf(1, x, BW, "%.3f", options.x_center + options.x_zoom * (x-w/2));
    } else if(y_0>=h-2){
      wprintf(h-2, x, BW, "%.3f", options.x_center + options.x_zoom * (x-w/2));
    } else{
      wprintf(y_0+1, x, BW, "%.3f", options.x_center + options.x_zoom * (x-w/2));
    }
  }
  update_ui();


  for(y = 0; y<h; y+=3){ 
    if(x_0<0){
      wprintf(y, 0, BW, " %.3f", options.y_center + options.y_zoom * (h/2-y));
    } else if(x_0>=w-10){
      wprintf(y, w-10, BW, " %.3f", options.y_center + options.y_zoom * (h/2-y));
    } else{
      wprintf(y, x_0+1, BW, " %.3f", options.y_center + options.y_zoom * (h/2-y));
    }
  }
  update_ui();

}



void delete_function(unsigned int i){
  if(i < MAX_FUNCTIONS){
    if(functions[i].valid){
     delete_expr(&(functions[i].f));
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



