
#include <functional>
#include <string>
#include <iostream>

#include <keybinder.h>
#include <libwnck/libwnck.h>

#include "keybind.h"
#include "layoutmanager.h"

KeyBind::KeyBind() = default;
KeyBind::KeyBind(std::string name, std::string mapping, Anchors anchor, int xPos, int yPos, int height, int width) {
    this->name = name;
    this->mapping = mapping;
    this->anchor = anchor;
    this->xPos = xPos;
    this->yPos = yPos;
    this->height = height;
    this->width = width;
}

void KeyBind::handler(const char* keystring, void* user_data) {
    KeyBind *kbind = static_cast<KeyBind *>(user_data);
    LayoutManager::tileActiveWindow(kbind);
    std::cout<<"test firing"<<std::endl;
}

void KeyBind::bindKey() {
    std::cout<<"test Bind: "<<this->mapping.c_str()<<std::endl;

    keybinder_bind(mapping.c_str(), handler, this);
}

void KeyBind::setName(std::string name) {
    this->name = name;
}
void KeyBind::setMapping(std::string mapping) {
    this->mapping = mapping;
}
void KeyBind::setAnchor(Anchors anchor) {
    this->anchor = anchor;
}

void KeyBind::setAnchor(std::string anchor) {
    if (anchor.compare("CURRENT") == 0)
        this->anchor = CURRENT;
    else if (anchor.compare("N") == 0)
        this->anchor = N;
    else if (anchor.compare("NE") == 0)
        this->anchor = NE;
    else if (anchor.compare("NW") == 0)
        this->anchor = NW;
    else if (anchor.compare("S") == 0)
        this->anchor = S;
    else if (anchor.compare("SE") == 0)
        this->anchor = SE;
    else if (anchor.compare("SW") == 0)
        this->anchor = SW;
    else if (anchor.compare("E") == 0)
        this->anchor = E;
    else if (anchor.compare("W") == 0)
        this->anchor = W;
    else if (anchor.compare("C") == 0)
        this->anchor = C;
    else
        this->anchor = NW;
}

void KeyBind::setType(std::string type) {
    this->type = type;
}
void KeyBind::setXPos(int xPos) {
    this->xPos = xPos;
}
void KeyBind::setYPos(int yPos) {
    this->yPos = yPos;
}
void KeyBind::setHeight(int height) {
    this->height = height;
}
void KeyBind::setWidth(int width) {
    this->width = width;
}

std::string KeyBind::getName() const {
    return name;
}

std::string KeyBind::getMapping() const {
    return mapping;
}

Anchors KeyBind::getAnchor() const {
    return anchor;
}

std::string KeyBind::getType() const {
    return type;
}

int KeyBind::getXPos() const {
    return xPos;
}

int KeyBind::getYPos() const {
    return yPos;
}

int KeyBind::getHeight() const {
    return height;
}

int KeyBind::getWidth() const {
    return width;
}