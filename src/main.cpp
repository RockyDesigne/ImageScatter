#include <iostream>
namespace Raylib {

#include <raylib.h>

}
#include <windows.h>
#include <random>
#include <cassert>

#include "Particle.h"
#include "Constants.h"

#undef LoadImage

/*
// Forward declaration of the LoadLibraryA function
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryA(const char* lpLibFileName);

// Typedef for the LoadLibraryA function pointer
typedef void*(__stdcall *LoadLibraryA_t)(const char* lpLibFileName);

// Forward declaration of the GetLastError function
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError();

// Typedef for the GetLastError function pointer
typedef unsigned long (__stdcall *GetLastError_t)();

// Forward declaration of the CopyFile function
extern "C" __declspec(dllimport) int __stdcall CopyFile(const char* lpExistingFileName, const char* lpNewFileName, int bFailIfExists);

// Typedef for the CopyFile function pointer
typedef int (__stdcall *CopyFile_t)(const char* lpExistingFileName, const char* lpNewFileName, int bFailIfExists);

// Forward declaration of the GetProcAddress function
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void* hModule, const char* lpProcName);

// Typedef for the GetProcAddress function pointer
typedef void*(__stdcall *GetProcAddress_t)(void* hModule, const char* lpProcName);

// Forward declaration of the FreeLibrary function
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(void* hModule);

// Typedef for the FreeLibrary function pointer
typedef int (__stdcall *FreeLibrary_t)(void* hModule);
*/

struct Plugin {

    //typedef void (*operation_func)(Particle *p, float friction, float ease, Raylib::Vector2 mousePos);

    using plugFunc = void (*)(Particle *p, float friction, float ease, Raylib::Vector2 mousePos);

    HMODULE m_handle = nullptr;
    plugFunc m_op = nullptr;

    const char* m_dllOgPath = nullptr;
    const char* m_dllToLoad = nullptr;
    const char* m_plugFuncName = nullptr;

    Plugin(const char* dllOgPath,const char* dllToLoad,const char* plugFuncName);

    void load_library();


    void copy_file();

    void unload_library();

    void loadAndAssignPlugin(plugFunc* f);

    ~Plugin();

};


Plugin::Plugin(const char *dllOgPath, const char *dllToLoad, const char *plugFuncName)
        :   m_dllOgPath{dllOgPath},
            m_dllToLoad{dllToLoad},
            m_plugFuncName{plugFuncName} {}

void Plugin::load_library() {
    m_handle = LoadLibrary(m_dllToLoad);
    if (!m_handle) {
        std::cerr << "Could not load library: " << GetLastError() << std::endl;
        return;
    }

    m_op= (plugFunc)GetProcAddress(m_handle, m_plugFuncName);
    if (!m_op) {
        std::cerr << "Could not load function: " << GetLastError() << std::endl;
        FreeLibrary(m_handle);
        m_handle = nullptr;
    }
}

void Plugin::copy_file() {
    bool copyResult = CopyFile(m_dllOgPath, m_dllToLoad, false);
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

    Raylib::SetWindowState(Raylib::FLAG_VSYNC_HINT | Raylib::FLAG_WINDOW_RESIZABLE);

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
