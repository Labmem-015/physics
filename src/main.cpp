#include "config.hpp"

using namespace phys;

int main(int, char **) {
    std::println("Hello, World!");
    std::println("Config:\n\twidth: {}\n\theight: {}\n\tfps: {}\n\ttitle: {}", config.screen_width,
                 config.screen_height, config.fps, config.title);
    std::println("\taddr: {}", (void *)&config);
    InitWindow(config.screen_width, config.screen_height, config.title.c_str());
    SetTargetFPS(config.fps);

    // main loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Hello, World!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
