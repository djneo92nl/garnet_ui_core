#include "garnet_time.h"

#include <Arduino.h>

bool garnetEvery(uint32_t &lastMs, uint32_t intervalMs) {
  uint32_t now = millis();
  if (now - lastMs < intervalMs) {
    return false;
  }
  lastMs = now;
  return true;
}
