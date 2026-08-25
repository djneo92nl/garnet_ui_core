#include "garnet_theme.h"

GarnetTheme garnetDarkVariant(const GarnetTheme &base) {
  GarnetTheme dark = base;
  dark.bg = 0x000000;
  dark.titleTag = 0x87CEEB; // sky blue
  dark.titleFg = 0x000000;
  dark.text = 0xFFFFFF;
  dark.border = 0x808080;
  dark.selectedBg = 0x87CEEB;
  dark.selectedFg = 0x000000;
  return dark;
}
