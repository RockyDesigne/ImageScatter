//
// Created by HORIA on 23.05.2024.
//
#include "AnimationEngine.h"
#include "MyRandom.h"


Plugin* AnimationEngine::plug = nullptr;
AnimationEngine* AnimationEngine::instance = nullptr;

AnimationEngine* AnimationEngine::getInstance() {
    if (!instance) {
        instance = new AnimationEngine;
    }
    return instance;
}

void AnimationEngine::reset() {
    for (int i = 0; i < particles.m_size; ++i) {
        particles.elems[i].x = std::clamp<float>(getRand() * winWidth, 0, winWidth - Particle::size);
        particles.elems[i].y = std::clamp<float>(getRand() * winHeight, 0, winHeight - Particle::size);
        particles.elems[i].touched = false;
    }
}

void AnimationEngine::updateParticles() {
    for (int i = 0; i < particles.m_size; ++i) {
        particles.elems[i].update();
    }
}

void AnimationEngine::drawParticles() {
    for (int i = 0; i < particles.m_size; ++i) {
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

                tmp.x = std::clamp<float>(getRand() * winWidth, 0, static_cast<float>(winWidth) - Particle::size);
                tmp.y = std::clamp<float>(getRand() * winHeight, 0, static_cast<float>(winHeight) - Particle::size);

                tmp.vx = getRand() * 2 - 1;
                tmp.vy = getRand() * 2 - 1;

                particles.push(tmp);
            }
        }
    }
}

AnimationEngine::~AnimationEngine() {
    delete plug;
    delete instance;
}

void AnimationEngine::loadImage(const char* filePath) {
    particles.reset();

    Raylib::Image image = Raylib::LoadImage(filePath);
    Raylib::Image currImg = Raylib::GenImageColor(currWinWidth, currWinHeight, backgroundColor);

    Raylib::ImageCrop(&image, Raylib::Rectangle {0,0,
                                                 std::clamp<float>((float)image.width, 0, currWinWidth),
                                                 std::clamp<float>((float)image.height,0,currWinHeight)});

    Raylib::ImageDraw(&currImg, image,
                      Raylib::Rectangle {0,0, (float)currImg.width, (float)currImg.height},
                      Raylib::Rectangle {(float)(currWinWidth/2 - image.width / 2), (float)(currWinHeight / 2 - image.height / 2), (float)image.width, (float)image.height}, Raylib::WHITE);

    Raylib::UnloadImage(image);

    Raylib::Color* pixels = Raylib::LoadImageColors(currImg);

    loadParticles(pixels, currImg.width, currImg.height);

    Raylib::UnloadImageColors(pixels);
    Raylib::UnloadImage(currImg);
}

void AnimationEngine::loadPlug(const char *dllOgPath, const char *dllToLoad, const char *plugName) {
    delete plug;
    plug = new Plugin {dllOgPath, dllToLoad, plugName};
}
