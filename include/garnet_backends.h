#pragma once

#include <Arduino.h>
#include <IPAddress.h>
#include <cstdint>

// Project-specific glue for each ready-made Garnet UI screen, injected as
// a nullable-field callback struct rather than an #include of a project's
// own header (see garnet_ui's CLAUDE.md - "no project-specific #include").
//
// These structs carry no rendering assumptions - they're populated
// directly from a project's own WiFi/storage/brightness functions either
// way - so the same backend wiring works whether the screen it's passed
// to is a garnet_ui (TFT_eSPI) screen or a garnet_ui_lvgl (LVGL) one. A
// project targeting both backends (or migrating from one to the other)
// reuses this wiring unchanged.

// Backs a WiFi selector/status screen: scan/connect flow plus current
// connection status. <WiFi.h> itself (scan/RSSI/gateway) is a standard
// ESP32 Arduino API a screen can call directly - what's project-specific
// is whether there's an STA-enable toggle at all, and how a chosen
// network gets persisted/applied.
struct WifiSelectorBackend {
  bool (*staFeatureEnabled)() = nullptr; // null = feature always on, skip the gating screen
  bool (*isConnected)() = nullptr;       // required
  String (*currentSsid)() = nullptr;     // required
  IPAddress (*localIP)() = nullptr;      // required (only read while connected)
  void (*connectAndSave)(const String &ssid, const String &password) = nullptr; // required
  void (*setReconnectPaused)(bool paused) = nullptr; // null = no-op
};

// Backs an SD card browser screen. <SD.h> itself is a standard
// framework-bundled API a screen can call directly - what's
// project-specific is whether/how the card is mounted, and whether SD
// access needs to be serialized against something else (e.g. a web
// server sharing the same SPI bus).
struct SdBrowserBackend {
  bool (*isMounted)() = nullptr; // null = always try to browse
  void (*lockBus)() = nullptr;   // null = no locking
  void (*unlockBus)() = nullptr; // null = no locking
};

// Backs the global quick-settings overlay (brightness + light/dark mode).
// How brightness/dark-mode are read and applied is always project
// specific, so every field is required.
struct QuickPanelBackend {
  uint8_t (*getBrightness)() = nullptr;     // required
  void (*setBrightness)(uint8_t) = nullptr; // required
  bool (*isDarkMode)() = nullptr;           // required
  void (*setDarkMode)(bool) = nullptr;      // required
};
