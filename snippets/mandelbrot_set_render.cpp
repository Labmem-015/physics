#include "mandelbrot_set_render.hpp"

#include <rlgl.h>

double previous_time = GetTime();
constexpr double target_fps = 60;
constexpr double target_time = 1.0 / target_fps;
int current_fps = 0;

void ManualEndDrawing() {
    static int frame_count = 0;
    static double fps_time_accumulator = 0.0;

    // flush the render batch data manually
    rlDrawRenderBatchActive();

    // swap the back and front buffers to display the frame
    SwapScreenBuffer();

    // handle frame rate limits
    auto delta = GetTime() - previous_time;
    if (delta < target_time) {
        WaitTime(target_time - delta);
    }
    current_fps = std::lround(1.0 / (GetTime() - previous_time));
    previous_time = GetTime();

    PollInputEvents();
}

void ManualDrawFPS() {
    DrawText(TextFormat("%i FPS", current_fps), 10, 10, 20, LIME);
    DrawText("vcpkg 6.0 EndDrawing patch active", 10, 40, 20, DARKBLUE);
}

void render_loop(std::vector<cl_uint> &pixels, int width, int height, float scale) {
    static_assert(sizeof(Color) == sizeof(cl_uint) && "Sizes of Color and cl_uint are not equal!");

    Image blank = GenImageColor(width, height, BLANK);
    Texture2D texture = LoadTextureFromImage(blank);
    UnloadImage(blank);

    while (!WindowShouldClose()) {
        UpdateTexture(texture, pixels.data());
        BeginDrawing();
        {
            ClearBackground(BLACK);
            DrawTexturePro(texture, Rectangle{0, 0, (float)width, (float)height},
                           Rectangle{0, 0, (float)(width * scale), (float)(height * scale)}, Vector2{0, 0}, 0.f, WHITE);
            ManualDrawFPS();
        }
        // TODO: apply fix for EndDrawing issue for vcpkg 6.0 version
        ManualEndDrawing();
    }

    UnloadTexture(texture);
}

