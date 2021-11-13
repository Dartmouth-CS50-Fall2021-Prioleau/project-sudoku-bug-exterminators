#include<stdlib.h> 
#include<stdio.h>
#include<math.h>
#include "board.h"
#include "display.h"
#include "solve.h"
#include "read.h"

/* Alan Sun, Arden Guo
 * CS50, Fall 2021, Sudoku Project
 * Sudoku solver module (solve.c)
 *
 * This module contains functions that are able to solv a given sudoku board.
 */

static bool find_possible(sudoku_t *puzzle, box_t *square, 
                int row, int col, int box); 

static int *possible_number(int number, int dim, bool random); 

box_t*** blank_grids(sudoku_t* puzzle);

int num_of_possible(box_t* square, sudoku_t* puzzle, int row, int col, int box);

void delete_blank_box(box_t*** blank_box, int dim);

void set_square(sudoku_t *, box_t *, int num, int i, int j);
void unset_square(sudoku_t *, box_t *, int num, int i, int j);


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
bool solve_board(sudoku_t *puzzle, bool random)
{
  box_t *square;
  int dim, *possible, count = 0;
  bool flag;

  if (puzzle == NULL || puzzle->board == NULL)
    return false;

  dim = puzzle->dim; 
  for (int i = dim - 1; i >= 0; i--) {
    for (int j = dim - 1; j >= 0; j--) {
      // Check if the box has a number, if so move on.
      square = puzzle->board[i][j];
      if (square->num == 0) {
        if (!find_possible(puzzle, square, i, j, box_index(i, j, dim))) {
          return false;
        }
        // Loop through all possibilites, and try them.
        possible = possible_number(square->possible, dim, random); 
        while (possible[count++] != -1) {
          set_square(puzzle, square, possible[count - 1], i, j);
          flag = solve_board(puzzle, false);
          if (!flag)
            unset_square(puzzle, square, possible[count - 1], i, j);
          else {
            break;
          }
        }
        free(possible);
        return square->num != 0;
      }
    }
  }
  return true;
}

int is_unique(sudoku_t *puzzle)
{
  box_t *square;
  int dim, *possible, count = 0, sols = 0;
  int flag;

  if (puzzle == NULL || puzzle->board == NULL)
    return false;

  dim = puzzle->dim; 
  for (int i = dim - 1; i >= 0; i--) {
    for (int j = dim - 1; j >= 0; j--) {
      // Check if the box has a number, if so move on.
      square = puzzle->board[i][j];
      if (square->num == 0) {
        if (!find_possible(puzzle, square, i, j, box_index(i, j, dim))) {
          return 0;
        }
        // Loop through all possibilites, and try them.
        possible = possible_number(square->possible, dim, false); 
        while (possible[count++] != -1) {
          set_square(puzzle, square, possible[count - 1], i, j);
          flag = is_unique(puzzle);
          sols += flag;
          unset_square(puzzle, square, possible[count - 1], i, j);
        }
        free(possible);
        return sols;
      }
    }
  }
  return 1;
}

void set_square(sudoku_t* puzzle, box_t *square, int num, int i, int j)
{
  square->num = num;
  puzzle->rows[i] |= 1 << (num - 1);
  puzzle->columns[j] |= 1 << (num - 1);
  puzzle->boxes[box_index(i, j, puzzle->dim)] |= 1 << (num - 1);
}

void unset_square(sudoku_t *puzzle, box_t *square, int num, int i, int j)
{
  square->num = 0;
  puzzle->rows[i] &= ~(1 << (num-1));
  puzzle->columns[j] &= ~(1 << (num-1));
  puzzle->boxes[box_index(i, j, puzzle->dim)] &= ~(1 << (num-1));
}


static int *possible_number(int number, int dim, bool random) {
  int num = 0, a, b, temp;
  int *numbers = calloc(dim + 1, sizeof(int));

  // Place numbers into array in order.
  for (int k = 0; k < dim; k++) {
    if ((number & (1 << k)) != 0) {
      numbers[num++] = k + 1; 
    }
  }
  numbers[num] = -1;

  if (!random)
    return numbers;

  // Randomize numbers.
  for (int i = 0; i < num; i++) {
    a = rand() % num;
    b = rand() % num;
    temp = numbers[a];
    numbers[a] = numbers[b];
    numbers[b] = temp;
  }
  return numbers;
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
  square->possible &= (int) pow(2, puzzle->dim) - 1;
  return square->possible != 0;
}

/*
 * (description): The `blank_grids` function loops through the puzzle and 
 * store the blank grids into a new 2D array.
 *
 * (input): A sudoku puzzle contains the board is passed in.
 * 
 * (output): A 2D array with row index i indicating there are i+1 pissibilities 
 * for the grids stored in this row. 
 */
box_t*** blank_grids(sudoku_t* puzzle)
{
  // get dimmension
  int dim = puzzle->dim;
  //printf("Initializing blank grids data structures ... \n"); 
  // initialize the data structures
  box_t*** blank_box = malloc(dim * sizeof(box_t**));
  if(blank_box == NULL){
    fprintf(stderr, "Failed to malloc for array\n");
    // delete before exiting
    delete_sudoku(puzzle);
    exit(2);
  }
 
  for(int i=0; i<dim; i++){
    blank_box[i] = calloc(dim*dim, sizeof(box_t*));
    if(blank_box[i] == NULL){
      //fprintf(stderr, "Failed to malloc for array\n");
      //delete the blank box 
      delete_blank_box(blank_box, dim);
      
      // delete before exiting
      delete_sudoku(puzzle);
      
      exit(2);
    }
  }
  //printf("initialize index ...\n");
  // index to store the box_t*
  int index[dim];
  for(int i=0; i<dim; i++){
    index[i] = 0;
  }
  
  //int ttl = 0;
  //printf("Loop through the puzzle to store the blank grids ... \n");

  for(int i=0; i<dim; i++){
    for(int j=0; j<dim; j++){
      //printf("i and j = %d, %d\n", i, j);
      box_t* current_box = puzzle->board[i][j];
      if(current_box->num == 0){
        //ttl++;
	//printf("find a blank grid\n");
        // calculate the number of possibilities for this grid
        int count = num_of_possible(current_box, puzzle, i, j, box_index(i,j,dim));
        //printf("%d , ", count);
        // insert the current box to the right place
        blank_box[count - 1][(index[count - 1])++] = current_box;
      }
    }
  }

  //printf("\nThere is a total of %d blank grids\n", ttl);
  return blank_box;
}

/*
 * (description): The `num_of_possible` function calculates the number of possiblities
 * for a grid.
 *
 * (input): square - the grid 
 *	    puzzle - the sudoku puzzle
 *	    row - the row index of the grid
 *	    col - the column index of the grid
 * 	    box - the box index of the grid
 *
 * (output): The numebr of possibilities for the grid.
 */
int num_of_possible(box_t* square, sudoku_t* puzzle, int row, int col, int box)
{
  //printf("Get the number of possible numbers ... \n");
  // get the possible number
  square->possible = ~(puzzle->rows[row] | puzzle->columns[col] | 
                          puzzle->boxes[box]);
  square->possible &= (int) pow(2, puzzle->dim) - 1;
  //printf("binary format is %s\n",binary_format(square->possible, 9));
  // count the number of 1s in the possible
  int count = 0;
  int dim = puzzle->dim;
  for (int k = 0; k < dim; k++) {
    if ((square->possible & (1 << k)) != 0) {
      count++;
    }
  }

  return count;
}

/*
 * (description): The function `delete_blank_box` frees the memory allocated
 * by the blank_grid function.
 * 
 * (input): blank_box - the 2D array allocated by the dynamic memory allocator
 *  	    dim - the dimmension size of the sudoku puzzle
 */
void delete_blank_box(box_t*** blank_box, int dim)
{
  for(int i=0; i <dim; i++){
    if(blank_box[i] != NULL){
      free(blank_box[i]);
    }
  }

  free(blank_box);
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
#include<unistd.h>
#include<stdlib.h>
#include "display.h"
#include "assert.h"
#include<fcntl.h>
#include "read.h"

static void test_unique_simple(void);
static void test_invalid_puzzle(void);
static void test_solved_puzzle(void);
static void test_one_empty(void);
static void test_simple_puzzle(void);
static void test_hard_puzzle1();
static void test_unique_hard1(void);
static void test_unique_hard2(void);
static void test_unique_hard3(void);

int main(void)
{
  test_unique_simple();
  test_unique_hard1();
  test_unique_hard2();
  test_unique_hard3();
  test_invalid_puzzle();
  test_solved_puzzle();
  test_one_empty();
  test_simple_puzzle();
  test_hard_puzzle1();
}

static void test_unique_simple(void)
{
  // Non-unique board.
  int fd = open("tests/p5", O_RDONLY);
  sudoku_t *board;

  printf("Test Unique Simple.\n");
  dup2(fd, STDIN_FILENO);
  board = read_sudoku(true);
  assert(is_unique(board) > 1);
  delete_sudoku(board);
}

static void test_unique_hard1(void)
{
  // Non-unqiue board.
  int fd = open("tests/p6", O_RDONLY);
  sudoku_t *board;
  
  printf("Test Unique Hard 1.\n");
  dup2(fd, STDIN_FILENO);
  board = read_sudoku(true);
  assert(is_unique(board) > 1);
  delete_sudoku(board);
}

static void test_unique_hard2(void)
{
  int fd = open("tests/p1", O_RDONLY);
  sudoku_t *board;

  printf("Test Unique Hard 2\n");
  dup2(fd, STDIN_FILENO);
  board = read_sudoku(true);
  assert(is_unique(board) == 1);
  delete_sudoku(board);
}

static void test_unique_hard3(void)
{
  int fd = open("tests/p7", O_RDONLY);
  sudoku_t *board;

  printf("Test Unique Hard 3\n");
  dup2(fd, STDIN_FILENO);
  board = read_sudoku(true);
  assert(is_unique(board) > 1);
  delete_sudoku(board);
}

static void test_invalid_puzzle(void)
{
  sudoku_t *board;

  assert(!solve_board(NULL, false)); 
  board = malloc(sizeof(sudoku_t));
  board->board = NULL;
  assert(!solve_board(board, false));
  free(board);
  
  // Test boards that have no solution.
  int fd = open("tests/p4", O_RDONLY);
  dup2(fd, STDIN_FILENO);
  board = read_sudoku(true);
  assert(!solve_board(board, false));
  delete_sudoku(board);
  
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
  assert(solve_board(board, false));
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
  assert(solve_board(board, false));
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
  int fd = open("tests/p1", O_RDONLY);

  dup2(fd, STDIN_FILENO);
  sudoku_t *board = read_sudoku(false);
  printf("Given board:\n");
  display(board);
  assert(solve_board(board, false));
  printf("Solved board:\n");
  display(board);
  delete_sudoku(board);
}

static void test_hard_puzzle1(void)
{
  int fd = open("tests/p2", O_RDONLY);

  dup2(fd, STDIN_FILENO);
  sudoku_t *board = read_sudoku(false);
  printf("Given board:\n");
  display(board);
  assert(solve_board(board, false));
  printf("Solved board:\n");
  display(board);
  delete_sudoku(board);
}
#endif
