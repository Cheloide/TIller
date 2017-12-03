#include <cstring>
#include <iostream>
#include <stdio.h>

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "keybind.h"
#include "layoutmanager.h"
#include "xaction.h"

void LayoutManager::getDecorationDimentions(Display* display, Window window, long* left, long* right, long* top, long* bottom) {

    Atom typeReturn;
    int formatReturn;
    unsigned long items;
    unsigned long bytesAfter;
    unsigned char* data;

    Status status = XGetWindowProperty(display,
                                       window,
                                       XInternAtom(display, "_NET_FRAME_EXTENTS", false),
                                       0,
                                       4,
                                       false,
                                       AnyPropertyType,
                                       &typeReturn,
                                       &formatReturn,
                                       &items,
                                       &bytesAfter,
                                       &data);

    XAction::printXError(display, "LayoutManager::getDecorationDimentions()", status);

    long* dim = (long*)data;
    printf("%lu\n", items);

    if (items == 4) {
        printf("%li %li %li %li\n", dim[0], dim[1], dim[2], dim[3]);
        *left = dim[0];
        *right = dim[1];
        *top = dim[2];
        *bottom = dim[2];
    }
}

void LayoutManager::getMaximizedGeometry(Display* display, Window window, int* x, int* y, int* w, int* h) {

    XSelectInput(display, window, StructureNotifyMask);
    XSelectInput(display, XDefaultRootWindow(display), SubstructureNotifyMask | SubstructureRedirectMask);

    XAction::maximizeWindow(display, window);

    Window root_return;
    int x_return;
    int y_return;
    unsigned int width_return;
    unsigned int height_return;
    unsigned int border_width_return;
    unsigned int depth_return;

    XGetGeometry(display,
                 window,
                 &root_return,
                 &x_return,
                 &y_return,
                 &width_return,
                 &height_return,
                 &border_width_return,
                 &depth_return);

    XAction::unMaximizeWindow(display, window);

    *x = x_return;
    *y = y_return;
    *w = (int)width_return;
    *h = (int)height_return;
}

void LayoutManager::init() {
}

void LayoutManager::reload() {
}

void LayoutManager::minimizeWindow(Display* display, Window window) {
}

void LayoutManager::unMinimizeWindow(Display* display, Window window) {
}

void LayoutManager::maximizeWindow(Display* display, Window window) {
}

void LayoutManager::unMaximizeWindow(Display* display, Window window) {
}

bool LayoutManager::checkWindowMaximized(Display* display, Window window) {

    Atom typeReturn;
    int formatReturn;
    unsigned long items;
    unsigned long bytesAfter;
    unsigned char* data;

    Status status = XGetWindowProperty(display,
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

    if (status != Success) {

        XAction::printXError(display, "LayoutManager::checkWindowMaximized()", status);
        return false;
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
void LayoutManager::tileWindow(Display* display, Window window, int x, int y, unsigned int w, unsigned int h) {

    /*int maxX;
    int maxY;
    int maxW;
    int maxH;
    LayoutManager::getMaximizedGeometry(display, window, &maxX, &maxY, &maxW, &maxH);
    XAction::moveResizeWindow(display,
                              window,
                              ForgetGravity,
                              (int)maxX + (maxW * (x / 100.0)),
                              (int)maxY + (maxH * (y / 100.0)),
                              (int)maxW * (w / 100.0),
                              (int)maxH * (h / 100.0));*/

    XAction::moveResizeWindow(display,
                              window,
                              ForgetGravity,
                              (int)XWidthOfScreen(XScreenOfDisplay(display)) + (x / 100.0),
                              (int)XHeightOfScreen(XScreenOfDisplay(display)) + (y / 100.0),
                              (int)XWidthOfScreen(XScreenOfDisplay(display)) * (w / 100.0),
                              (int)XHeightOfScreen(XScreenOfDisplay(display)) * (h / 100.0);
}

void LayoutManager::executeAction(const KeyBind* keybind) {
    /*TODO
     *  Actions:
     *      Tile
     *      Iconify
     *      Maximize
     *      MInimize
     *      AutoLayout:
     *          Cascade
     *          Mosaic
     *          Columns
     *          Rows
    */

    //XLIB
    Display* display;

    Window window;
    int revert;

    display = XOpenDisplay(nullptr);
    XGetInputFocus(display, &window, &revert);

    LayoutManager::tileWindow(display, window, keybind->getXPos(), keybind->getYPos(), keybind->getWidth(), keybind->getHeight());

    XFlush(display);
    XCloseDisplay(display);
}