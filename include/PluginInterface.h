//
// Created by HORIA on 24.05.2024.
//

#ifndef IMAGEBANANA_PLUGININTERFACE_H
#define IMAGEBANANA_PLUGININTERFACE_H

//This interface describes the os specific functions that need to be implemented

#include <string>

class PluginInterface {
public:
    virtual void load_library() = 0;

    virtual void copy_file() = 0;

    virtual void unload_library() = 0;

    virtual void loadAndAssignPlugin(void* f) = 0;

    virtual ~PluginInterface() = default;

private:
};

#endif //IMAGEBANANA_PLUGININTERFACE_H
