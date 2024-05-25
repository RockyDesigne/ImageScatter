//
// Created by HORIA on 23.05.2024.
//

#ifndef IMAGEBANANA_ANIMATIONENGINE_H
#define IMAGEBANANA_ANIMATIONENGINE_H

#include "Particle.h"
#include "ParticleVector.h"
#include "Constants.h"
#include "PluginInterface.h"
#include "OsObject.h"

#include <algorithm>

namespace Raylib {
#include <raylib.h>
}

using namespace Raylib;

#undef LoadImage

class AnimationEngine final {
public:
    static AnimationEngine* getInstance();

    int currWinHeight = winHeight;
    int currWinWidth = winWidth;
    static constexpr int maxParticles = winHeight * winHeight;
    static constexpr Raylib::Color backgroundColor = {255,255,255,0};

    OsObject* getOsObject();
    PluginInterface* getPlug();

    void reset();
    void updateParticles();
    void drawParticles();
    void loadParticles(Raylib::Color* pixels, int imgWidth, int imgHeight);
    void loadImage(const char* filePath);
    void loadPlug(PluginInterface* plug);
    void loadOsObject(OsObject* osObj);


    AnimationEngine(const AnimationEngine&) = delete;
    AnimationEngine& operator=(const AnimationEngine&) = delete;

private:

    AnimationEngine() = default;
    ~AnimationEngine();

    static AnimationEngine* m_instance;
    PluginInterface* m_plug = nullptr;
    OsObject* m_osObject = nullptr;

    ParticleVector<maxParticles> particles;
};


#endif //IMAGEBANANA_ANIMATIONENGINE_H
