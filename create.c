#include "create.h"
#include "read.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Alan Sun, Arden Guo
 * CS50, Fall 2021, Sudoku Project
 * Display sudoku board (display.c)
 *
 * This module contains code that initialize the data structure of 
 * a sudoku board. After reading from the stdin, the 2D board has been
 * set up. This module tries to initialize the rows used, col used, and
 * box used. Initializing the possible numbers of each grid is also 
 * implemented here.
 * 
 * @Data structure:
 * An integer is used to represent which number from 1 to 9 has been used.
 * The bit format of the integer with 1s represents the current possition 
 * has been used, while 0s represents not used yet.
 * 
 * @Example
 *  
 * +---+---+---+---+---+---+---+---+---+
 * | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 |
 * +---+---+---+---+---+---+---+---+---+
 *            
 *            
 *           bit format of 97
 * +---+---+---+---+---+---+---+---+---+
 * | 0 | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 1 |   integer: 97
 * +---+---+---+---+---+---+---+---+---+ 
 * 
 * The integer 97 with the bit format indicates that number 1, 6, and 7 has been used.
 * 
 */


/* (description): Calls the read function to get the sudoku puzzle. Then it 
 *                initializes the number used for rows, columns, and boxes.
 *                Finally, it compute the possible numbers for each blank grid
 *                by doing the bitwise opeartion.
 *
 * (inputs): A boolean value indicates if it is a difficult mode
 *
 * (outputs): The function will return a pointer to sudoku with all data initialized.
 *
 * (support): 
 */
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