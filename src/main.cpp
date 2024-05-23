namespace Raylib {

#include <raylib.h>

}
using namespace Raylib;

#include "Particle.h"
#include "Constants.h"
#include "AnimationEngine.h"

#include <windows.h>
#undef LoadImage

std::string getFileLocation() {
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

int main() {

    Raylib::InitWindow(winWidth, winHeight, "imageBanana");

    Raylib::SetWindowState(Raylib::FLAG_VSYNC_HINT | Raylib::FLAG_WINDOW_RESIZABLE | Raylib::FLAG_FULLSCREEN_MODE);

    auto shader = Raylib::LoadShader("../shaders/vs.glsl", "../shaders/fs.glsl");

    auto animEngine = AnimationEngine::getInstance();

    animEngine->loadImage("../images/lena.png");

    Raylib::ClearBackground(AnimationEngine::backgroundColor);

    Raylib::SetTargetFPS(60);

    animEngine->loadPlug(R"(G:\projects\repos\imageBanana\cmake-build-debug\lib\libplugs.dll)",
                           "G:/projects/repos/imageBanana/plugs/libplugs_v1.dll",
                           "plug");

    AnimationEngine::plug->loadAndAssignPlugin(&Particle::plug);

    while (!Raylib::WindowShouldClose()) {
        Raylib::BeginDrawing();

        Raylib::ClearBackground(AnimationEngine::backgroundColor);

            if (IsKeyPressed(Raylib::KEY_F5)) {
                animEngine->reset();
                AnimationEngine::plug->loadAndAssignPlugin(&Particle::plug);
            }

            if (IsKeyPressed(Raylib::KEY_F4)) {
                std::string location = getFileLocation();
                if (location.empty()) {
                    throw std::runtime_error("File not found!");
                }
                animEngine->loadImage(location.c_str());
                //Raylib::TraceLog(Raylib::LOG_WARNING, location);
            }

            if (IsKeyPressed(Raylib::KEY_F11)) {
                Raylib::ToggleFullscreen();
            }

            animEngine->updateParticles();

            animEngine->drawParticles();

        Raylib::EndDrawing();
    }

    Raylib::UnloadShader(shader);

    Raylib::CloseWindow();

    return 0;
}
