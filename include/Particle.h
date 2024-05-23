//
// Created by HORIA on 18.05.2024.
//

#ifndef IMAGEBANANA_PARTICLE_H
#define IMAGEBANANA_PARTICLE_H

namespace Raylib {

#include <raylib.h>

}

using namespace Raylib;

#include "Constants.h"
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

    Raylib::Color color = {};

    //static variables
    static float ease;
    static int size;
    static float friction;

    static void (*plug)(Particle* p, float friction, float ease, Raylib::Vector2 mousePos);

    void draw();
    void update();

    void warp();
};

#endif //IMAGEBANANA_PARTICLE_H
