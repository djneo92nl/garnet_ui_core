#pragma once

#include <cstdint>

// Runtime-configurable screen geometry and palette, since different
// projects using a Garnet UI backend have different resolutions and/or
// want to match their own brand colors instead of the default Palm-ish
// one.
//
// Colors are stored as plain 0xRRGGBB - deliberately NOT any renderer's
// native pixel format (e.g. TFT_eSPI's packed RGB565 uint16_t). This
// struct is shared by every backend, so it can't assume one; each backend
// converts these to its own native color type once, at theme-apply time
// (see e.g. garnet_ui's garnetSetTheme, which converts to RGB565 via
// TFT_eSPI's own color565()).
struct GarnetTheme {
  int screenW = 240;
  int screenH = 320;
  int titleBarH = 22;

  uint32_t bg = 0xFFFFFF;         // page background
  uint32_t titleTag = 0x000080;   // the small colored tag behind title text
  uint32_t titleFg = 0xFFFFFF;    // text color on the tag
  uint32_t text = 0x000000;       // body text
  uint32_t border = 0x000000;     // borders/dividers
  uint32_t selectedBg = 0x000080; // selected list row background
  uint32_t selectedFg = 0xFFFFFF; // selected list row text
};

// Returns a copy of `base` with a ready dark palette applied to just the
// 7 color fields - screenW/screenH/titleBarH are copied through
// unchanged, so this is safe regardless of your project's resolution.
GarnetTheme garnetDarkVariant(const GarnetTheme &base);
