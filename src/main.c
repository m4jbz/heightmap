#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

#define BG_COLOR (Color) {18, 18, 18, 255}
#define WIDTH 1500
#define HEIGHT 1125

void draw_fps(Font font)
{
    Vector2 position = {10.0f, 10.0f};
    char message[16];
    sprintf(message, "%d\n", GetFPS());
    DrawTextEx(font, message, position, font.baseSize*4.0f, 2.0f, RAYWHITE);
}

int main(void)
{
    // start drawing
    InitWindow(WIDTH, HEIGHT, "heightmap");
    SetTargetFPS(60);

    Font font;
    font = LoadFont("assets/romulus.png");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BG_COLOR);
        draw_fps(font);


        EndDrawing();
    }

    UnloadFont(font);
    // end drawing
    CloseWindow();

    return 0;
}
