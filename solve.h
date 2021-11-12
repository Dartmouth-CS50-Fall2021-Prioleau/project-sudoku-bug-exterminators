#ifndef SOLVE_H
#define SOLVE_H
/* Alan Sun, Arden Guo
 * CS50, Fall 2021, Sudoku Project
 * Header for sudoku solver (solve.h)
 *
 * This file contains functions that solves a given sudoku board.
 */

#include<stdbool.h>
#include "board.h"

bool solve_board(sudoku_t *board);
int is_unique(sudoku_t *puzzle);
void set_square(sudoku_t *, box_t *, int num, int i, int j);
void unset_square(sudoku_t *, box_t *, int num, int i, int j);




#endif
