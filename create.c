#include<math.h>
#include<stdlib.h>
#include<time.h>
#include "board.h"
#include "solve.h"
#include "create.h"
#include "read.h"
/* Alan Sun, Arden Guo
 * CS50, Fall 2021, Sudoku Project
 * Create sudoku (create.c)
 *
 * This file contains functions that helps to create a random sudoku puzzle.
 */

static sudoku_t *empty(int dim);

sudoku_t *create(bool difficult, int dim)
{
  sudoku_t *puzzle = empty(dim);
  int *nums = calloc(dim * dim, sizeof(int));
  int a, b, temp;

  solve_board(puzzle);
  // Remove numbers from the solved sudoku board.
  for (int i = 0; i < dim * dim; i++)
    nums[i] = i;
  // Randomly shuffle this index array.
  for (int i = 0; i < dim * dim; i++) {
    a = rand() % (dim * dim);
    b = rand() % (dim * dim);
    temp = nums[a];
    nums[a] = nums[b];
    nums[b] = temp;
  }

  // Index map from the ordinal numbers to coordinates that are 
  // to be removed from the solved sudoku board.
  for (int i = 0; i < (difficult ? 56 : 44); i++) {
    temp = nums[i];
    puzzle->board[temp / 9][temp % 9]->num = 0;
  }
  free(nums);
  return puzzle;
}

static sudoku_t *empty(int dim)
{
  sudoku_t *puzzle = malloc(sizeof(sudoku_t));
  puzzle->dim = dim;
  puzzle->rows = calloc(dim, sizeof(int));
  puzzle->columns = calloc(dim, sizeof(int));
  puzzle->boxes = calloc(dim, sizeof(int));
  puzzle->board = calloc(dim, sizeof(box_t **));
  
  for (int i = 0; i < dim; i++) {
    puzzle->board[i] = calloc(dim, sizeof(box_t *));
    for (int j = 0; j < dim; j++) {
      puzzle->board[i][j] = malloc(sizeof(box_t)); 
      puzzle->board[i][j]->num = 0;
      puzzle->board[i][j]->possible = pow(2, dim) - 1; 
    }
  }
  return puzzle;
}

/************************************************************************
 ************************************************************************
 ************************************************************************
 *                               Unit Tests
 ************************************************************************
 ************************************************************************
 ************************************************************************
 */
#ifdef UNIT_TEST
#include "display.h"

void test_simple(void);
void test_hard(void);

int main(void)
{ 
  // Generate 3 simple sudoku.
  for (int i = 0; i < 3; i++) {
    test_simple();
  }
  // Generate 3 hard sudoku.
  for (int i = 0; i < 3; i++) {
    test_hard();
  }
}

void test_simple(void)
{
  sudoku_t *puzzle = create(false, 9);
  display(puzzle);
  delete_sudoku(puzzle);
}

void test_hard(void)
{
  sudoku_t *puzzle = create(true, 9);
  display(puzzle);
  delete_sudoku(puzzle);
}
#endif
