#ifndef OPTIONS
#define OPTIONS

#include <stdbool.h>

struct {
  double x_center;
  double y_center;
  double x_zoom;
  double y_zoom;

  int width;
  int height;

  bool quit;
  bool show_info;
  double cpu_time_draw; 
} options;

void init_structs(void);

#endif
