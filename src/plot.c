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


#define MAX(x,y) (x)>(y)?(x):(y)
void plot_function(expr e, int index){
  //static double epsilon = 0.001;
  //static double threshold = 4.0; // derivative threshold, "4 is big"

  static char c[1] = "#";

  int height = options.height;
  int width = options.width;

  int x, y, yi, last_y = 0;
  double x_, y_;
  double dx_;

  double dx_zoom = options.y_zoom/options.x_zoom;

  int color = index%16 + 1;


  wprintf(0,0,BW, "plotting...");
  update_ui();

  for(x = -1; x<width; x++){
    x_ = options.x_center + options.x_zoom * (x - width/2);
    y_ = eval(e, x_);

    y = height/2 + (options.y_center - y_)/options.y_zoom;

    if(x>=0 && ((y>=0 && y<height) || (last_y>=0 && last_y<height))){
      wprintf(y, x, color, c);
      if(y>last_y+1)
        for(yi=MAX(last_y+1,0); yi<y && yi<height; yi++) wprintf(yi, x, color, c);
      
      else if(y<last_y-1)
        for(yi=MAX(y+1,0); yi<last_y && yi<height; yi++) wprintf(yi, x, color, c);
      update_ui();
    }



/*  
    dx_ = (eval(e, x_+epsilon)-eval(e, x_))/epsilon;
    if(dx_ < dx_zoom/threshold &&  dx_ > -dx_zoom/threshold ){
      wprintf(y+1, x, color, "_");
    } else if(dx_ > dx_zoom/threshold && dx_ < dx_zoom*threshold){
      wprintf(y, x, color, "/");
    } else if(dx_ < -dx_zoom/threshold && dx_ > -dx_zoom*threshold){
      wprintf(y, x, color, "\\");
    } else{
      wprintf(y, x, color, "|");
    }
*/ 
    last_y = y;
  }

  wprintf(0,0,BW, "           ");
  wprintf(1+index, 0, BW, "%d", index); 
  wprintf(1+index, 2, color, "f(x) = %s", e.str); 

  update_ui();
}


void draw_axis(){
  int h = options.height;
  int w = options.width;

  double xz = options.x_zoom;
  double yz = options.y_zoom;

  int y, x;
  int x_0 = w/2 - options.x_center/xz;
  int y_0 = h/2 + options.y_center/yz; 

  for(y = 0; y<h; y++) wprintf(y, x_0, BW, "|");
  update_ui();
   
  for(x = 0; x<w; x++) wprintf(y_0, x, BW, "-");
  update_ui();
   
  
  for(x = 0; x<w-14; x+=15){
    int y_ = y_0<0 ? 1 : y_0>=h-2 ? h-2 : y_0+1;
    
    wprintf(y_, x, BW, xz>10||xz<0.001? "%.3e": "%.3f", options.x_center + options.x_zoom * (x-w/2));
  }
  update_ui();

  for(y = 0; y<h; y+=3){
    int x_ = x_0<0? 0 : x_0>=w-15? w-15 : x_0+1;
    wprintf(y, x_, BW, yz > 10||yz<0.001? " %.3e" : " %.3f", options.y_center + options.y_zoom * (h/2-y)); 
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



