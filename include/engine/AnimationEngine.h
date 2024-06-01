//
// Created by HORIA on 23.05.2024.
//

#ifndef IMAGEBANANA_ANIMATIONENGINE_H
#define IMAGEBANANA_ANIMATIONENGINE_H

#include "Particle.h"
#include "ParticleVector.h"
#include "Constants.h"

#define LIBRARY_EXPORT

#include "AnimationEngineInterface.h"

#include <algorithm>

namespace Raylib {
#include <raylib.h>
}

using namespace Raylib;

#undef LoadImage

class AnimationEngine : public AnimationEngineInterface {
public:
    static constexpr int currWinHeight = winHeight;
    static constexpr int currWinWidth = winWidth;
    static constexpr int maxParticles = winHeight * winHeight;
    static constexpr Raylib::Color backgroundColor = {255,255,255,0};

    void reset() override;
    void updateParticles() override;
    void drawParticles() override;
    void loadParticles(Raylib::Color* pixels, int imgWidth, int imgHeight) override;
    void loadImage(const char* filePath) override;
    void release() override;
    void run() override;

    AnimationEngine(const AnimationEngine&) = delete;
    AnimationEngine& operator=(const AnimationEngine&) = delete;

    ~AnimationEngine() = default;

    AnimationEngine() = default;
private:
    ParticleVector<maxParticles> particles;
};

#endif //IMAGEBANANA_ANIMATIONENGINE_H
