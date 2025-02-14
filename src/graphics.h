#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

#define BG_COLOR (Color) {18, 18, 18, 255}
#define FONT (const char*) "assets/romulus.png"
#define PLAYER_MODE_KEY KEY_P
#define INIT_MODE_KEY KEY_I
#define WIDTH 1500
#define HEIGHT 1125

void draw_fps(Font font);
void draw_3d_plane(Camera camera, int grid_lines);
void draw_camera_info(Camera camera, int camera_mode, int pro_mode);
void handle_camera_modes(Camera* camera, int* camera_mode, int* pro_mode);

#endif // GRAPHICS_H
