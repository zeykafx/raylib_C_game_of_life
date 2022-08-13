//
// Created by coren on 3/27/2022.
//

#ifndef RAYLIB_TESTS_BOARD_H
#define RAYLIB_TESTS_BOARD_H

#include "cell.h"
#include "consts.h"
#include "raylib.h"

typedef struct board {
    cell_t *cells[GRID_WIDTH * GRID_HEIGHT];
} board_t;

board_t *init_board();

bool check_status(board_t *board, int x, int y);

void set_next_status(board_t *board, int x, int y, bool status);

int alive_neighbours(board_t *board, int x, int y);

void play_round(board_t *board);

#endif//RAYLIB_TESTS_BOARD_H
