//
// Created by HORIA on 18.05.2024.
//

#ifndef IMAGEBANANA_PARTICLE_H
#define IMAGEBANANA_PARTICLE_H


#include "Constants.h"
#include "PluginState.h"

namespace Raylib {

#include <raylib.h>

}

using namespace Raylib;
#include <cctype>

class Particle {
public:

    float oX = 0.0f;
    float oY = 0.0f;

    float x = 0.0f;
    float y = 0.0f;

    float vx = 0.0f;
    float vy = 0.0f;

    bool touched = false;
    static bool isMousePressed;

    Raylib::Color color = {};

    //static variables
    static float ease;
    static int size;
    static float friction;

    void draw() ;
    void update() ;

    //plugs
    void chillPlug();

    void whooshyPlug();

    void testPlug();

    void boomPlug();

};

#endif //IMAGEBANANA_PARTICLE_H
