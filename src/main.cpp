namespace Raylib {

#include <raylib.h>

}

using namespace Raylib;

#include "Particle.h"
#include "Constants.h"
#include "AnimationEngine.h"
#include "Plugin.h"
#include "WindowsObject.h"

int main() {

    Raylib::InitWindow(winWidth, winHeight, "imageBanana");

    Raylib::SetWindowState(Raylib::FLAG_VSYNC_HINT | Raylib::FLAG_WINDOW_RESIZABLE | Raylib::FLAG_FULLSCREEN_MODE);

    auto shader = Raylib::LoadShader("../shaders/vs.glsl", "../shaders/fs.glsl");

    auto animEngine = AnimationEngine::getInstance();

    animEngine->loadImage("../images/lena.png");

    Raylib::ClearBackground(AnimationEngine::backgroundColor);

    Raylib::SetTargetFPS(60);


    {
        auto pl = new Plugin {R"(G:\projects\repos\imageBanana\cmake-build-debug\lib\libplugs.dll)",
                              "G:/projects/repos/imageBanana/plugs/libplugs_v1.dll",
                              "plug"};
        animEngine->loadPlug(pl);
    }

    auto plug = animEngine->getPlug();

    {
        auto osObj = new WindowsObject {};
        animEngine->loadOsObject(osObj);
    }

    auto osObj = animEngine->getOsObject();

    plug->loadAndAssignPlugin(&Particle::plug);

    while (!Raylib::WindowShouldClose()) {
        Raylib::BeginDrawing();

        Raylib::ClearBackground(AnimationEngine::backgroundColor);

            if (IsKeyPressed(Raylib::KEY_F5)) {
                animEngine->reset();
                plug->loadAndAssignPlugin(&Particle::plug);
            }

            if (IsKeyPressed(Raylib::KEY_F4)) {
                std::string location = osObj->getFileLocation();
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
