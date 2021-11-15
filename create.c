#include<math.h>
#include<stdlib.h>
#include<time.h>
#include "board.h"
#include "solve.h"
#include "display.h"
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
 * To create a random sudoku puzzle, the functions in thie module first 
 * initialize an empty board, solve that empty board using random backtracking
 * such that solving this empty board over and over again will result in a 
 * random fully-solved board. Then, our functions will proceed to pluck numbers
 * off the board, each time checking if the number that we just plucked is
 * unique. If it is, then we continue. Otherwise, we pluck off a different 
 * number until we reach the number of givens that is appropriate for the
 * given level of difficulty.
 */

static sudoku_t *empty(int dim);
static bool pluck(sudoku_t *puzzle, int *coor, bool difficulty);
static int *random_remove(int dim);

/* (description): The `create` function creates a sudoku puzzle, given the 
 * dimensions of the puzzle, and the difficulty of the puzzle. It will
 * return a puzzle that is well initialized : not only the values of its
 * squares are initalized appropriately, but also the possible values for each
 * column, row, and box.
 *
 * (inputs): The difficulty: true represents a hard puzzle (56 removed, 25
 * givens), false represents an easy puzzle (44 removed, 37 givens). `dim`
 * represents the number of dimensions of the given sudoku board.
 *
 * (outputs): The function will return a dynamically allocated sudoku board
 * whose square values should adhere to the rules of sudoku and should
 * only have a unique solution. The user should later free this output by 
 * calling `delete_sudoku`.
 *
 * (error handling): If at any point, the function or its helpers fail to 
 * allocate function, the function itself may terminate. This is undefined
 * behavior and should be noted by the user.
 *
 */
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
    solve_board(puzzle, true);
    nums = random_remove(dim);
  }
  free(nums);
  return puzzle;
}

/* (description): A helper function that generates a list of randomly ordered
 * numbers in the range [0, dim * dim). Lists generated from this function
 * are dynamically allocated and can be directly used to input into the `coor`
 * argument of pluck. 
 *
 * (inputs): The dimension of the sudoku board.
 *
 * (outputs): A dynamically allocated list that includes numbers in random
 * order from 0 -> dim * dim. For example if dim = 3, then these following
 * lists could appear:
 *
 *      - [0, 1, 2, 3, 4, 5, 6, 7, 8]
 *      - [7, 4, 5, 1, 2, 3, 6, 8, 0]
 *      - [8, 7, 6, 5, 4, 3, 2, 1, 0]
 *
 * (error handling): If `dim` is 0 or negative, NULL is returned. Or if memory
 * allocation fails, then NULL is returned.
 */
static int *random_remove(int dim)
{
  int *nums = calloc(dim * dim, sizeof(int));
  int a, b, temp;
  
  if (dim < 1 || nums == NULL)
    return NULL;
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

/* (description): `pluck` is a helper function that plucks numbers off of a
 * given solved board, such that the puzzle remains unique. It will continue
 * to pluck off numbers until the number of givens is appropriate for the 
 * requested difficulty level:
 *
 *    - Easy : 37 given => 44 removed from the solved board.
 *    - Hard : 25 given => 56 removed from the solved board.
 *
 * We note that if the OPTIMIZED flag is turned on, the pluck will try to pluck
 * in a more optimzied way: checking for uniqueness not in order, but in order
 * of most to least possible.
 *
 * (inputs): A given sudoku puzzle that is completely solved, `coor` which 
 * represents an array of unique integers in the range [0,81). This 
 * represents the order in which certain squares are to be removed from the
 * board. `difficulty` represents the level of difficulty the generated puzzle
 * must adhere to. If this argument is false, then an easy puzzle is generated.
 * Otherwise, a hard puzzle will be generated.
 *
 * (outputs): The function will output true, if it is able to pluck out numbers
 * in the sequence of `coor` that will result in a unique puzzle. If the given
 * puzzle does not have a unique solution, or if it cannot be solved, then the
 * function will output false.
 *
 * (error handling): We note here that `coor` needs to be an array of length 81
 * containing unique integers between [0, 81). If a valid array is not provided
 * this would result in undefined behavior.
 *
 */
static bool pluck(sudoku_t *puzzle, int *coor, bool difficulty)
{
  int temp, num, cols, rows;
  box_t *square;
  int count = 0;
  int flag;
  int total = puzzle->dim * puzzle->dim;
  int removed = difficulty ? 56 : 44;

  // Invalid arguments checking
  if (puzzle == NULL || coor == NULL)
    return false;

  for (int i = 0; count < removed; i++) {
    if (i >= 81 || (total - i < removed - count))
      return false;
    temp = coor[i];
    rows = temp / 9;
    cols = temp % 9;
    square = puzzle->board[rows][cols];
    num = square->num;
    // Removed the square to pre-set unique checking.
    unset_square(puzzle, square, num, rows, cols);
    // Check if board stil lhas unique solution.
#ifdef OPTIMIZED
    box_t ***blanks;
    if (removed < 35) {
      flag = is_unique(puzzle);
    } else {
      blanks = blank_grids(puzzle);
      flag = is_unique(puzzle, blanks);
      delete_blank_box(blanks, 9); 
    }
#endif
#ifndef OPTIMIZED
    if (count < 30) {
      count++;
      continue;
    }
    flag = is_unique(puzzle);
#endif
    if (flag == 1) {
      count++;
    } else {
      // If the removal of the square resulted in a non-unique solution
      // then we restore the square and try to removed a different one.
      set_square(puzzle, square, num, rows, cols);
    } 
  }
  return true;
}

/* (description): `empty` is a helper function that allocates for and creates 
 * a empty sudoku board. It sets the value of each square to 0, and initializes
 * the possibilities bit-string for each column, row, and box to 0.
 *
 * (inputs): `dim` the number of dimensions of the sudoku puzzle that needs to
 * be created.
 *
 * (outputs): A dynamically allocated sudoku board that is empty (all values 
 * are set to 0). This must be freed by the user later, by calling 
 * `delete_sudoku`. 
 *
 * (error handling): If at any point, memory cannot allocated, the function 
 * will return NULL, without freeing any memory that has already been allocated
 * successfully. If this edge case occurs, it is likely to result in memory leaks.
 */
static sudoku_t *empty(int dim)
{
  sudoku_t *puzzle = malloc(sizeof(sudoku_t));
  if (puzzle == NULL)
    return NULL;
  puzzle->dim = dim;
  puzzle->rows = calloc(dim, sizeof(int));
  puzzle->columns = calloc(dim, sizeof(int));
  puzzle->boxes = calloc(dim, sizeof(int));
  puzzle->board = calloc(dim, sizeof(box_t **));
  // Check for successful allocation.
  if (puzzle->rows == NULL || puzzle->columns == NULL || puzzle->boxes == NULL
                  || puzzle->board == NULL)
    return NULL;

  for (int i = 0; i < dim; i++) {
    puzzle->board[i] = calloc(dim, sizeof(box_t *));
    for (int j = 0; j < dim; j++) {
      puzzle->board[i][j] = malloc(sizeof(box_t)); 
      puzzle->board[i][j]->num = 0;
      // Since all cells are empty, all numbers are possible at each cell.
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
