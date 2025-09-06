#define LOGGING_IMPL
#include "globals.h"

#define SOKOL_IMPL
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_log.h"

static struct {
  sg_pass_action pass;
} ctx;

void init() {
  log_printf(INFO, "Window width: %d!", window_width);
  log_printf(INFO, "Window height: %d!", window_height);

  sg_setup(&(sg_desc){
      .environment = sglue_environment(),
      .logger.func = slog_func,
  });

  ctx.pass = (sg_pass_action){
      .colors[0] =
          {
              .load_action = SG_LOADACTION_CLEAR,
              .clear_value = {0.694, 0.89, 0.98, 1.0},
          },
  };
}

void clean() {
  sg_shutdown();
  log_printf(INFO, "Exit game");
}

void frame() {
  sg_begin_pass(&(sg_pass){.action = ctx.pass, .swapchain = sglue_swapchain()});
  sg_end_pass();
  sg_commit();
}

static void event(const sapp_event *e) {
  switch (e->type) {
  case SAPP_EVENTTYPE_RESIZED:
    window_width = e->window_width;
    window_height = e->window_height;
    log_printf(INFO, "New window size: %d x %d", window_width, window_height);
    break;
  case SAPP_EVENTTYPE_KEY_DOWN:
    if (e->key_code == SAPP_KEYCODE_ESCAPE) {
      sapp_quit();
    }
    break;
  default:
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
      .width = window_width,
      .height = window_height,
      .high_dpi = true,
      .window_title = "My render",
  };
}
