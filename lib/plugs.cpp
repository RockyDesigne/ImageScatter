//
// Created by HORIA on 18.05.2024.
//

#include "../include/Constants.h"
#include "../include/Particle.h"

namespace Raylib {

#include <raylib.h>

}

#include <cmath>

void chillPlug(Particle* p, float friction, float ease, Raylib::Vector2 mousePos) {
    float dx = mousePos.x - p->x;
    float dy = mousePos.y - p->y;
    float distance = dx * dx + dy * dy;

    if (distance < MOUSE_RADIUS) {
        p->touched = true;
    }
    if (p->touched) {
        p->vx *= friction;
        p->vy *= friction;
        p->x += p->vx + (p->oX - p->x) * ease;
        p->y += p->vy + (p->oY - p->y) * ease;
    }
}

void whooshyPlug(Particle* p, float friction, float ease, Raylib::Vector2 mousePos) {
    auto dx = mousePos.x - p->x;
    auto dy = mousePos.y - p->y;
    auto distance = dx * dx + dy * dy;
    auto force = -MOUSE_RADIUS / distance;

    if (distance < MOUSE_RADIUS) {
        auto angle = std::atan2(dy,dx);
        p->vx += force * std::cos(angle);
        p->vy += force * std::sin(angle);
    }
    p->vx *= friction;
    p->vy *= friction;
    p->x += p->vx + (p->oX - p->x) * ease;
    p->y += p->vy + (p->oY - p->y) * ease;
}

void testPlug(Particle* p, float friction, float ease, Raylib::Vector2 mousePos) {
    auto dx = mousePos.x - p->x;
    auto dy = mousePos.y - p->y;
    auto distance = dx * dx + dy * dy;
    auto force = -MOUSE_RADIUS / distance;

    if (distance < MOUSE_RADIUS) {
        auto angle = std::atan2(dy,dx);
        p->vx -= force * std::cos(angle);
        p->vy -= force * std::sin(angle);
    }
    p->vx *= 0.8;
    p->vy *= 0.8;
    p->x += p->vx + (p->oX - p->x) * 0.1;
    p->y += p->vy + (p->oY - p->y) * 0.1;
}

extern "C" {

__declspec(dllexport) void plug(Particle* p, float friction, float ease, Raylib::Vector2 mousePos) {
    testPlug(p,friction,ease,mousePos);
}

}
