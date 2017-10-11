#include <iostream>
#include <istream>

#include <gdk/gdk.h>
#include <gtk/gtk.h>
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