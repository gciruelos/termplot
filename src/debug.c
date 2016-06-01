#include "debug.h"

FILE * dbg;

void start_debug(void) {
  if (debug_enabled) {
    dbg = fopen("debug.out", "w");
    if (dbg == NULL) {
      fprintf(stderr, "Can't open debug file!\n");
      exit(1);
    }
    fprintf(dbg, "Debug file\n\n");
    fclose(dbg);
  }
}

void d_print(const char * format, ...) {
  if (debug_enabled) {
    dbg = fopen("debug.out", "a");
    va_list args;
    va_start(args, format);
    vfprintf(dbg, format, args);
    va_end(args);
    fclose(dbg);
  }
}

