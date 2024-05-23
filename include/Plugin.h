//
// Created by HORIA on 19.05.2024.
//

#ifndef IMAGEBANANA_PLUGIN_H
#define IMAGEBANANA_PLUGIN_H

#include "Particle.h"

#include <string>

#define WIN_32_LEAN_AND_MEAN
#include <windows.h>

namespace Raylib {

#include <raylib.h>

}

using namespace Raylib;

struct Plugin {

    //typedef void (*operation_func)(Particle *p, float friction, float ease, Raylib::Vector2 mousePos);

    using plugFunc = void (*)(Particle *p, float friction, float ease, Raylib::Vector2 mousePos);

    HMODULE m_handle = nullptr;
    plugFunc m_op = nullptr;

    std::string m_dllOgPath{};
    std::string m_dllToLoad {};
    std::string m_plugFuncName {};

    Plugin(const char* dllOgPath,const char* dllToLoad,const char* plugFuncName);

    void load_library();

    void copy_file();

    void unload_library();

    void loadAndAssignPlugin(plugFunc* f);

    ~Plugin();

};

#endif
