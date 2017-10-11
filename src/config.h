#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <string>

#include "keybind.h"

class Config {
  private:
    std::string configPath;
    std::vector<KeyBind*> keybinds;

  protected:
  public:
    Config(const std::string& path = std::string());
    bool loadConfig();
};

#endif