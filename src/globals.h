#pragma once

#ifndef _GLOBALS_
#define _GLOBALS_
#include <stdint.h>

extern int GAME_WIDTH;
extern int GAME_HEIGHT;

void log_printf(uint32_t level, const char* fmt, ...);

#define PANIC 0
#define ERROR 1
#define WARNING 2
#define INFO 3

#endif
