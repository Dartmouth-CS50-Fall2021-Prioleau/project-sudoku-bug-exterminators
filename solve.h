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


bool solve_board(sudoku_t *board, bool check_unique);


#endif
