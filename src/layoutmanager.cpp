#include <iostream>
#include <stdio.h>

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "keybind.h"
#include "layoutmanager.h"

void LayoutManager::init() {
}

void LayoutManager::reload() {
}

bool LayoutManager::checkWindowMaximized(Display* display, Window window) {

    Atom typeReturn;
    int formatReturn;
    unsigned long items;
    unsigned long bytesAfter;
    unsigned char* data;

    int status = XGetWindowProperty(display,
                                      window,
                                      XInternAtom(display, "_NET_WM_STATE", false),
                                      0,
                                      (~0L),
                                      false,
                                      AnyPropertyType,
                                      &typeReturn,
                                      &formatReturn,
                                      &items,
                                      &bytesAfter,
                                      &data);
        switch (status) {
        case Success:
            //printf("Success");
            break;
        case BadWindow:
            printf("%s\n\t%s\n","LayoutManager::checkWindowMaximized","Error: BadWindow");
            return false;
            break;
        case BadAtom:
        printf("%s\n\t%s\n","LayoutManager::checkWindowMaximized","Error: BadAtom");
            return false;
            break;
        case BadValue:
        printf("%s\n\t%s\n","LayoutManager::checkWindowMaximized","Error: BadValue");
            return false;
            break;
        default:
        printf("%s\n\t%s\n","LayoutManager::checkWindowMaximized","Error: Unknown");
            return false;
            break;
        }

    bool maxHor = false;
    bool maxVert = false;

    Atom atomMaxHorz = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", true);
    Atom atomMaxVert = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", true);

    for (unsigned int i = 0; i < items; ++i) {
        if (reinterpret_cast<unsigned long*>(data)[i] == (unsigned long)atomMaxHorz)
            maxHor = true;
        else if (reinterpret_cast<unsigned long*>(data)[i] == (unsigned long)atomMaxVert)
            maxVert = true;

        if (maxVert && maxHor) {
            XFree(data);
            return true;
        }
    }
    XFree(data);
    return false;
}

void LayoutManager::tileActiveWindow(const KeyBind* keybind) {

    //XLIB
    Display* display = XOpenDisplay(nullptr);
    Window window;
    int revert;
    XGetInputFocus(display, &window, &revert);

    XWindowAttributes wAttrib;
    XGetWindowAttributes(display, window, &wAttrib);

    Atom atomState = XInternAtom(display, "_NET_WM_STATE", true);
    Atom atomMaxHori = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", true);
    Atom atomMaxVert = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", true);

    int scrW = wAttrib.screen->width;
    int scrH = wAttrib.screen->height;

    std::cout << scrW << "x" << scrH << std::endl;
    bool isMaximized = checkWindowMaximized(display, window);
    std::cout << "Max: " << isMaximized << std::endl;

    XMoveWindow(display,
                window,
                (int)scrW * (keybind->getXPos() / 100.0),
                (int)scrH * (keybind->getYPos() / 100.0));

    XResizeWindow(display,
                  window,
                  (unsigned int)scrW * (keybind->getWidth() / 100.0),
                  (unsigned int)scrH * (keybind->getHeight() / 100.0));

    XFlush(display);
    XCloseDisplay(display);
    /*
    Atom nameAtom = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", false);
    Atom intAtom = XInternAtom(display, "INTEGER", false);

    Atom type;
    int format;
    unsigned long nitems, after;
    unsigned char* data;

    if (Success == XGetWindowProperty(display, window, nameAtom, 0, 65536,
                                      false, intAtom, &type, &format,
                                      &nitems, &after, &data)) {
        if (data) {
            std::cout << "W:" << data << std::endl;
            XFree(data);
        }
    }
*/
    /*
    int scr = DefaultScreen(display);
    int scrW = DisplayWidth(display, scr);
    int scrH = DisplayHeight(display, scr);
    
    XMoveResizeWindow(display,
        window,
        (int)dispW * (keybind->getXPos() / 100.0),
        (int)dispH * (keybind->getYPos() / 100.0),
        (unsigned int)dispW * (keybind->getWidth() / 100.0),
        (unsigned int)dispH * (keybind->getHeight() / 100.0));
        */
    /*
    XMoveResizeWindow(display,
                      window,
                      (int)screen->width * (keybind->getXPos() / 100.0),
                      (int)screen->height * (keybind->getYPos() / 100.0),
                      (unsigned int)screen->width * (keybind->getWidth() / 100.0),
                      (unsigned int)screen->height * (keybind->getHeight() / 100.0));
    */
}