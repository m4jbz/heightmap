#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "heightmap");

    Font font;
    font = LoadFont(FONT);

    // i dont really like to initialize variables like this, but i don't have a better idea
    // so it's going to be like that
    Camera camera = { 0 };
    // nochecking: i'm using SCENE_SCALE because i think thats how camera
    // position works, but it seems i'm an idiot.
    camera.position = (Vector3) {(float)SCENE_SCALE, 1000.0f, 0.0f};
    camera.target = (Vector3) {0.0f, 0.0f, 0.0f};
    camera.up = (Vector3) {0.0f, 1.0f, 0.0f};
    camera.fovy = 50.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Image image = LoadImage("assets/heightmap.png");
    Texture2D texture = LoadTextureFromImage(image);
    Mesh mesh = GenMeshHeightmap(image, (Vector3){1000, 500, 1000}); // how big the 3d model is
    Model model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    Vector3 map_pos = {-500.0f, 0.0f, -500.0f}; // is half the size because yk half in negative
    // and the other half in positive, so it's centered

    int camera_mode = CAMERA_ORBITAL;
    int mode = 0;

    UnloadImage(image);

    // this is magic, it keeps locked the cursor inside the window
    DisableCursor();
    SetTargetFPS(-1);

    // game loop
    while (!WindowShouldClose()) {
        // keeps updating the camera, if it's pro or not
        update_camera(mode, &camera, camera_mode);
        handle_camera_modes(&camera, &camera_mode, &mode);

        BeginDrawing();
        ClearBackground(BG_COLOR);

        draw_3d_plane(camera, SCENE_SCALE, model, map_pos);
        draw_fps(font);
        draw_camera_info(camera, camera_mode, mode);

        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();

    return 0;
}
