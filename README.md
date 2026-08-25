# garnet_ui_core

The renderer-agnostic core of the [Garnet UI](https://github.com/djneo92nl/garnet_ui)
toolkit: touch/geometry primitives, the runtime theme, the `GarnetApp`
screen convention, row-list/popup layout math, and shared
backend-injection contracts for the ready-made screens.

This is a PlatformIO library dependency, not something you use directly.
Add whichever rendering backend you want to your project instead:

- [garnet_ui](https://github.com/djneo92nl/garnet_ui) - TFT_eSPI-drawn
  widgets.
- [garnet_ui_lvgl](https://github.com/djneo92nl/garnet_ui_lvgl) -
  LVGL-drawn widgets.

Both depend on this repo and share its types, so a `GarnetTheme` or a
`WifiSelectorBackend` wired up for one reads the same way in the other.

See [CLAUDE.md](CLAUDE.md) for what belongs in this repo (and why) if
you're contributing.
