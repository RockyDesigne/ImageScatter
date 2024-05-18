#include <iostream>
#include <raylib.h>
#include <random>
#include <cassert>

constexpr int winHeight = 800, winWidth = 800, GAP = 1, MOUSE_RADIUS = 3000;

float getRand() {
    static std::random_device rd {};
    static std::seed_seq ss { rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    static std::mt19937 mt {ss};
    static std::uniform_real_distribution<float> dist {0, 1};

    return dist(mt);
}

struct Particle {
    float oX;
    float oY;
    float x;
    float y;
    float vx;
    float vy;
    static float ease;
    static int size;
    static float friction;
    Color color;

    void draw() {
        DrawRectangle(x,y,size,size, color);
    }

    void update() {

        auto mousePos = GetMousePosition();
        auto dx = mousePos.x - x;
        auto dy = mousePos.y - y;
        auto distance = dx * dx + dy * dy;
        auto force = -MOUSE_RADIUS / distance;

        if (distance < MOUSE_RADIUS) {
            auto angle = std::atan2(dy,dx);
            vx += force * std::cos(angle);
            vy += force * std::sin(angle);
        }
        vx *= friction;
        vy *= friction;
        x += vx + (oX - x) * ease;
        y += vy + (oY - y) * ease;
    }

    void warp() {

        auto angle = std::atan2(y,x);
        vx += std::cos(angle);
        vx += std::sin(angle);

        //x = GetMousePosition().x + getRand() * 100;
        //y = GetMousePosition().y + getRand() * 100;
    }

};

int Particle::size = 10;
float Particle::ease = 0.1f;
float Particle::friction = 0.95f;
constexpr int particleMaxSize = winHeight * winWidth;
static Particle particles[particleMaxSize];
int particleSize = 0;
constexpr Color backgroundColor = {255,255,255,0};

void pushParticle(const Color& color, int oX, int oY) {
    assert(particleSize < particleMaxSize && "Particles buffer overflow!");
    particles[particleSize].color = color;
    particles[particleSize].oX = oX;
    particles[particleSize].oY = oY;
    particles[particleSize].x = (getRand() * winWidth);
    particles[particleSize].y = (getRand() * winHeight);
    particles[particleSize].vx = (getRand() * 2 - 1);
    particles[particleSize].vy = (getRand() * 2 - 1);
    ++particleSize;
}

void loadParticles(Color* pixels, int imgWidth, int imgHeight) {
    for (int y = 0; y < imgHeight; y += GAP) {
        for (int x = 0; x < imgWidth; x += GAP) {
            Color pixel = pixels[y*imgWidth+x];
            if (pixel.a > 0) {
                pushParticle(pixel, x, y);
            }
        }
    }
}

int main() {


    InitWindow(winWidth, winHeight, "imageBanana");

    //auto lenaTexture = LoadTexture("../images/lena.png");

    auto lenaShader = LoadShader("../shaders/vs.glsl", "../shaders/fs.glsl");

    Image lenaImage = LoadImage("../images/lena.png");
    Image currImg = GenImageColor(winWidth, winHeight, backgroundColor);

    //ImageDrawRectangle(&currImg,0,0,winWidth,winHeight, backgroundColor);

    ImageDraw(&currImg, lenaImage,
              Rectangle {0,0, (float)currImg.width, (float)currImg.height},
              Rectangle {(float)(winWidth/2-lenaImage.width/2),(float)(winHeight/2-lenaImage.height/2), (float)lenaImage.width,(float)lenaImage.height}, WHITE);

    UnloadImage(lenaImage);

    Color* pixels = LoadImageColors(currImg);

    loadParticles(pixels, currImg.width, currImg.height);

    UnloadImageColors(pixels);

    auto texture = LoadTextureFromImage(currImg);

    ClearBackground(backgroundColor);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground(backgroundColor);

            //DrawTexture(texture, 0, 0, WHITE);

            for (int i = 0; i < particleSize; ++i) {
                particles[i].draw();
            }

            for (int i = 0; i < particleSize; ++i) {
                particles[i].update();
            }

            /*
            for (int i = 0; i < particleSize; ++i) {
                /*
                if (CheckCollisionPointCircle(Vector2(particles[i].x,particles[i].y),
                                              GetMousePosition(),
                                              16))
                {
                    particles[i].warp();
                }
            }
            */
        EndDrawing();

        //UnloadImage(currImg);
        //UnloadImageColors(pixels);
    }

    UnloadShader(lenaShader);
    UnloadImage(currImg);
    UnloadTexture(texture);

    CloseWindow();

    return 0;
}
