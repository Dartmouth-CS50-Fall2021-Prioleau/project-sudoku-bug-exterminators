#include<math.h>
#include<stdlib.h>
#include<time.h>
#include "board.h"
#include "solve.h"
#include "create.h"
#include "read.h"
#include<stdbool.h>
#include<sys/time.h>
#include<time.h>
/* Alan Sun, Arden Guo
 * CS50, Fall 2021, Sudoku Project
 * Create sudoku (create.c)
 *
 * This file contains functions that helps to create a random sudoku puzzle.
 */

static sudoku_t *empty(int dim);
static bool pluck(sudoku_t *puzzle, int *coor, bool difficulty);
static int *random_remove(int dim);

sudoku_t *create(bool difficult, int dim)
{ 
  struct timeval current_time;
  gettimeofday(&current_time, NULL);
  srand(current_time.tv_usec);
  sudoku_t *puzzle = empty(dim);
  int *nums;

  solve_board(puzzle, true);
  nums = random_remove(dim);

  // Index map from the ordinal numbers to coordinates that are 
  // to be removed from the solved sudoku board.
  while (!pluck(puzzle, nums, difficult)) {
    puzzle = empty(dim);
    nums = random_remove(dim);
  }
  free(nums);
  return puzzle;
}

static int *random_remove(int dim)
{
  int *nums = calloc(dim * dim, sizeof(int));
  int a, b, temp;
  
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
  return nums;
}

static bool pluck(sudoku_t *puzzle, int *coor, bool difficulty)
{
  int temp, num, cols, rows;
  box_t *square;
  int count = 0;
  int total = puzzle->dim * puzzle->dim;
  int removed = difficulty ? 56 : 44;

  for (int i = 0; count < removed; i++) {
    if (i >= 81 || (total - i < removed - count))
      return false;
    temp = coor[i];
    rows = temp / 9;
    cols = temp % 9;
    square = puzzle->board[rows][cols];
    num = square->num;
    // Set the possibilities to pre-set unique checking.
    unset_square(puzzle, square, num, rows, cols);
    // Check if board stil lhas unique solution.
    if (is_unique(puzzle) == 1)
      count++;
    else {
      set_square(puzzle, square, num, rows, cols);
    } 
  }
  return true;
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
#include<stdio.h>

void test_simple(void);
void test_hard(void);

int main(void)
{ 
  // Generate 3 simple sudoku.
  for (int i = 0; i < 3; i++) {
    printf("Simple Puzzle:\n");
    test_simple();
  }
  // Generate 3 hard sudoku.
  for (int i = 0; i < 3; i++) {
    printf("Hard Puzzle:\n");
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
