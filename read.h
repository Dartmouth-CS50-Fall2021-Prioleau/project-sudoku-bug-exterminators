/* Alan Sun, Arden Guo
 * CS50, Fall 2021, Sudoku Solver Project
 * Read Sudoku (read.h)
 *
 * Function prototypes for module that reads a given sudoku board.
 */

#ifndef READ_H
#define READ_H

#include "board.h"
#include <stdbool.h>

/*************** Function prototypes *****************/
// please see the description above each function in read.c

sudoku_t *read_sudoku(bool difficult);
sudoku_t *sudoku_ini(bool difficulty, sudoku_t* sudoku);
int* array_create(int dim, sudoku_t* sudoku);
int box_index(int row, int col, int dim);
void delete_sudoku(sudoku_t* sudoku);
char* binary_format(int n, int len);

#endif
