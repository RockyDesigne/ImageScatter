//
// Created by HORIA on 18.05.2024.
//

#include "Constants.h"
#include "Particle.h"
#include "AnimationEngine.h"
#include "PluginState.h"

namespace Raylib {

#include <raylib.h>

}

#include <cmath>

void chillPlug(Particle* p, PluginState* pluginState) {
    auto mousePos = pluginState->mousePos;
    auto friction = pluginState->friction;
    auto ease = pluginState->ease;
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

void whooshyPlug(Particle* p, PluginState* pluginState) {
    auto mousePos = pluginState->mousePos;
    auto friction = pluginState->friction;
    auto ease = pluginState->ease;
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

void testPlug(Particle* p, PluginState* pluginState) {
    auto mousePos = pluginState->mousePos;
    auto friction = pluginState->friction;
    auto ease = pluginState->ease;
    auto dx = mousePos.x - p->x;
    auto dy = mousePos.y - p->y;
    auto distance = dx * dx + dy * dy;
    auto force = -3000 / distance;

        if (distance < MOUSE_RADIUS) {
            auto angle = std::atan2(dy, dx);
            p->vx += force * std::cos(angle);
            p->vy += force * std::sin(angle);
        }
        p->vx *= 0.9;
        p->vy *= 0.9;
        p->x += p->vx + (p->oX - p->x) * 0.1;
        p->y += p->vy + (p->oY - p->y) * 0.1;
}

void boomPlug(Particle* p, PluginState* pluginState) {
    auto mousePos = pluginState->mousePos;
    auto friction = pluginState->friction;
    auto ease = pluginState->ease;
    auto dx = mousePos.x - p->x;
    auto dy = mousePos.y - p->y;
    auto distance = dx * dx + dy * dy;
    auto force = -3000 / distance;

        if (pluginState->isMousePressed) {
            if (distance < MOUSE_RADIUS) {
                auto angle = std::atan2(dy, dx);
                p->vx += force * std::cos(angle);
                p->vy += force * std::sin(angle);
            }
            p->vx *= 0.9;
            p->vy *= 0.9;
            p->x += p->vx + (p->oX - p->x) * 0.1;
            p->y += p->vy + (p->oY - p->y) * 0.1;
        }
}

extern "C" {

__declspec(dllexport) void update(AnimationEngine* animEngine) {

}

__declspec(dllexport) void plug(Particle* p, PluginState* pluginState) {
    boomPlug(p,pluginState);
}

}
