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

bool solve_board(sudoku_t *board, bool random);
int is_unique(sudoku_t *puzzle);
int is_unique_quick(sudoku_t *puzzle, box_t ***blanks);
box_t ***blank_grids(sudoku_t *puzzle);
void set_square(sudoku_t *, box_t *, int num, int i, int j);
void unset_square(sudoku_t *, box_t *, int num, int i, int j);
void delete_blank_box(box_t ***blank_box, int dim);



#endif
