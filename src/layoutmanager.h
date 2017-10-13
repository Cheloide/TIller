#ifndef LAYOUT_MANAGER_H
#define LAYOUT_MANAGER_H

#include <X11/Xlib.h>

#include "keybind.h"

class LayoutManager {
  private:
    static bool checkWindowMaximized(Display*, Window);
    static void minimizeWindow(Display*,Window);
    static void maximizeWindow(Display*,Window);

  protected:
  public:
    static void init();
    static void reload();
    static void tileActiveWindow(const KeyBind* keybind);
};

#endif