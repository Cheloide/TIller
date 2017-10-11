

#include "layoutmanager.h"
#include "keybind.h"

void LayoutManager::tileActiveWindow(const KeyBind * keybind) {

    WnckScreen* screen;
    WnckWindow* active_window;

    screen = wnck_screen_get_default();
    wnck_screen_force_update(screen);

    active_window = wnck_screen_get_active_window(screen);

    int screenHeight = wnck_screen_get_height(screen);
    int screenWidth = wnck_screen_get_width(screen);

    if (wnck_window_is_maximized(active_window))
        wnck_window_unmaximize(active_window);

    wnck_window_set_geometry(active_window,
                             (WnckWindowGravity)keybind->getAnchor(),
                             (WnckWindowMoveResizeMask)(WNCK_WINDOW_CHANGE_X | WNCK_WINDOW_CHANGE_Y | WNCK_WINDOW_CHANGE_HEIGHT | WNCK_WINDOW_CHANGE_WIDTH),
                             (int)screenWidth / 100 * keybind->getXPos(),
                             (int)screenHeight / 100 * keybind->getYPos(),
                             (int)screenWidth / 100 * keybind->getWidth(),
                             (int)screenHeight / 100 * keybind->getHeight());
}