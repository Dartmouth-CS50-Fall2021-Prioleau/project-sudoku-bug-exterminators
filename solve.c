#include<stdlib.h>
#include<stdio.h>
#include "solve.h"

/* Alan Sun, Arden Guo
 * CS50, Fall 2021, Sudoku Project
 * Sudoku solver module (solve.c)
 *
 * This module contains functions that are able to solv a given sudoku board.
 */

/* (description): The `solve_board` function will sovle a given sudoku board, 
 * filling in the blanks with numbers that conform to the rules of sudoku.
 *
 * (inputs): A sudoku board that has already been initialized. It must contain
 * a board, such that each box in the board must have its possible values 
 * initialized as well as its target number. If a non-NULL sudoku pointer has 
 * been passed, the function will assume that theses parameters have been 
 * initialized. Otherwise, there will be undefined behavior.
 *
 * (outputs): True if the board can be solved, and false if not. The function
 * will modify the given sudoku board in place.
 *
 * (error handling): If the board given is not initialized appropriately 
 * then undefined behavior will occur.
 *
 */
bool solve_board(sudoku_t *puzzle)
{
  if (puzzle == NULL || puzzle->board == NULL)
    return false;
  return false;
}
