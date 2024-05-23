//
// Created by HORIA on 19.05.2024.
//
#include "Plugin.h"
#include <stdexcept>
#include <iostream>

Plugin::Plugin(const char *dllOgPath, const char *dllToLoad, const char *plugFuncName)
        :   m_dllOgPath{dllOgPath},
            m_dllToLoad{dllToLoad},
            m_plugFuncName{plugFuncName} {}

void Plugin::load_library() {
    m_handle = LoadLibraryA(m_dllToLoad.c_str());
    if (!m_handle) {
        std::cerr << "Could not load library: " << GetLastError() << std::endl;
        return;
    }

    m_op= (plugFunc)GetProcAddress(m_handle, m_plugFuncName.c_str());
    if (!m_op) {
        std::cerr << "Could not load function: " << GetLastError() << std::endl;
        FreeLibrary(m_handle);
        m_handle = nullptr;
    }
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
        FreeLibrary(m_handle);
    }
}

void Plugin::loadAndAssignPlugin(plugFunc* f) {
    unload_library();

    copy_file();

    m_handle = nullptr;
    m_op= nullptr;

    load_library();

    if (!m_op|| !m_handle) {
        throw std::runtime_error("Failed to load plug!");
    }
    *f = m_op;
}

Plugin::~Plugin() {
    unload_library();
}
