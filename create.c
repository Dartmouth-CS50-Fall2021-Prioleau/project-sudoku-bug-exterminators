#include "create.h"
#include "read.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

sudoku_t *create(bool difficult){
    sudoku_t* sudoku = read(difficult);
    box_t*** board = sudoku->board;

    // get dim
    int dim = sudoku->dim;
    
    // row used record
    int* row = array_create(dim);

    // column used record
    int* col = array_create(dim);

    // box used record
    int* box = array_create(dim);

    sudoku->rows = row;
    sudoku->columns = col;
    sudoku->boxes = box;

    // initialization of rows, cols, boxes
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            int num = board[i][j]->num;
            if(num != 0){
                int k = box_index(i, j, dim);
                row[i] |= 2<<(num - 1);
                col[j] |= 2<<(num - 1);
                box[k] |= 2<<(num - 1);
            }
        }
    }

    // initialization of grid possibility
    for(int i = 0; i< dim; i++){
        for(int j = 0; j<dim; j++){
            box_t* grid = board[i][j];
            if(grid->num != 0){
                int k = box_index(i, j, dim);
                grid->possible = ~(row[i] | col[j] | box[k]);
            }
        }
    }

    return sudoku;
}

int* array_create(int dim){
    int* array = calloc(dim, sizeof(int));
    if(array == NULL){
        fprintf(stderr, "Failed to malloc for array\n");
        exit(2);
    }
    return array;
}

int box_index(int row, int col, int dim){
    int box_size = sqrt(dim);
    return (row % box_size) + (col % box_size);
}