#pragma once

// Renderer-agnostic geometry/input primitives shared by every Garnet UI
// backend (garnet_ui's TFT_eSPI widgets, garnet_ui_lvgl's LVGL widgets,
// and whatever else gets built on top of this). Nothing in this header
// may depend on a specific display/graphics library.

struct GarnetRect {
  int x, y, w, h;
  bool contains(int px, int py) const { return px >= x && px < x + w && py >= y && py < y + h; }
};

// A plain touch-point triple - deliberately not any project's own touch
// driver type (which usually carries raw/uncalibrated fields alongside
// x/y, and is inherently per-board) and not any renderer's own input
// event type either. Every backend and screen built on Garnet UI takes
// this instead. Construct one from whatever your own touch read (or, for
// an LVGL backend, indev callback) produces.
struct GarnetTouchPoint {
  int x = 0;
  int y = 0;
  bool valid = false;
};
