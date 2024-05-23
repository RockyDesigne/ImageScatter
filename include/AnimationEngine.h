//
// Created by HORIA on 23.05.2024.
//

#ifndef IMAGEBANANA_ANIMATIONENGINE_H
#define IMAGEBANANA_ANIMATIONENGINE_H

#include "Particle.h"
#include "ParticleVector.h"
#include "Constants.h"
#include "Plugin.h"

#include <algorithm>

namespace Raylib {
#include <raylib.h>
}

using namespace Raylib;

#undef LoadImage

class AnimationEngine {
public:
    static AnimationEngine* getInstance();

    static Plugin* plug;

    int currWinHeight = winHeight;
    int currWinWidth = winWidth;
    static constexpr int maxParticles = winHeight * winHeight;
    static constexpr Raylib::Color backgroundColor = {255,255,255,0};

    void reset();
    void updateParticles();
    void drawParticles();
    void loadParticles(Raylib::Color* pixels, int imgWidth, int imgHeight);
    void loadImage(const char* filePath);
    void loadPlug(const char* dllOgPath, const char* dllToLoad, const char* plugName);


    AnimationEngine(const AnimationEngine&) = delete;
    AnimationEngine& operator=(const AnimationEngine&) = delete;

private:

    const char* m_dllOgPath = R"(G:\projects\repos\imageBanana\cmake-build-debug\lib\libplugs.dll)";
    const char* m_dllToLoad = "G:/projects/repos/imageBanana/plugs/libplugs_v1.dll";

    char* m_currFile = nullptr;

    AnimationEngine() = default;
    ~AnimationEngine();

    static AnimationEngine* instance;

    ParticleVector<maxParticles> particles;
};


#endif //IMAGEBANANA_ANIMATIONENGINE_H
