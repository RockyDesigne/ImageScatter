//
// Created by HORIA on 01.06.2024.
//

#ifndef IMAGEBANANA_ANIMATIONENGINEINTERFACE_H
#define IMAGEBANANA_ANIMATIONENGINEINTERFACE_H

#if defined(LIBRARY_EXPORT) // inside DLL
#   define LIBAPI   __declspec(dllexport)
#else // outside DLL
#   define LIBAPI   __declspec(dllimport)
#endif  // LIBRARY_EXPORT

namespace Raylib {
#include <raylib.h>
}

using namespace Raylib;

class AnimationEngineInterface {
public:
    virtual void reset() = 0;
    virtual void updateParticles() = 0;
    virtual void drawParticles() = 0;
    virtual void loadParticles(Raylib::Color* pixels, int imgWidth, int imgHeight) = 0;
    virtual void loadImage(const char* filePath) = 0;
    virtual void release() = 0;
    virtual void reassignPlug(void*) = 0;
};

extern "C" LIBAPI AnimationEngineInterface* getAnimPtr(void);

using ANIM_ENG_PTR = AnimationEngineInterface* (*)(void);

#endif //IMAGEBANANA_ANIMATIONENGINEINTERFACE_H
