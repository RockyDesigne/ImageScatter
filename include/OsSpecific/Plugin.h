//
// Created by HORIA on 19.05.2024.
//

#ifndef IMAGEBANANA_PLUGIN_H
#define IMAGEBANANA_PLUGIN_H

#include "PluginInterface.h"

#include <string>

class Plugin : public PluginInterface {
public:
    //typedef void (*operation_func)(Particle *p, float friction, float ease, Raylib::Vector2 mousePos);

    //using plugFunc = void (*)(Particle *p, float friction, float ease, Raylib::Vector2 mousePos,bool isMousePressed);

    void* m_handle = nullptr;

    std::string m_dllOgPath{};
    std::string m_dllToLoad {};
    std::string m_plugFuncName {};

    Plugin(const char* dllOgPath,const char* dllToLoad);

    void reload_library() override;

    void load_library() override;

    void copy_file() override;

    void unload_library() override;

    void* get_function(const char* name) override;

    void loadAndAssignPlugin(void* f) override;

    ~Plugin();

};

#endif
