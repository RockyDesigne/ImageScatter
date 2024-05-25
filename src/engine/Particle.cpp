//
// Created by HORIA on 18.05.2024.
//

#include "Particle.h"
#include <cmath>
#include <cassert>

int Particle::size = 10;
float Particle::ease = 0.1f;
float Particle::friction = 0.95f;
void (*Particle::plug) (Particle* p, float friction, float ease, Raylib::Vector2 mousePos) = nullptr;

void Particle::draw() {
    DrawRectangle(x,y,size,size, color);
}

void Particle::update() {

    assert(plug && "Failed to load m_plug!");

    if (plug) {
        plug(this, friction, ease, Raylib::GetMousePosition());
    }

}

void Particle::warp() {

    auto angle = std::atan2(y,x);
    vx += std::cos(angle);
    vx += std::sin(angle);

    //x = GetMousePosition().x + getRand() * 100;
    //y = GetMousePosition().y + getRand() * 100;
}
