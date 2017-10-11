

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "config.h"
#include "keybind.h"

Config::Config(const std::string& path) {
    if (path.empty())
#ifdef DEBUG
        configPath = "./testconfig.yaml";
#else
        configPath = std::getenv("HOME") + "/.tilercfg.yaml";
#endif
    else
        configPath = path;
}

bool Config::loadConfig() {

    YAML::Node root = YAML::LoadFile(configPath);
    if (root["keybinds"].IsSequence()) {
        std::cout << "Config Loaded!" << std::endl;
        YAML::Node kbinds = root["keybinds"];
        for (std::size_t i = 0, n = kbinds.size(); i < n; ++i) {
            KeyBind* keybind = new KeyBind();
            keybind->setName(kbinds[i]["name"].as<std::string>());
            keybind->setMapping(kbinds[i]["mapping"].as<std::string>());
            //keybind->setAnchor(kbinds[i]["anchor"].as<std::string>());
            keybind->setType(kbinds[i]["type"].as<std::string>());
            keybind->setXPos(kbinds[i]["xpos"].as<int>());
            keybind->setYPos(kbinds[i]["ypos"].as<int>());
            keybind->setHeight(kbinds[i]["height"].as<int>());
            keybind->setWidth(kbinds[i]["width"].as<int>());

            keybind->bindKey();
            keybinds.push_back(keybind);
        }

        return true;
    } else {
        std::cout << "Not Ok!"
                  << " " << YAML::NodeType::Sequence << std::endl;
        return false;
    }
}