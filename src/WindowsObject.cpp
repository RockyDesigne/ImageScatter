//
// Created by HORIA on 24.05.2024.
//
#include "WindowsObject.h"

#include <windows.h>

std::string WindowsObject::getFileLocation() {
    OPENFILENAME ofn;
    char szFile[260];

    ZeroMemory(&ofn, sizeof ofn);
    ofn.lStructSize = sizeof ofn;
    ofn.hwndOwner = GetForegroundWindow();

    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof szFile;
    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = R"(G:\projects\repos\imageBanana\images)";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    // Display the Open File dialog box
    if (GetOpenFileName(&ofn) == TRUE) {
        return ofn.lpstrFile;
    } else {
        return {};
    }
}

WindowsObject::~WindowsObject() = default;
