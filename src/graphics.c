#include "graphics.h"

void draw_fps(Font font)
{
    Vector2 position = {10.0f, 10.0f};
    float font_size = font.baseSize*3.0f;
    float spacing = 2.0f;
    char message[5]; // it just 2 digit numnber (60), so 5 bytes is enough
    sprintf(message, "%d\n", GetFPS());
    DrawTextEx(font, message, position, font_size, spacing, RAYWHITE);
}

void draw_3d_plane(Camera camera, int grid_lines)
{
    BeginMode3D(camera);
        DrawGrid(grid_lines, 1.0f);
    EndMode3D();
}

void draw_camera_info(Camera camera, int camera_mode, int pro_mode)
{

    DrawText(TextFormat("Mode: %s", (camera_mode == CAMERA_FREE) ? "FREE" :
                                    (camera_mode == CAMERA_FIRST_PERSON) ? "FIRST_PERSON" :
                                    (camera_mode == CAMERA_THIRD_PERSON) ? "THIRD_PERSON" :
                                    (camera_mode == CAMERA_ORBITAL) ? "ORBITAL" : "CUSTOM"), 1250, 10, 18, RAYWHITE);
    DrawText(TextFormat("Projection: %s", (camera.projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
                                          (camera.projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"), 1250, 35, 18, RAYWHITE);
    DrawText("Camera mode keys: 1, 2, 3, 4", 1250, 60, 18, RAYWHITE);
    DrawText(pro_mode == 1 ? "Estas en PRO MODE" : "NO estas en PRO MODE", 1250, 85, 18, RAYWHITE);
}

void handle_camera_modes(Camera* camera, int* camera_mode, int* pro_mode)
{
    if (IsKeyPressed(KEY_X)) {
        *pro_mode = 1;
    }

    if (IsKeyPressed(KEY_ONE)) {
        *camera_mode = CAMERA_FREE;
        camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
    }

    if (IsKeyPressed(KEY_TWO)) {
        *camera_mode = CAMERA_FIRST_PERSON;
        camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
    }

    if (IsKeyPressed(KEY_THREE)) {
        *camera_mode = CAMERA_THIRD_PERSON;
        camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
    }

    if (IsKeyPressed(KEY_FOUR)) {
        *camera_mode = CAMERA_ORBITAL;
        camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
    }

    if (IsKeyPressed(PLAYER_MODE_KEY)) {
        *camera_mode = CAMERA_FIRST_PERSON;
        camera->projection = CAMERA_PERSPECTIVE;
        camera->position = (Vector3) {0.0f, 2.0f, 4.0f};
        camera->target = (Vector3) {0.0f, 2.0f, 0.0f};
        camera->up = (Vector3) {0.0f, 1.0f, 0.0f};
        *pro_mode = 0;
    }

    if (IsKeyPressed(INIT_MODE_KEY)) {
        *camera_mode = CAMERA_ORBITAL;
        camera->position = (Vector3) {20.0f, 10.0f, 0.0f};
        camera->target = (Vector3) {0.0f, 0.0f, 0.0f};
        camera->up = (Vector3) {0.0f, 1.0f, 0.0f};
        camera->projection = CAMERA_PERSPECTIVE;
        *pro_mode = 0;
    }
}
