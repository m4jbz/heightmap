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

void draw_3d_plane(Camera camera, int grid_lines, Model model, Vector3 map_pos)
{
    BeginMode3D(camera);
    DrawModel(model, map_pos, 1.0f, WHITE);
    // DrawGrid(grid_lines, 1.0f);
    EndMode3D();
}

void draw_camera_info(Camera camera, int camera_mode, int mode)
{

    DrawText(TextFormat("Mode: %s", (camera_mode == CAMERA_FREE) ? "FREE" :
                                    (camera_mode == CAMERA_FIRST_PERSON) ? "FIRST_PERSON" :
                                    (camera_mode == CAMERA_THIRD_PERSON) ? "THIRD_PERSON" :
                                    (camera_mode == CAMERA_ORBITAL) ? "ORBITAL" : "CUSTOM"), 1200, 10, 18, RAYWHITE);
    DrawText(TextFormat("Projection: %s", (camera.projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
                                          (camera.projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"), 1200, 35, 18, RAYWHITE);
    DrawText("Camera mode keys: 1, 2, 3, 4", 1200, 60, 18, RAYWHITE);
    DrawText(mode == 1 ? "Estas en PRO MODE" : "NO estas en PRO MODE", 1200, 85, 18, RAYWHITE);
    DrawText(TextFormat("Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 1200, 110, 18, RAYWHITE);
    DrawText(TextFormat("Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z), 1200, 135, 18, RAYWHITE);
    DrawText(TextFormat("Up: (%06.3f, %06.3f, %06.3f)", camera.up.x, camera.up.y, camera.up.z), 1200, 160, 18, RAYWHITE);
}

void handle_camera_modes(Camera* camera, int* camera_mode, int* mode)
{
    if (IsKeyPressed(KEY_X)) {
        *mode = 1;
    }

    if (IsKeyPressed(KEY_U)) {
        *mode = 0;
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
        *mode = 0;
    }

    // goes back to the init camera initialization
    if (IsKeyPressed(INIT_MODE_KEY)) {
        *camera_mode = CAMERA_ORBITAL;
        camera->position = (Vector3) {(float)SCENE_SCALE, 10.0f, 0.0f};
        camera->target = (Vector3) {0.0f, 0.0f, 0.0f};
        camera->up = (Vector3) {0.0f, 1.0f, 0.0f};
        camera->projection = CAMERA_PERSPECTIVE;
        *mode = 0;
    }
}

void update_camera(int mode, Camera* camera, int camera_mode)
{
    if (mode) {
        UpdateCameraPro(camera,
            (Vector3){(IsKeyDown(KEY_W))*0.4f - (IsKeyDown(KEY_S))*0.4f,
                      (IsKeyDown(KEY_D))*0.4f - (IsKeyDown(KEY_A))*0.4f,
                      (IsKeyDown(KEY_SPACE))*0.4f - (IsKeyDown(KEY_LEFT_SHIFT))*0.4f},
            (Vector3){GetMouseDelta().x*(0.05f),
                      GetMouseDelta().y*(0.05f),
                      0.0f},
            GetMouseWheelMove()*2.0f);
    } else {
        UpdateCamera(camera, camera_mode);
    }
}
