#include "plot.h"

#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))

void add_plot(char* cmd) {
  if (strchr(cmd, '=') == NULL) {
    struct function new;
    new.f = parse(cmd);
    /*new.g = y;*/

    new.type = EXPLICIT;
    new.valid = 0;

    if (new.f.size > 0) {
      new.valid = 1;
      int i;
      for (i = 0; i < MAX_FUNCTIONS; i++) {
        if (!functions[i].valid) {
          functions[i] = new;
          break;
        }
      }
    }
  } else {
    char* eq = strchr(cmd, '=');
    if (eq) {
      *eq = '\0';
      struct function new;
      new.f = parse(cmd);
      new.g = parse(eq+1);
      new.type = IMPLICIT;
      new.valid = 0;

      *eq = '=';

      if (new.f.size > 0) {
        new.valid = 1;
        int i;
        for (i = 0; i < MAX_FUNCTIONS; i++) {
          if (!functions[i].valid) {
            functions[i] = new;
            break;
          }
        }
      }
    }
  }
}


void replot_functions(void) {
  int i;
  for (i = 0; i < MAX_FUNCTIONS; i++) {
    if (functions[i].valid) {
      if (functions[i].type == EXPLICIT) {
        plot_function(functions[i].f, i);
      } else {
        plot_implicit(functions[i].f, functions[i].g, i);
      }
    }
  }
}

void plot_function(expr e, int index) {
  static char c[1] = "o";

  int height = options.height;
  int width = options.width;

  int x, y, yi, last_y = 0;
  double x_, y_;
  // double dx_;

  // double dx_zoom = options.y_zoom/options.x_zoom;

  // int color = index % 16 + 1;
  int color = index + 2;

  wcprintf(0, 0, FG_WHITE, BG_BLACK, "plotting...");
  update_ui();

  for (x = -1; x < width; x++) {
    x_ = options.x_center + options.x_zoom * (x - width / 2);
    y_ = eval(e, x_, 0);

    y = height/2 + (options.y_center - y_)/options.y_zoom;

    if (x >= 0 &&
        ((y >= 0 && y < height) || (last_y >= 0 && last_y < height))) {
      wcprintf(y, x, color, BG_BLACK, c);
      if (y > last_y + 1) {
        for (yi = MAX(last_y + 1,0); yi < y && yi<height; yi++) {
          wcprintf(yi, x, color, BG_BLACK, c);
        }
      } else if (y < last_y - 1) {
        for (yi = MAX(y + 1, 0); yi < last_y && yi < height; yi++) {
          wcprintf(yi, x, color, BG_BLACK, c);
        }
      }
      update_ui();
    }

    last_y = y;
  }

  wcprintf(0, 0, FG_WHITE, BG_BLACK, "           ");
  wcprintf(1 + index, 0, FG_WHITE, BG_BLACK, "%d", index);
  wcprintf(1 + index, 2, color, BG_BLACK, "f(x) = %s", e.str);

  update_ui();
}

double test_interval(const expr* e1, const expr* e2, 
    double x1, double x2, double y1, double y2, double* x_min, double* y_min) {

  *x_min = x1;
  *y_min = y1;
  double min_diff = fabs(eval(*e1, x1, y1) - eval(*e2, x1, y1));

  for (int i = 0; i < 50; i++) {
    double x_rand = ((double) rand()) / RAND_MAX;
    double y_rand = ((double) rand()) / RAND_MAX;

    double x = x1 + (x2 - x1) * x_rand;
    double y = y1 + (y2 - y1) * y_rand;
    double diff = fabs(eval(*e1, x, y) - eval(*e2, x, y));
    if (diff < min_diff) {
      min_diff = diff;
      *x_min = x;
      *y_min = y;
    }
  }
  return min_diff;
}

bool cut(const expr* e1, const expr* e2,
    double x1, double x2, double y1, double y2) {
  double zoom = (2.0 * options.x_zoom + options.y_zoom) / 2.0;
  double x, y;
  double min_diff = test_interval(e1, e2, x1, x2, y1, y2, &x, &y);

  if (min_diff < zoom / 4.0) {
    return true;
  } else if (fabs(x1 - x2) < 0.01 ||
             fabs(y1 - y2) < 0.01) {
    return false;
  } else if (min_diff < zoom) {
    double delta_x = MIN(fabs(x - x1), fabs(x - x2));
    double delta_y = MIN(fabs(y - y1), fabs(y - y2));
    return cut(e1, e2, x - delta_x, x + delta_x, y - delta_y, y + delta_y);
  } else {
    return false;
  }
}

void plot_implicit(expr e1, expr e2, int index) {

  static char c[1] = "o";

  int height = options.height;
  int width = options.width;

  int x, y;
  int color = index % 16 + 2;

  wcprintf(0, 0, FG_WHITE, BG_BLACK, "plotting...");
  update_ui();

  for (x = 0; x < width; x++) {
    for (y = 0; y< height; y++) {
      double x_ = options.x_center + options.x_zoom * (x - width / 2);
      double y_ = options.y_center + options.y_zoom * (height / 2 - y);
      double x_2 = options.x_center + options.x_zoom * ((x + 1) - width / 2);
      double y_2 = options.y_center + options.y_zoom * (height / 2 - (y + 1));
      if (cut(&e1, &e2, x_, x_2, y_, y_2)) {
        wcprintf(y, x, color, BG_BLACK, c);
      }
    }
    update_ui();
  }

  wcprintf(0, 0, FG_WHITE, BG_BLACK, "           ");
  wcprintf(1 + index, 0, FG_WHITE, BG_BLACK, "%d", index);
  wcprintf(1 + index, 2, color, BG_BLACK, "%s = %s", e1.str, e2.str);

  update_ui();
}


void draw_axis(void) {
  int h = options.height;
  int w = options.width;

  double xz = options.x_zoom;
  double yz = options.y_zoom;

  int y, x;
  int x_0 = w / 2 - options.x_center / xz;
  int y_0 = h / 2 + options.y_center / yz;

  for (y = 0; y<h; y++) {
    wcprintf(y, x_0, FG_WHITE, BG_BLACK, "|");
  }
  update_ui();

  for (x = 0; x<w; x++) {
    wcprintf(y_0, x, FG_WHITE, BG_BLACK, "-");
  }
  update_ui();
}

void draw_axis_numbers(void) {
  int h = options.height;
  int w = options.width;

  double xz = options.x_zoom;
  double yz = options.y_zoom;

  int y, x;
  int x_0 = w / 2 - options.x_center / xz;
  int y_0 = h / 2 + options.y_center / yz;

  for (x = 0; x < w - 14; x += 15) {
    int y_ = y_0 < 0 ? 1 : y_0 >= h - 2 ? h - 2 : y_0 + 1;

    wcprintf(y_,
             x,
             FG_WHITE, BG_BLACK,
             xz > 10 || xz < 0.001 ? "%.3e" : "%.3f",
             options.x_center + options.x_zoom * (x - w / 2));
  }
  update_ui();

  for(y = 0; y < h; y += 3) {
    int x_ = x_0 < 0 ? 0 : x_0 >= w - 15 ? w - 15 : x_0 + 1;
    wcprintf(y,
             x_,
             FG_WHITE, BG_BLACK,
             yz > 10 || yz < 0.001 ? " %.3e" : " %.3f",
             options.y_center + options.y_zoom * (h / 2 - y));
  }
  update_ui();
}

void show_options(void) {
  int y = options.height;
  wcprintf(y - 7, 0, FG_WHITE, BG_BLACK,
      "options.cpu_time_draw = %f", options.cpu_time_draw);
  wcprintf(y - 6, 0, FG_WHITE, BG_BLACK,
      "options.height = %d", options.height);
  wcprintf(y - 5, 0, FG_WHITE, BG_BLACK,
      "options.width = %d", options.width);
  wcprintf(y - 4, 0, FG_WHITE, BG_BLACK,
      "options.x_center = %f", options.x_center);
  wcprintf(y - 3, 0, FG_WHITE, BG_BLACK,
      "options.y_center = %f", options.y_center);
  wcprintf(y - 2, 0, FG_WHITE, BG_BLACK,
      "options.x_zoom = %f", options.x_zoom);
  wcprintf(y - 1, 0, FG_WHITE, BG_BLACK,
      "options.y_zoom = %f", options.y_zoom);

  update_ui();
}

void delete_function(unsigned int i) {
  d_print("Deleting funcion %d...", i);
  d_print("State of the function array: \n");
  for (int j = 0; j < MAX_FUNCTIONS; j++) {
    char* fexpr = functions[j].f.str;
    d_print("\t(%d) %s  -> %d.\n", j, fexpr ? fexpr : "???", functions[j].valid);
  }
    
  if (i < MAX_FUNCTIONS) {
    if (functions[i].valid) {
      delete_expr(&(functions[i].f));
      functions[i].valid = 0;
    }
  }
}

void init_plotter(void) {
  unsigned int i;
  for (i = 0; i < MAX_FUNCTIONS; i++) {
    functions[i].valid = 0;
  }
}

void clean_plotter(void) {
  unsigned int i;
  for (i = 0; i < MAX_FUNCTIONS; i++) {
    delete_function(i);
  }
}
