#ifndef OPTIONS
#define OPTIONS

struct {
  double x_center;
  double y_center;
  double x_zoom;
  double y_zoom;

  int width;
  int height;

  int quit;
} options;

void init_structs(void);

#endif
