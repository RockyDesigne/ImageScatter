//
// Created by HORIA on 18.05.2024.
//

#include "Particle.h"
#include <cmath>
#include <cassert>

int Particle::size = 10;
float Particle::ease = 0.1f;
float Particle::friction = 0.95f;
bool Particle::isMousePressed = false;
Particle::plugFunc Particle::plug = nullptr;

void Particle::draw() {
    DrawRectangle(x,y,size,size, color);
}

void Particle::update() {

    assert(plug && "Failed to load m_plug!");

    PluginState pluginState {
        .friction = friction,
        .ease = ease,
        .mousePos = Raylib::GetMousePosition(),
        .isMousePressed = Raylib::IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
    };

    if (plug) {
        plug(this, &pluginState);
    }

}
