#include <iostream>
#include <stdio.h>

#include <X11/Xlib.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <keybinder.h>

#include "config.h"


int main(int argc, char** argv) {

    gdk_init(&argc, &argv);
    keybinder_init();

    Config cfg;
    if (cfg.loadConfig())
        printf("Config Loaded\n");
    else
        printf("Config could not be loaded!\n");

    gtk_main();
    exit(0);
}