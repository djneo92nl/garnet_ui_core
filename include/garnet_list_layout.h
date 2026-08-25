#pragma once

#include "garnet_types.h"

// Pure geometry/hit-test math behind every scrollable row list (the WiFi
// network list, the SD file browser, Settings' rows) and every centered
// popup dialog, shared across backends because none of it draws anything
// - each backend still draws its own row content and popup chrome, just
// against this same layout math, so a TFT_eSPI screen and an LVGL screen
// built from the same row/popup data lay out identically.

// Row `index` starts at `top + index * rowH`, full width.
struct GarnetListLayout {
  int top;
  int rowH;
};

int garnetListRowY(const GarnetListLayout &layout, int index);

// Row index for a touch at (x, y) among `count` rows, or -1 if `y` is
// above the list or at/past the last row.
int garnetListHitTest(const GarnetListLayout &layout, int count, int y);

// The popup counterpart: call on every tap while `popupOpen` (the
// caller's own bool state) is true, instead of the caller's own touch
// handling that tick. Always clears `popupOpen`. A tap inside `box` is
// Confirmed; anywhere else is Dismissed. Draws nothing - the caller
// redraws its own screen afterward either way, to erase the popup.
enum class GarnetPopupTap { None, Confirmed, Dismissed };
GarnetPopupTap garnetHandlePopupTap(int x, int y, bool &popupOpen, GarnetRect box);
