#ifndef KEYBIND_H
#define KEYBIND_H

#include <string>

#include <libwnck/libwnck.h>

enum Anchors {
    CURRENT = WNCK_WINDOW_GRAVITY_CURRENT,
    NW = WNCK_WINDOW_GRAVITY_NORTHWEST,
    N = WNCK_WINDOW_GRAVITY_NORTH,
    NE = WNCK_WINDOW_GRAVITY_NORTHEAST,
    W = WNCK_WINDOW_GRAVITY_WEST,
    C = WNCK_WINDOW_GRAVITY_CENTER,
    E = WNCK_WINDOW_GRAVITY_EAST,
    SW = WNCK_WINDOW_GRAVITY_SOUTHWEST,
    S = WNCK_WINDOW_GRAVITY_SOUTH,
    SE = WNCK_WINDOW_GRAVITY_SOUTHEAST
};

class KeyBind {
  private:
    std::string name;
    std::string mapping;
    Anchors anchor;
    std::string type;
    int xPos;
    int yPos;
    int height;
    int width;

    
  protected:
  public:
    KeyBind();
    KeyBind(std::string name, std::string mapping, Anchors anchor, int xPos, int yPos, int height, int width);
    ~KeyBind();
    
    static void handler(const char *keystring, void *user_data);
    
    void bindKey();

    void setName(std::string);
    void setMapping(std::string);
    void setAnchor(Anchors);
    void setAnchor(std::string);
    void setType(std::string);
    void setXPos(int);
    void setYPos(int);
    void setHeight(int);
    void setWidth(int);

    std::string getName() const;
    std::string getMapping() const;
    Anchors getAnchor() const;
    std::string getType() const;
    int getXPos() const;
    int getYPos() const;
    int getHeight() const;
    int getWidth() const;
};

#endif