namespace Raylib {

#include <raylib.h>

}

using namespace Raylib; // this is done to avoid naming conflicts with windows.h (yes, it's a hack)

#include <stdexcept>

#include "Constants.h"
#include "Plugin.h"
#include "WindowsObject.h"
#include "AnimationEngineInterface.h"

int main() {

    Raylib::InitWindow(winWidth, winHeight, "imageBanana");

    Raylib::SetWindowState(Raylib::FLAG_VSYNC_HINT | Raylib::FLAG_WINDOW_RESIZABLE | Raylib::FLAG_FULLSCREEN_MODE);

    auto shader = Raylib::LoadShader("../shaders/vs.glsl", "../shaders/fs.glsl");

    Color bkgColor {255,255,255,0};

    Raylib::ClearBackground(bkgColor);

    Raylib::SetTargetFPS(60);

    Plugin pl {R"(G:\projects\repos\imageBanana\cmake-build-debug\lib\libplugs.dll)",
                          "G:/projects/repos/imageBanana/plugs/libplugs_v1.dll"};
    pl.load_library();

    WindowsObject osObj {};

    auto f = reinterpret_cast<ANIM_ENG_PTR>(pl.get_function("getAnimPtr"));

    AnimationEngineInterface* animEngine = f();
    animEngine->reassignPlug(pl.get_function("plug"));
    animEngine->loadImage("../images/lena.png");

    //update(animEngine);

    while (!Raylib::WindowShouldClose()) {

        if (IsKeyPressed(Raylib::KEY_F5)) {
            animEngine->release();
            pl.reload_library();
            auto tmp = reinterpret_cast<ANIM_ENG_PTR>(pl.get_function("getAnimPtr"));
            animEngine = tmp();
            animEngine->reset();
            animEngine->reassignPlug(pl.get_function("plug"));
            animEngine->loadImage("../images/lena.png");
        }

        if (IsKeyPressed(Raylib::KEY_F4)) {
            std::string location = osObj.getFileLocation();
            if (location.empty()) {
                throw std::runtime_error("File not found!");
            }
            animEngine->loadImage(location.c_str());
            //Raylib::TraceLog(Raylib::LOG_WARNING, location);
        }

        if (IsKeyPressed(Raylib::KEY_F11)) {
            Raylib::ToggleFullscreen();
        }


        Raylib::BeginDrawing();

            Raylib::ClearBackground(bkgColor);

            animEngine->updateParticles();

            animEngine->drawParticles();

        Raylib::EndDrawing();

        //update(animEngine);

    }

    Raylib::UnloadShader(shader);

    Raylib::CloseWindow();

    animEngine->release();

    return 0;
}
