#pragma once

inline Image create_image(std::vector<cl_uint> &pixels, int width, int height) {
    Image image{
        .data = pixels.data(),
        .width = width,
        .height = height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
    };
    return image;
}

inline void render_loop(std::vector<cl_uint> &pixels) {
    static_assert(sizeof(Color) == sizeof(cl_uint) && "Sizes of Color and cl_uint are not equal!");

    Color color;
    while (!WindowShouldClose()) {
        BeginDrawing();

        EndDrawing();

        // TODO: Remove after fix
        PollInputEvents();
        SwapScreenBuffer();
    }
}
