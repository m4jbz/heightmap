#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "heightmap");

    Font font;
    font = LoadFont(FONT);
    Camera camera = { 0 };
    camera.position = (Vector3) {20.0f, 10.0f, 0.0f};
    camera.target = (Vector3) {0.0f, 0.0f, 0.0f};
    camera.up = (Vector3) {0.0f, 1.0f, 0.0f};
    camera.fovy = 50.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    int camera_mode = CAMERA_ORBITAL;
    int pro_mode = 0;

    // this is magic, it keeps locked the cursor inside the window
    DisableCursor();
    SetTargetFPS(60);

    // game loop
    while (!WindowShouldClose()) {
        if (pro_mode) {
            UpdateCameraPro(&camera,
                (Vector3){(IsKeyDown(KEY_W))*0.4f - (IsKeyDown(KEY_S))*0.4f,
                          (IsKeyDown(KEY_D))*0.4f - (IsKeyDown(KEY_A))*0.4f,
                          (IsKeyDown(KEY_SPACE))*0.4f - (IsKeyDown(KEY_LEFT_SHIFT))*0.4f},
                (Vector3){GetMouseDelta().x*(0.05f),
                          GetMouseDelta().y*(0.05f),
                          0.0f},
                GetMouseWheelMove()*2.0f);
        } else {
            UpdateCamera(&camera, camera_mode);
        }

        handle_camera_modes(&camera, &camera_mode, &pro_mode);

        BeginDrawing();
            ClearBackground(BG_COLOR);

            draw_3d_plane(camera, 20);
            draw_fps(font);

            draw_camera_info(camera, camera_mode, pro_mode);

        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();

    return 0;
}
