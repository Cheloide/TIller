#include "layoutmanager.h"
#include "keybind.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>

void LayoutManager::tileActiveWindow(const KeyBind* keybind) {

    //XLIB
    Display* display = XOpenDisplay(nullptr);
    Window window;
    int revert;
    XGetInputFocus(display, &window, &revert);

    XWindowAttributes wAttrib;
    XGetWindowAttributes(display, window, &wAttrib);
    Screen* screen = wAttrib.screen;
    std::cout<< wAttrib.screen <<std::endl;
    XMoveResizeWindow(display,
                      window,
                      (int)screen->width * (keybind->getXPos() / 100.0),
                      (int)screen->height * (keybind->getYPos() / 100.0),
                      (unsigned int)screen->width * (keybind->getWidth() / 100.0),
                      (unsigned int)screen->height * (keybind->getHeight() / 100.0));
    XFlush(display);
    XCloseDisplay(display);

    /*
X       MoveResizeWindow(display, w, x, y, width, height)
      Display *display;
      Window w;
      int x, y;
      unsigned int width, height;
      */

    //WNCK
    /*
    WnckScreen* screen;
    WnckWindow* activeWindow;

    screen = wnck_screen_get_default();
    wnck_screen_force_update(screen);

    activeWindow = wnck_screen_get_active_window(screen);

    int screenHeight = wnck_screen_get_height(screen);
    int screenWidth = wnck_screen_get_width(screen);
    std::cout << screenWidth << 'x' << screenHeight << std::endl;

    XWMHints* win_hints = XAllocWMHints();

    if (!wnck_window_is_maximized(activeWindow))
        wnck_window_maximize(activeWindow);

    wnck_window_get_geometry(activeWindow, &windowX, &windowY, &maximizedWidth, &maximizedHeight);

    wnck_window_set_geometry(activeWindow,
                             (WnckWindowGravity)WNCK_WINDOW_GRAVITY_STATIC,
                             (WnckWindowMoveResizeMask)(WNCK_WINDOW_CHANGE_X | WNCK_WINDOW_CHANGE_Y | WNCK_WINDOW_CHANGE_HEIGHT | WNCK_WINDOW_CHANGE_WIDTH),
                             (int)screenWidth * (keybind->getXPos() / 100.0),
                             (int)screenHeight * (keybind->getYPos() / 100.0),
                             (int)screenWidth * (keybind->getWidth() / 100.0),
                             (int)screenHeight * (keybind->getHeight() / 100.0));
    */
}