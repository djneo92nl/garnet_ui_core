#pragma once

#include "garnet_types.h"

// What a "screen" in a Garnet UI launcher implements - open it, poll
// whether it's still active, run its per-tick input/redraw logic, or
// force it closed. A screen reports isActive()==false once it has closed
// itself (e.g. via its own title-bar dropdown's "Close" item); it never
// has to call anything to signal that beyond just going inactive.
//
// This shape is a convention, not a base class (see garnet_ui's CLAUDE.md
// for why) - every screen is a .cpp file with its own namespace-local
// state exposing these five free functions. It's shared here, rather than
// duplicated per backend, because it carries no rendering assumptions: a
// TFT_eSPI backend's `loop` does its own per-tick hit-testing, while an
// LVGL backend's `loop` may do little beyond periodic content refresh
// (LVGL's own input device and event callbacks handle the touch
// dispatch) - either is a valid `loop`.
struct GarnetApp {
  void (*open)() = nullptr;
  bool (*isActive)() = nullptr;
  void (*loop)(GarnetTouchPoint touch, bool tapped) = nullptr;
  void (*close)() = nullptr;
  // Repaints this screen in place, without resetting its own state (open()
  // would). Optional - null if this screen never needs to be repainted by
  // something else (e.g. a global overlay closing, or a live theme
  // change) while it's active.
  void (*redraw)() = nullptr;
};
