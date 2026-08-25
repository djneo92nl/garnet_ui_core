#include "garnet_list_layout.h"

int garnetListRowY(const GarnetListLayout &layout, int index) { return layout.top + index * layout.rowH; }

int garnetListHitTest(const GarnetListLayout &layout, int count, int y) {
  if (y < layout.top || y >= layout.top + count * layout.rowH) {
    return -1;
  }
  return (y - layout.top) / layout.rowH;
}

GarnetPopupTap garnetHandlePopupTap(int x, int y, bool &popupOpen, GarnetRect box) {
  if (!popupOpen) {
    return GarnetPopupTap::None;
  }
  popupOpen = false;
  return box.contains(x, y) ? GarnetPopupTap::Confirmed : GarnetPopupTap::Dismissed;
}
