//
// Created by HORIA on 18.05.2024.
//

#ifndef IMAGEBANANA_PARTICLE_H
#define IMAGEBANANA_PARTICLE_H

namespace Raylib {

#include <raylib.h>

}

struct Particle {
    float oX;
    float oY;
    float x;
    float y;
    float vx;
    float vy;
    static float ease;
    static int size;
    static float friction;
    static void (*plug)(Particle* p, float friction, float ease, Raylib::Vector2 mousePos);
    bool touched = false;
    Raylib::Color color;


    void draw();
    void update();

    void warp();

};

#endif //IMAGEBANANA_PARTICLE_H
