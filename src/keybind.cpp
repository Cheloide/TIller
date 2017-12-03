
#include <iostream>
#include <string>

#include <keybinder.h>

#include "keybind.h"
#include "layoutmanager.h"

KeyBind::KeyBind() = default;

void KeyBind::handler(const char* keystring, void* data) {
    KeyBind* kbind = static_cast<KeyBind*>(data);
    LayoutManager::executeAction(kbind);
#if DEBUG
    std::cout << "Action: " << kbind->getName() << std::endl;
#endif
}

void KeyBind::bindKey() {
    keybinder_bind(mapping.c_str(), handler, this);

#if DEBUG
    std::cout << "Bind: " << this->mapping.c_str() << std::endl;
#endif
}

void KeyBind::setName(const std::string& name) {
    this->name = name;
}
void KeyBind::setMapping(const std::string& mapping) {
    this->mapping = mapping;
}

void KeyBind::setType(const std::string& type) {
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