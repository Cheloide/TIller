#ifndef LAYOUT_MANAGER_H
#define LAYOUT_MANAGER_H

#include <X11/Xlib.h>

#include "keybind.h"

class LayoutManager {
  private:
    static void getMaximizedGeometry(Display*, Window, int*, int*, int*, int*);
    static bool checkWindowMaximized(Display*, Window);
    static void minimizeWindow(Display*, Window);
    static void unMinimizeWindow(Display*, Window);
    static void maximizeWindow(Display*, Window);
    static void unMaximizeWindow(Display*, Window);
    static void tileWindow(Display*, Window, int, int, unsigned int, unsigned int);
    static void getDecorationDimentions(Display*, Window, long*, long*, long*, long*);

  protected:
  public:
    static void init();
    static void reload();
    static void executeAction(const KeyBind* keybind);
};

#endif