#ifndef XACTION_H
#define XACTION_H

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class XAction {

  private:
    static bool waitForEvent(Display*, Window, const long, const long);

  protected:
  public:
    static bool moveResizeWindow(Display*, Window, const int, const int, const int, const int, const int);
    static bool maximizeWindow(Display*, Window);
    static bool unMaximizeWindow(Display*, Window);
    static bool minimizeWindow(Display*, Window);
    static bool unMinimizeWindow(Display*, Window);
    static bool iconifyWindow(Display*, Window);
    static bool deIconifyWindow(Display*, Window);
    static bool hideWindowOnTaskBar(Display*, Window);
    static bool showWindowOnTaskBar(Display*, Window);
    static bool turnWindowFullscreen(Display*, Window);
    static bool unTurnWindowFullscreen(Display*, Window);
    static void printXError(Display*, const char*, Status);
};

#endif