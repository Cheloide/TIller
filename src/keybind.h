#ifndef KEYBIND_H
#define KEYBIND_H

#include <string>

class KeyBind {
  private:
    std::string name;
    std::string mapping;
    std::string type;
    int xPos;
    int yPos;
    int height;
    int width;

    
  protected:
  public:
    KeyBind();
    ~KeyBind();
    
    static void handler(const char *keystring, void *user_data);
    
    void bindKey();

    void setName(const std::string&);
    void setMapping(const std::string&);
    void setType(const std::string&);
    void setXPos(const int);
    void setYPos(const int);
    void setHeight(const int);
    void setWidth(const int);

    std::string getName() const;
    std::string getMapping() const;
    std::string getType() const;
    int getXPos() const;
    int getYPos() const;
    int getHeight() const;
    int getWidth() const;
};

#endif