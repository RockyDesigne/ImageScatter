//
// Created by HORIA on 19.05.2024.
//
#include "Plugin.h"

#include <stdexcept>
#include <iostream>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

Plugin::Plugin(const char *dllOgPath, const char *dllToLoad)
        :   m_dllOgPath{dllOgPath},
            m_dllToLoad{dllToLoad} {}

void Plugin::load_library() {
    copy_file();
    m_handle = LoadLibraryA(m_dllToLoad.c_str());
    if (!m_handle) {
        std::cerr << "Could not load library: " << GetLastError() << std::endl;
        return;
    }
}

void* Plugin::get_function(const char* funcName) {
    void* f = nullptr;
    f = reinterpret_cast<void*>(GetProcAddress(reinterpret_cast<HMODULE>(m_handle), funcName));
    if (!f) {
        std::cerr << "Could not load function: " << GetLastError() << std::endl;
        FreeLibrary(reinterpret_cast<HMODULE>(m_handle));
        m_handle = nullptr;
    }
    return f;
}

void Plugin::copy_file() {
    bool copyResult = CopyFileA(m_dllOgPath.c_str(), m_dllToLoad.c_str(), false);
    if (!copyResult) {
        DWORD error = GetLastError();
        std::cerr << "Failed to copy file. Error code: " << error << std::endl;
    }
}

void Plugin::unload_library() {
    if (m_handle) {
        FreeLibrary(reinterpret_cast<HMODULE>(m_handle));
    }
}

void Plugin::loadAndAssignPlugin(void* f) {
    unload_library();

    copy_file();

    m_handle = nullptr;

    load_library();

    if (!m_handle) {
        throw std::runtime_error("Failed to load m_plug!");
    }
}

void Plugin::reload_library() {
    unload_library();

    copy_file();

    m_handle = nullptr;

    load_library();
}

Plugin::~Plugin() {
    FreeLibrary(reinterpret_cast<HMODULE>(m_handle));
}
