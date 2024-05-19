#include <iostream>
namespace Raylib {

#include <raylib.h>

}
#include <cstdarg>

#include <random>
#include <cassert>

#include "Particle.h"
#include "Constants.h"
#include "Plugin.h"

#include <windows.h>
#undef LoadImage

float getRand() {
    static std::random_device rd {};
    static std::seed_seq ss { rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    static std::mt19937 mt {ss};
    static std::uniform_real_distribution<float> dist {0, 1};

    return dist(mt);
}

constexpr int particleMaxSize = winHeight * winWidth;
static Particle particles[particleMaxSize];
int particleSize = 0;
constexpr Raylib::Color backgroundColor = {255,255,255,0};

void pushParticle(const Raylib::Color& color, int oX, int oY, float x, float y, float vx, float vy) {
    assert(particleSize < particleMaxSize && "Particles buffer overflow!");
    particles[particleSize].color = color;
    particles[particleSize].oX = oX;
    particles[particleSize].oY = oY;
    particles[particleSize].x = x;
    particles[particleSize].y = y;
    particles[particleSize].vx = vx;
    particles[particleSize].vy = vy;
    ++particleSize;
}

void loadParticles(Raylib::Color* pixels, int imgWidth, int imgHeight) {
    for (int y = 0; y < imgHeight; y += GAP) {
        for (int x = 0; x < imgWidth; x += GAP) {
            Raylib::Color pixel = pixels[y*imgWidth+x];
            if (pixel.a > 0) {
                pushParticle(pixel,
                             x,
                             y,
                             std::clamp<float>(getRand() * winWidth,0,winWidth - Particle::size),
                             std::clamp<float>(getRand() * winHeight,0,winHeight - Particle::size),
                             getRand() * 2 - 1,
                             getRand() * 2 -1);
            }
        }
    }
}

void resetState() {
    for (int i = 0; i < particleSize; ++i) {
        particles[i].x = std::clamp<float>(getRand() * winWidth,0,winWidth - Particle::size);
        particles[i].y = std::clamp<float>(getRand() * winHeight,0,winHeight - Particle::size);
        particles[i].touched = false;
    }
}

int main() {

    const char* filePath = "../images/lena.png";
    const char* dllOgPath = R"(G:\projects\repos\imageBanana\cmake-build-debug\lib\libplugs.dll)";
    const char* dllToLoad = "G:/projects/repos/imageBanana/plugs/libplugs_v1.dll";

    Raylib::InitWindow(winWidth, winHeight, "imageBanana");

    Raylib::SetWindowState(Raylib::FLAG_VSYNC_HINT | Raylib::FLAG_WINDOW_RESIZABLE | Raylib::FLAG_FULLSCREEN_MODE);

    auto shader = Raylib::LoadShader("../shaders/vs.glsl", "../shaders/fs.glsl");

    Raylib::Image image = Raylib::LoadImage(filePath);
    Raylib::Image currImg = Raylib::GenImageColor(winWidth, winHeight, backgroundColor);

    Raylib::ImageCrop(&image, Raylib::Rectangle {0,0,
                                 std::clamp<float>((float)image.width, 0, winWidth),
                                 std::clamp<float>((float)image.height,0,winHeight)});

    Raylib::ImageDraw(&currImg, image,
                      Raylib::Rectangle {0,0, (float)currImg.width, (float)currImg.height},
                      Raylib::Rectangle {(float)(winWidth/2 - image.width / 2), (float)(winHeight / 2 - image.height / 2), (float)image.width, (float)image.height}, Raylib::WHITE);

    Raylib::UnloadImage(image);

    Raylib::Color* pixels = Raylib::LoadImageColors(currImg);

    loadParticles(pixels, currImg.width, currImg.height);

    Raylib::UnloadImageColors(pixels);

    auto texture = Raylib::LoadTextureFromImage(currImg);

    Raylib::ClearBackground(backgroundColor);

    Raylib::SetTargetFPS(60);

    Plugin plugin {dllOgPath, dllToLoad, "plug"};

    plugin.loadAndAssignPlugin(&Particle::plug);

    while (!Raylib::WindowShouldClose()) {
        Raylib::BeginDrawing();

        Raylib::ClearBackground(backgroundColor);

            if (IsKeyPressed(Raylib::KEY_F5)) {
                resetState();
                plugin.loadAndAssignPlugin(&Particle::plug);
            }

            if (IsKeyPressed(Raylib::KEY_F11)) {
                Raylib::ToggleFullscreen();
            }

            for (int i = 0; i < particleSize; ++i) {
                particles[i].update();
            }

            for (int i = 0; i < particleSize; ++i) {
                particles[i].draw();
            }

        Raylib::EndDrawing();
    }

    Raylib::UnloadShader(shader);
    Raylib::UnloadImage(currImg);
    Raylib::UnloadTexture(texture);

    Raylib::CloseWindow();

    return 0;
}
