#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int debug_enabled;

void start_debug();
void d_print(const char * format, ...);
