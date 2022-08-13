#include "board.h"
#include "consts.h"
#include "raylib.h"
//#include "rlgl.h"
#include <stdio.h>
#include <stdlib.h>

#define NEXT_GEN_INTERVAL_INITIAL (1.0f / 6)
#define FRAME_RATE 60

#define TEXT_SIZE 40

Camera2D *setup_cam() {
    Camera2D *camera = malloc(sizeof(Camera2D));
    camera->target = (Vector2){0.0f, 0.0f};
    camera->offset = (Vector2){0.0f, 0.0f};
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;
    return camera;
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");

    SetTargetFPS(FRAME_RATE);

    Camera2D *camera = setup_cam();

    board_t *board = init_board();

    int frame = 0;
    bool pause = true;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            pause = !pause;
        }

        if (IsKeyPressed(KEY_R)) {
            for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i) {
                free(board->cells[i]);
            }
            free(board);
            board = init_board();
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            int x = GetMouseX() / CELL_SIZE;
            int y = GetMouseY() / CELL_SIZE;
            if (!(x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)) {
                if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
                    board->cells[(y * GRID_WIDTH) + x]->alive = false;
                    set_next_status(board, x, y, false);
                } else {
                    board->cells[(y * GRID_WIDTH) + x]->alive = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? true : false;
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(*camera);
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            for (int x = 0; x < GRID_WIDTH; ++x) {
                if (check_status(board, x, y)) {
                    DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);
                }
                DrawRectangleLines(x * CELL_SIZE, y * CELL_SIZE, 1, 1, GRAY);
            }
        }
        EndMode2D();

        DrawFPS(SCREEN_WIDTH - 80, 0);

        if (pause) {
            DrawText("Paused", 2, 2, TEXT_SIZE, RED);
        }

        if (!pause) {
            if (frame == (int) (FRAME_RATE * NEXT_GEN_INTERVAL_INITIAL)) {
                play_round(board);
                frame = 1;
            }
            frame++;
        }

        EndDrawing();
    }

    free(camera);
    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i) {
        free(board->cells[i]);
    }
    free(board);
    CloseWindow();
    return 0;
}