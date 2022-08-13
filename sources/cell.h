//
// Created by coren on 3/27/2022.
//

#ifndef RAYLIB_TESTS_CELL_H
#define RAYLIB_TESTS_CELL_H

#include <stdbool.h>

#define CELL_SIZE 12

typedef struct cell {
    bool alive;
    bool next_round;
} cell_t;

cell_t *create_cell(bool alive);


#endif//RAYLIB_TESTS_CELL_H
