#ifndef BOARD_H
#define BOARD_H
/* Alan Sun, Arden Guo
 * CS50, Fall 2021, Sudoku Solver Project
 * Structs for Sudoku (board.h)
 *
 * This file contains two data structures: one represents the struct for 
 * each box, and the other represents the entire sudoku board.
 */

typedef struct box {
  int num;
  int *possible;
} box_t;

typedef struct sudoku {
  box_t ***board;
  int **rows;
  int **columns
  int **boxes;
  int dim;
} sudoku_t;
#endif
