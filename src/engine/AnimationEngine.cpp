//
// Created by HORIA on 23.05.2024.
//
#include "AnimationEngine.h"
#include "MyRandom.h"

void AnimationEngine::reset() {
    for (std::size_t i = 0; i < particles.m_size; ++i) {
        particles.elems[i].x = std::clamp<float>(getRand() * winWidth, 0, static_cast<float>(winWidth) - static_cast<float>(Particle::size));
        particles.elems[i].y = std::clamp<float>(getRand() * winHeight, 0, static_cast<float>(winHeight) - static_cast<float>(Particle::size));
        particles.elems[i].touched = false;
    }
}

void AnimationEngine::updateParticles() {
    for (std::size_t i = 0; i < particles.m_size; ++i) {
        particles.elems[i].update();
    }
}

void AnimationEngine::drawParticles() {
    for (std::size_t i = 0; i < particles.m_size; ++i) {
        particles.elems[i].draw();
    }
}

void AnimationEngine::loadParticles(Raylib::Color* pixels, int imgWidth, int imgHeight) {
    for (int y = 0; y < imgHeight; y += GAP) {
        for (int x = 0; x < imgWidth; x += GAP) {
            Raylib::Color pixel = pixels[y * imgWidth + x];
            if (pixel.a > 0) {
                Particle tmp {};

                tmp.color = pixel;

                tmp.oX = static_cast<float>(x);
                tmp.oY = static_cast<float>(y);

                tmp.x = std::clamp<float>(getRand() * winWidth, 0, static_cast<float>(winWidth) - static_cast<float>(Particle::size));
                tmp.y = std::clamp<float>(getRand() * winHeight, 0, static_cast<float>(winHeight) - static_cast<float>(Particle::size));

                tmp.vx = getRand() * 2 - 1;
                tmp.vy = getRand() * 2 - 1;

                particles.push(tmp);
            }
        }
    }
}

void AnimationEngine::loadImage(const char* filePath) {
    particles.reset();

    Raylib::Image image = Raylib::LoadImage(filePath);
    Raylib::Image currImg = Raylib::GenImageColor(currWinWidth, currWinHeight, backgroundColor);

    Raylib::ImageCrop(&image, Raylib::Rectangle {0,0,
                                                 std::clamp<float>((float)image.width, 0, static_cast<float>(currWinWidth)),
                                                 std::clamp<float>((float)image.height,0,static_cast<float>(currWinHeight))});

    Raylib::ImageDraw(&currImg, image,
                      Raylib::Rectangle {0,0, static_cast<float>(currImg.width), static_cast<float>(currImg.height)},
                      Raylib::Rectangle {(static_cast<float>(currWinWidth)/2 - static_cast<float>(image.width) / 2),
                                         (static_cast<float>(currWinHeight) / 2 - static_cast<float>(image.height) / 2),
                                         static_cast<float>(image.width),
                                         static_cast<float>(image.height)},
                                         Raylib::WHITE);

    Raylib::UnloadImage(image);

    Raylib::Color* pixels = Raylib::LoadImageColors(currImg);

    loadParticles(pixels, currImg.width, currImg.height);

    Raylib::UnloadImageColors(pixels);
    Raylib::UnloadImage(currImg);
}

void AnimationEngine::run() {
    Raylib::BeginDrawing();

        Raylib::ClearBackground(AnimationEngine::backgroundColor);

        updateParticles();

        drawParticles();

    Raylib::EndDrawing();
}

void AnimationEngine::release() {
    delete this;
}

AnimationEngineInterface* getAnimPtr(void) {
    return new AnimationEngine;
}
