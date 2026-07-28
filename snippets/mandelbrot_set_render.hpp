#pragma once

inline void render_loop(std::vector<cl_uint> &pixels, int width, int height, float scale = 1.0f) {
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
            DrawFPS(10, 10);
        }
        EndDrawing();

        // TODO: Remove after fix
        PollInputEvents();
        SwapScreenBuffer();
    }

	UnloadTexture(texture);
}
