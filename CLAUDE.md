# garnet_ui_core

The renderer-agnostic core of the Garnet UI toolkit. Everything in this
repo is shared, unmodified, between [garnet_ui](https://github.com/djneo92nl/garnet_ui)
(TFT_eSPI-drawn widgets) and [garnet_ui_lvgl](https://github.com/djneo92nl/garnet_ui_lvgl)
(LVGL-drawn widgets) - the same Palm OS 5-styled framework, two different
rendering backends. This repo is not useful on its own; it's a dependency
of one of those two.

## What belongs here vs. what doesn't

Only code with **zero rendering assumptions** belongs in this repo -
nothing that calls a drawing API, and nothing whose type depends on one
(e.g. a renderer's native pixel format). Concretely:

- `garnet_types.h` - `GarnetRect`, `GarnetTouchPoint`. Pure data.
- `garnet_theme.h`/`.cpp` - `GarnetTheme` (screen geometry + a 0xRRGGBB
  palette) and `garnetDarkVariant()`. Colors are plain hex, not any
  renderer's native pixel format - each backend converts once, at
  theme-apply time (garnet_ui's `garnetSetTheme` converts to RGB565 via
  TFT_eSPI's own `color565()`; garnet_ui_lvgl's converts via LVGL's own
  `lv_color_hex()`).
- `garnet_app.h` - the `GarnetApp` struct (open/isActive/loop/close/
  redraw function pointers). This is the *convention* a screen follows,
  not a base class - see either backend repo's own CLAUDE.md for why. It
  belongs here because the convention itself doesn't draw anything; each
  backend's screens still implement it very differently (a TFT_eSPI
  screen's `loop` does manual per-tick hit-testing; an LVGL screen's
  `loop` may do little beyond periodic content refresh, since LVGL's own
  input device and event callbacks handle touch dispatch).
- `garnet_list_layout.h`/`.cpp` - the row-list and popup-box layout math
  (`GarnetListLayout`, `garnetListRowY`, `garnetListHitTest`,
  `garnetHandlePopupTap`). Pure geometry/hit-testing, no drawing - each
  backend still draws its own row content and popup chrome against this
  same layout.
- `garnet_time.h`/`.cpp` - `garnetEvery`, a millis()-based "at most once
  every N ms" rate limiter. Pure time math, no rendering assumptions -
  used by both backends' screens for periodic content refresh (e.g. a
  WiFi screen's slow-timer signal-strength readout).
- `garnet_backends.h` - the backend-injection contracts for each
  ready-made screen (`WifiSelectorBackend`, `SdBrowserBackend`,
  `QuickPanelBackend`). These are plain function-pointer structs a
  project populates from its own WiFi/storage/brightness code; since they
  don't reference either backend's drawing API, the exact same wiring
  works for a TFT_eSPI build or an LVGL build of the same project.

What does **not** belong here: `GarnetAppRunner` (it dispatches to a
Home icon grid, and drawing that grid - including each backend's own
icon-callback signature - is inherently backend-specific; both `garnet_ui`
and `garnet_ui_lvgl` implement their own small `GarnetAppRunner`), any
widget-drawing function, any screen implementation, and anything that
`#include`s a display/graphics library.

## Design rules

Same spirit as the two repos that depend on this one:

- **No project-specific `#include`.** Same rule as garnet_ui - nothing
  here may depend on a specific consuming project's own headers.
  Framework-bundled APIs (`<Arduino.h>`, `<IPAddress.h>`) are fine, same
  reasoning as garnet_ui's CLAUDE.md: every ESP32 Arduino project has
  them.
- **No rendering `#include`, ever - not even conditionally.** Not
  `<TFT_eSPI.h>`, not `<lvgl.h>`, not anything else. The day this repo
  needs one is the day something in it stopped being core.
- **No hardcoded screen size.** Same as garnet_ui - `GarnetTheme` carries
  geometry precisely so nothing here (or downstream) bakes in a literal
  resolution.
- Adding something here should make BOTH downstream repos simpler, not
  just one. If only `garnet_ui` or only `garnet_ui_lvgl` would use it, it
  belongs in that repo instead.

## Verifying a change

This repo has no display and doesn't build standalone. Verify a change by
building `garnet_ui` and/or `garnet_ui_lvgl` (whichever it affects) with
this checked out as their `garnet_ui_core` dependency, and building
whatever project embeds them - see each repo's own CLAUDE.md.
