//
// Created by coren on 3/27/2022.
//

#include "board.h"
#include "cell.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

board_t *init_board() {
    board_t *board = malloc(sizeof(board_t));
    if (board == NULL) {
        fprintf(stderr, "failed to create board...");
        printf("%s", errno);
        exit(1);
    }

    srand(time(NULL));

    for (int e = 0; e < GRID_HEIGHT * GRID_WIDTH; ++e) {

        if (rand() % 3 == 2) {
            board->cells[e] = create_cell(true);
        } else {
            board->cells[e] = create_cell(false);
        }
    }
    return board;
}

bool check_status(board_t *board, int x, int y) {
    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) {
        return false;
    } else {
        return board->cells[(y * GRID_WIDTH) + x]->alive;
    }
}

void set_next_status(board_t *board, int x, int y, bool status) {
    board->cells[(y * GRID_WIDTH) + x]->next_round = status;
}

int alive_neighbours(board_t *board, int x, int y) {
    int count = 0;

    if (check_status(board, x - 1, y - 1)) {
        count++;
    }

    if (check_status(board, x + 0, y - 1)) {
        count++;
    }

    if (check_status(board, x + 1, y - 1)) {
        count++;
    }

    if (check_status(board, x - 1, y + 0)) {
        count++;
    }

    if (check_status(board, x + 1, y + 0)) {
        count++;
    }

    if (check_status(board, x - 1, y + 1)) {
        count++;
    }

    if (check_status(board, x + 0, y + 1)) {
        count++;
    }

    if (check_status(board, x + 1, y + 1)) {
        count++;
    }

    return count;
}

void play_round(board_t *board) {
    // go through the rules to see what happens to each cell
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            // rules

            int neighbours = alive_neighbours(board, x, y);
            bool status = check_status(board, x, y);

            if (status) {
                // if the cell is alive
                if (neighbours < 2 || neighbours > 3) {
                    set_next_status(board, x, y, false);

                } else if (neighbours == 2 || neighbours == 3) {
                    // Death by isolation: Each live cell with one or fewer live neighbors will die in the next generation.
                    set_next_status(board, x, y, true);
                }
            } else {
                // the cell is dead
                if (neighbours == 3) {
                    set_next_status(board, x, y, true);
                }
            }
        }
    }

    // apply the outcome
    for (int i = 0; i < sizeof(board->cells) / sizeof(cell_t *); ++i) {
        board->cells[i]->alive = board->cells[i]->next_round;
    }
}
