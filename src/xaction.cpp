#include <cstring>
#include <iostream>
#include <stdio.h>

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "xaction.h"

void XAction::printXError(Display* display, const char* name, Status statusCode) {
    char* errorText = (char*)malloc(sizeof(char) * 512);
    XGetErrorText(display, statusCode, errorText, 512);
    printf("ERROR::%s %s\n", name, errorText);
    free(errorText);
}

bool XAction::waitForEvent(Display* display, Window window, const long mask, const long type) {
    while (true) {
        XEvent e;
        XCheckWindowEvent(display, window, mask, &e);
        if (e.type > 0)
            printf("%d\n", e.type);
        if (e.type == type)
            return true;
    }
}

bool XAction::moveResizeWindow(Display* display, Window window, const int gravity, const int x, const int y, const int width, const int height) {
    XSelectInput(display, window, StructureNotifyMask);

    Atom messageType = XInternAtom(display, "_NET_MOVERESIZE_WINDOW", false);

    XClientMessageEvent event = {};
    event.type = ClientMessage;
    event.window = window;
    event.message_type = messageType;
    event.format = 32;
    event.data.l[0] = gravity | (0b11111 << 8);
    event.data.l[1] = x;
    event.data.l[2] = y;
    event.data.l[3] = width;
    event.data.l[4] = height;

    Status status = XSendEvent(display,
                               window,
                               false,
                               StructureNotifyMask,
                               (XEvent*)&event);

    if (status != 1) {
        printXError(display, "XAction::moveResizeWindow()", status);
        return false;
    }
    printf("XAction::moveResizeWindow()\n");
    return XAction::waitForEvent(display, window, StructureNotifyMask, ConfigureNotify);
}

bool XAction::maximizeWindow(Display* display, Window window) {
    XSelectInput(display, window, StructureNotifyMask);

    Atom messageType = XInternAtom(display, "_NET_WM_STATE", false);
    Atom maxHorz = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", false);
    Atom maxVert = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", false);

    XClientMessageEvent event = {};
    event.type = ClientMessage;
    event.window = window;
    event.message_type = messageType;
    event.format = 32;
    event.data.l[0] = 1;
    event.data.l[1] = maxHorz;
    event.data.l[2] = maxVert;
    event.data.l[3] = 1;

    Status status = XSendEvent(display,
                               window,
                               false,
                               StructureNotifyMask,
                               (XEvent*)&event);

    if (status != 1) {
        printXError(display, "XAction::maximizeWindow()", status);
        return false;
    }
    printf("XAction::maximizeWindow()\n");
    return XAction::waitForEvent(display, window, StructureNotifyMask, ConfigureNotify);
}
bool XAction::unMaximizeWindow(Display* display, Window window) {
    XSelectInput(display, window, StructureNotifyMask);

    Atom messageType = XInternAtom(display, "_NET_WM_STATE", false);
    Atom maxHorz = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", false);
    Atom maxVert = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", false);

    XClientMessageEvent event = {};
    event.type = ClientMessage;
    event.window = window;
    event.message_type = messageType;
    event.format = 32;
    event.data.l[0] = 0;
    event.data.l[1] = maxHorz;
    event.data.l[2] = maxVert;
    event.data.l[3] = 1;

    Status status = XSendEvent(display,
                               window,
                               false,
                               StructureNotifyMask,
                               (XEvent*)&event);

    if (status != 1) {
        printXError(display, "XAction::maximizeWindow()", status);
        return false;
    }

    printf("XAction::unMaximizeWindow()\n");
    return XAction::waitForEvent(display, window, StructureNotifyMask, ConfigureNotify);
}
bool XAction::minimizeWindow(Display* display, Window window) {
    return false;
}
bool XAction::unMinimizeWindow(Display* display, Window window) {
    return false;
}
bool XAction::iconifyWindow(Display* display, Window window) {
    return false;
}
bool XAction::deIconifyWindow(Display* display, Window window) {
    return false;
}
bool XAction::hideWindowOnTaskBar(Display* display, Window window) {

    XSelectInput(display, window, PropertyChangeMask);

    Atom messageType = XInternAtom(display, "_NET_WM_STATE", false);
    Atom skipTaskbar = XInternAtom(display, "_NET_WM_STATE_SKIP_TASKBAR", false);

    XClientMessageEvent event = {};
    event.type = ClientMessage;
    event.window = window;
    event.message_type = messageType;
    event.format = 32;
    event.data.l[0] = 1;
    event.data.l[1] = skipTaskbar;
    event.data.l[2] = 0;
    event.data.l[3] = 1;

    Status status = XSendEvent(display,
                               window,
                               false,
                               PropertyChangeMask,
                               (XEvent*)&event);

    if (status != 1) {
        printXError(display, "XAction::hideWindowOnTaskBar()", status);
        return false;
    }

    printf("XAction::hideWindowOnTaskBar()\n");
    return XAction::waitForEvent(display, window, PropertyChangeMask, PropertyNotify);
}
bool XAction::showWindowOnTaskBar(Display* display, Window window) {
    return false;
}
bool XAction::turnWindowFullscreen(Display* display, Window window) {
    return false;
}
bool XAction::unTurnWindowFullscreen(Display* display, Window window) {
    return false;
}