#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int debug_enabled;

void start_debug();
void d_print(const char * format, ...);
