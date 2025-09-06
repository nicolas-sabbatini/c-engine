#ifndef LOGGING_H_INCLUDE
#define LOGGING_H_INCLUDE

#include "sokol_log.h"
#include <stdarg.h>
#include <stdint.h>

// Logging levels
#define PANIC   0
#define ERROR   1
#define WARNING 2
#define INFO    3

extern int window_width;
extern int window_height;
#define game_width 800
#define game_height 600

void log_printf(uint32_t level, const char *fmt, ...);

#endif // LOGGING_H_INCLUDE

// IMPLEMENTATION SECTION
#ifdef LOGGING_IMPL

#include <stdio.h>

int window_width = 800;
int window_height = 600;

void log_printf(uint32_t level, const char *fmt, ...) {
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    slog_func("app", level, 0, buf, 0, NULL, NULL);
}

#endif // LOGGING_IMPL

