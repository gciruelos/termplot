#include <stdio.h>
#include <string.h>
#include <time.h>

#include "debug.h"
#include "options.h"
#include "plot.h"
#include "ui.h"


// This is ugly.
int parse_args(int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--debug") == 0) {
      debug_enabled = 1;
    }
    if (strcmp(argv[i], "--help") == 0) {
      printf("Usage: %s [options]\n", argv[0]);
      printf("Options:\n");
      printf("\t--debug     Write debug information to a file.\n");
      printf("\t--help      Show this help message.\n");
      printf("\n");
      printf("Commands:\n");
      printf("\t:plot <formula>   Plot a formula, it can be explicit (like "
             "\"x^3 + 1\") or\n"
             "\t                  implicit (like \"y^3 + x^2 = y\").\n");
      printf("\t:remove <n>       Remove the n-th plot.\n");
      printf("\t:quit             Quit the program.\n");
      printf("\n");
      printf("Hotkeys:\n");
      printf("\t+                 Zoom in.\n");
      printf("\t-                 Zoom out.\n");
      printf("\tArrow keys        Move across the plane.\n");
      printf("\tq                 Quit.\n");
      exit(0);
    }
  }
  return 0;
}


int main(int argc, char* argv[]) {
  parse_args(argc, argv);

  init_ui();
  init_structs();
  init_plotter();

  start_debug();

  int x;
  clock_t start, end;
  while (!options.quit) {
    term_clear();
    set_terminal_size(&options);
    start = clock();
    draw_axis();
    replot_functions();
    draw_axis_numbers();
    end = clock();
    options.cpu_time_draw = ((double) (end - start)) / CLOCKS_PER_SEC;
    if (options.show_info) {
      show_options();
    }

    x = input();
    if (x == -1) {
      break;
    }
    term_refresh();
  }

  clean_plotter();
  clean_ui();
  return 0;
}
