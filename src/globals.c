#include "globals.h"
#include "sokol/sokol_log.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

void log_printf(uint32_t level, const char *fmt, ...) {
  char buf[1024];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, sizeof(buf), fmt, args);
  va_end(args);
  slog_func("app", level, 0, buf, 0, NULL, NULL);
}

int GAME_WIDTH = 800;
int GAME_HEIGHT = 600;
