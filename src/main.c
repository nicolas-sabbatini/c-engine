#include "globals.c"

#define SOKOL_IMPL
#define SOKOL_GLCORE
#define SOKOL_EGL
#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_log.h"

void init() {
  log_printf(INFO, "Game width: %d!", GAME_WIDTH);
  log_printf(INFO, "Game height: %d!", GAME_HEIGHT);
}

void clean() { log_printf(INFO, "Exit game"); }

void frame() {}

static void event(const sapp_event *e) {
  if (e->type == SAPP_EVENTTYPE_RESIZED) {
    log_printf(INFO, "Resize windows");
    GAME_WIDTH = sapp_width();
    GAME_HEIGHT = sapp_height();
    log_printf(INFO, "New game width: %d!", GAME_WIDTH);
    log_printf(INFO, "New game height: %d!", GAME_HEIGHT);
  }
}

sapp_desc sokol_main(int argc, char *argv[]) {
  return (sapp_desc){
      // Callbacks
      .init_cb = init,
      .frame_cb = frame,
      .cleanup_cb = clean,
      .event_cb = event,
      .logger.func = slog_func,
      // Options
      .width = 800,
      .height = 600,
      .high_dpi = true,
      .window_title = "My engine",
  };
}
