#include "options.h"

void init_structs(void) {
  options.x_center = 0.0;
  options.y_center = 0.0;
  options.x_zoom = 0.1;
  options.y_zoom = 0.2;

  options.quit = false;
  options.show_info = false;
  options.cpu_time_draw = 0.0;
}

