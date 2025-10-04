#pragma once

struct buffer_entry {
  char* buf;
  int x;
  int y;
  unsigned int fg_color;
  unsigned int bg_color;
};

struct options_t {
  double x_center;
  double y_center;
  double x_zoom;
  double y_zoom;

  int width;
  int height;

  bool quit;
  bool show_info;
  double cpu_time_draw; 
};
