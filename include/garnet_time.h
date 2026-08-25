#pragma once

#include <cstdint>

// Millis()-based rate limiter, identical to garnet_ui's own garnetEvery
// (previously only declared in garnet_ui.h) - pure time math, no rendering
// assumptions, so it belongs here rather than duplicated per backend. Added
// for garnet_ui_lvgl's ui_wifi_selector (its periodic status-value refresh
// needs the exact same gating garnet_ui's TFT version does), but any screen
// on either backend wanting a "at most once every N ms" tick can use it.

// True (and advances lastMs) once `intervalMs` has elapsed since the last
// true; false (and lastMs untouched) otherwise. Caller owns lastMs's
// storage and initial value (typically set from millis() at open()-time).
bool garnetEvery(uint32_t &lastMs, uint32_t intervalMs);
