#ifndef CREATE_H
#define CREATE_H

#include<stdbool.h>
#include "board.h"

sudoku_t *create(bool difficulty);
int* array_create(int dim);
int box_index(int row, int col, int dim);

#endif 
