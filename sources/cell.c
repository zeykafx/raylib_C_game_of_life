//
// Created by coren on 3/27/2022.
//

#include "cell.h"
#include <stdlib.h>
#include <stdio.h>

cell_t *create_cell(bool alive) {
    cell_t *cell = malloc(sizeof(cell_t));
    if (cell == NULL) {
        fprintf(stderr, "failed to create cell...");
        printf("%s", errno);
        exit(1);
    }

    cell->alive = alive;
    cell->next_round = false;

    return cell;
}
