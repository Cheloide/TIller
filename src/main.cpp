#include <iostream>
#include <istream>

#include <gdk/gdk.h>
#include <keybinder.h>

#include "config.h"

int main(int argc, char** argv) {

    gdk_init(&argc, &argv);
    keybinder_init();

    Config cfg;
    if (cfg.loadConfig())
        std::cout << "Config loaded." << std::endl;

    gtk_main();
    
#if DEBUG
    std::getchar();
#endif
    return 0;
}

/*
void test(const char *keystring, void *user_data){

    WnckScreen* screen;
    WnckWindow* active_window;

    screen = wnck_screen_get_default();
    wnck_screen_force_update(screen);

    active_window = wnck_screen_get_active_window(screen);

    g_print("%s\n", wnck_window_get_name(active_window));
    
    int x;
    int y;
    int width;
    int height;

    wnck_window_get_geometry(active_window, &x, &y, &width, &height);

    if (wnck_window_is_maximized(active_window))
        wnck_window_unmaximize(active_window);

    wnck_window_set_geometry(active_window,
                             WNCK_WINDOW_GRAVITY_NORTHWEST,
                             (WnckWindowMoveResizeMask)(WNCK_WINDOW_CHANGE_HEIGHT | WNCK_WINDOW_CHANGE_WIDTH),
                             x,
                             y,
                             width,
                             //(int)(width / 2),
                             (int)(height / 2));
}

int main(int argc, char** argv) {
    gdk_init(&argc, &argv);

    char* EXAMPLE_KEY = "<Super>Left";

    keybinder_init();
    keybinder_bind(EXAMPLE_KEY, test, NULL);
    gtk_main();

    return 0;
}
*/