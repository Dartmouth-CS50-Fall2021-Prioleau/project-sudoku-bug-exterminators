#include<stdlib.h>
#include<stdio.h>
#include "board.h"
#include "solve.h"

/* Alan Sun, Arden Guo
 * CS50, Fall 2021, Sudoku Project
 * Sudoku solver module (solve.c)
 *
 * This module contains functions that are able to solv a given sudoku board.
 */

static bool find_possible(sudoku_t *puzzle, box_t *square, 
                int row, int col, int box); 

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
  box_t *square;
  int dim;

  if (puzzle == NULL || puzzle->board == NULL)
    return false;

  dim = puzzle->dim; 
  for (int i = dim - 1; i >= 0; i--) {
    for (int j = dim - 1; j >= 0; j--) {
      // Check if the box has a number, if so move on.
      square = puzzle->board[i][j];
      if (square->num == 0) {
        if (!find_possible(puzzle, square, i, j, (i % dim) + (j % dim)))
          return false;
        // Loop through all possibilites, and try them.
        for (int k = 0; k < dim; k++) {
          if ((square->possible & (1 << k)) != 0) {
            square->num = k + 1;
            puzzle->rows[i] &= ~(1 << k);
            puzzle->columns[j] &= ~(1 << k);
            puzzle->boxes[(i % dim) + (j % dim)] &= ~(1 << k);
            if (solve_board(puzzle))
              return true;
          }
        }
        
      }
    }
  }
  return true;
}

/* (description): The `find_possbile` function finds the possibilities of a
 * given square. It will "output" the results by modifying in place the 
 * possibilites of the box.
 *
 * (inputs): A pointer to a box struct that represents a square on the board.
 * A row representing the index of the row; a column representing the index
 * of the column, and a box index representing the index of the box the 
 * square is in. As well as a pointer to the entire puzzle.
 *
 * (output): The function will output false if no possibilites were found and
 * true if there are possibilities for the current square.
 */
static bool find_possible(sudoku_t *puzzle, box_t *square, 
                int row, int col, int box)
{
  if (puzzle == NULL || square == NULL) {
    return false;
  }
  square->possible = ~(puzzle->rows[row] | puzzle->columns[col] | 
                          puzzle->boxes[box]);
  return square->possible != 0;
}

/***************************************************************************
 ***************************************************************************
 ***************************************************************************
 *                              Unit Tests
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 */
#ifdef UNIT_TEST
#include<stdio.h>
#include<stdlib.h>
#include "display.h"
#include "assert.h"

static void test_invalid_puzzle(void);
static void test_solved_puzzle(void);
static void test_one_empty(void);
static void test_simple_puzzle(void);
static void test_hard_puzzle(void);

int main(void)
{
  test_invalid_puzzle();
  test_solved_puzzle();
  test_one_empty();
  test_simple_puzzle();
  test_hard_puzzle();
}

static void test_invalid_puzzle(void)
{
  sudoku_t *board;

  assert(!solve_board(NULL)); 
  board = malloc(sizeof(sudoku_t));
  board->board = NULL;
  assert(!solve_board(board));
  free(board);
} 

static void test_solved_puzzle(void)
{
  int arr[9][9] = {
    {4, 3, 5, 2, 6, 9, 7, 8, 1},
    {6, 8, 2, 5, 7, 1, 4, 9, 3},
    {1, 9, 7, 8, 3, 4, 5, 6, 2},
    {8, 2, 6, 1, 9, 5, 3, 4, 7},
    {3, 7, 4, 6, 8, 2, 9, 1, 5},
    {9, 5, 1, 7, 4, 3, 6, 2, 8},
    {5, 1, 9, 3, 2, 6, 8, 7, 4},
    {2, 4, 8, 9, 5, 7, 1, 3, 6},
    {7, 6, 3, 4, 1, 8, 2, 5, 9}
  };

  sudoku_t *board = malloc(sizeof(sudoku_t));
  board->dim = 9;
  board->board = calloc(9, sizeof(box_t *));
  for (int i = 0; i < 9; i++) {
    board->board[i] = calloc(9, sizeof(box_t *));
    for (int j = 0; j < 9; j++) {
      board->board[i][j] = malloc(sizeof(box_t));
      board->board[i][j]->num = arr[i][j];
    }
  }
  assert(solve_board(board));
  display(board);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++)
      free(board->board[i][j]);
    free(board->board[i]);
  }
  free(board->board);
  free(board);
}

static void test_one_empty(void)
{
  int arr[9][9] = {
    {4, 3, 0, 2, 6, 9, 7, 8, 1},
    {6, 8, 2, 5, 7, 1, 4, 9, 3},
    {1, 9, 7, 8, 3, 4, 5, 6, 2},
    {8, 2, 6, 1, 9, 5, 3, 4, 7},
    {3, 7, 4, 6, 8, 2, 9, 1, 5},
    {9, 5, 1, 7, 4, 3, 6, 2, 8},
    {5, 1, 9, 3, 2, 6, 8, 7, 4},
    {2, 4, 8, 9, 5, 7, 1, 3, 6},
    {7, 6, 3, 4, 1, 8, 2, 5, 9}
  };

  sudoku_t *board = malloc(sizeof(sudoku_t));
  board->rows = calloc(9, sizeof(int));
  board->columns = calloc(9, sizeof(int));
  board->boxes = calloc(9, sizeof(int));
  board->rows[0] = ~(1 << 4);
  board->boxes[0] = ~(1 << 4);
  board->columns[1] = ~(1 << 4);
  board->dim = 9;
  board->board = calloc(9, sizeof(box_t *));
  for (int i = 0; i < 9; i++) {
    board->board[i] = calloc(9, sizeof(box_t *));
    for (int j = 0; j < 9; j++) {
      board->board[i][j] = malloc(sizeof(box_t));
      board->board[i][j]->num = arr[i][j];
      if (i == 0 && j == 2)
        board->board[i][j]->possible = 1 << 4;
    }
  }
  assert(solve_board(board));
  display(board);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++)
      free(board->board[i][j]);
    free(board->board[i]);
  }
  free(board->rows), free(board->columns), free(board->boxes);
  free(board->board);
  free(board);
}

static void test_simple_puzzle(void)
{
  int arr[9][9] = {

  }

}

static void test_hard_puzzle(void)
{


}

#endif
