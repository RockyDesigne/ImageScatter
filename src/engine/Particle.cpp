//
// Created by HORIA on 18.05.2024.
//

#include "Particle.h"

#include <cassert>
#include <cmath>

int Particle::size = 20;
float Particle::ease = 0.1f;
float Particle::friction = 0.95f;

void Particle::draw() {
    DrawRectangle(x,y,size,size, color);
}

void Particle::update() {

    testPlug();

}
//plugs

void Particle::boomPlug() {
    auto mousePos = Raylib::GetMousePosition();
    auto dx = mousePos.x - x;
    auto dy = mousePos.y - y;
    auto distance = dx * dx + dy * dy;
    auto force = -3000 / distance;

    if (Raylib::IsMouseButtonPressed(Raylib::MOUSE_BUTTON_LEFT)) {
        if (distance < MOUSE_RADIUS) {
            auto angle = std::atan2(dy, dx);
            vx += force * std::cos(angle);
            vy += force * std::sin(angle);
        }
        vx *= 0.9;
        vy *= 0.9;
        x += vx + (oX - x) * 0.1;
        y += vy + (oY - y) * 0.1;
    }
}

void Particle::testPlug() {
    auto mousePos = Raylib::GetMousePosition();
    auto dx = mousePos.x - x;
    auto dy = mousePos.y - y;
    auto distance = dx * dx + dy * dy;
    auto force = -3000 / distance;

    if (distance < MOUSE_RADIUS) {
        auto angle = std::atan2(dy, dx);
        vx += force * std::cos(angle);
        vy += force * std::sin(angle);
    }
    vx *= 0.9;
    vy *= 0.9;
    x += vx + (oX - x) * 0.1;
    y += vy + (oY - y) * 0.1;
}

void Particle::whooshyPlug() {
    auto mousePos = Raylib::GetMousePosition();
    auto dx = mousePos.x - x;
    auto dy = mousePos.y - y;
    auto distance = dx * dx + dy * dy;
    auto force = -MOUSE_RADIUS / distance;

    if (distance < MOUSE_RADIUS) {
        auto angle = std::atan2(dy,dx);
        vx += force * std::cos(angle);
        vy += force * std::sin(angle);
    }
    vx *= friction;
    vy *= friction;
    x += vx + (oX - x) * ease;
    y += vy + (oY - y) * ease;
}

void Particle::chillPlug() {
    auto mousePos = Raylib::GetMousePosition();
    float dx = mousePos.x - x;
    float dy = mousePos.y - y;
    float distance = dx * dx + dy * dy;

    if (distance < MOUSE_RADIUS) {
        touched = true;
    }
    if (touched) {
        vx *= friction;
        vy *= friction;
        x += vx + (oX - x) * ease;
        y += vy + (oY - y) * ease;
    }
}
