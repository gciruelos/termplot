#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

extern int debug_enabled;

void start_debug(void);
void d_print(const char * format, ...);
