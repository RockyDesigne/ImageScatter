//
// Created by HORIA on 25.05.2024.
//

#ifndef IMAGEBANANA_PLUGINSTATE_H
#define IMAGEBANANA_PLUGINSTATE_H

namespace Raylib {
#include <raylib.h>
}

class PluginState {
public:
    float friction;
    float ease ;
    Raylib::Vector2 mousePos;
    bool isMousePressed;
private:
};

#endif //IMAGEBANANA_PLUGINSTATE_H
