#include<stdio.h>
#include<math.h>
#include "board.h"
#include "display.h"

/* Alan Sun, Arden Guo
 * CS50, Fall 2021, Sudoku Project
 * Display sudoku board (display.c)
 *
 * This module contains code that is able to display a sudoku board in both 
 * formatted and unformatted layouts. For formatted layouts, boards will
 * be displayed with explicit box and grid outlines and empty boxes will
 * be represented using `.`s. An example of this is shown below.
 *
 * 	+-------+-------+-------+
 * 	| 9 . . | . . . | . . 1 |
 *  | . . . | . . 2 | . . . |
 *  | . . . | . . 3 | . . . |
 *  +-------+-------+-------+
 *  | 8 . . | 4 . . | . . 3 |
 *  | 2 . . | . . . | . . . |
 *  | . . 1 | . . . | . 4 . |
 *  +-------+-------+-------+
 *  | . . 4 | 5 . 6 | 3 . . |
 *  | . . . | . . . | . . . | 
 *  | 6 1 . | . 2 . | 5 9 7 |
 *  +-------+-------+-------+
 * 
 * On the other hand, unformatted sudoku boards will be presented in simple
 * numeric representation, where 0s represent the empty boxes. An example
 * is shown below.
 *
 * 0 0 3 0 2 0 6 0 0
 * 9 0 0 3 0 5 0 0 1
 * 0 0 1 8 0 6 4 0 0
 * 0 0 8 1 0 2 9 0 0
 * 7 0 0 0 0 0 0 0 8
 * 0 0 6 7 0 8 2 0 0
 * 0 0 2 6 0 9 5 0 0
 * 8 0 0 2 0 3 0 0 9
 * 0 0 5 0 1 0 3 0 0
 *
 */

/* (description): Prints out the stylized border that is seen in the pretty
 * print of the formatted sudoku.
 *
 * +-------+-------+-------+
 *
 * (inputs): The dimension of the board. From this, we deduce that the size
 * of the box must be the squart root of this dimension. Moreover, we note
 * that this dimension must be a perfect square.
 *
 * (outputs): The function will not return anything; however, the function
 * will print to `stdout` the formatted border.
 *
 */
static void pborder(int dim)
{
  // Loop through the boxes.
  int dash = dim == 16 ? 13 : 7;
  for (int i = 0; i < sqrt(dim); i++) {
    printf("+");
    for (int j = 0; j < dash; j++) {
      printf("-");
    }
  }
  printf("+");
  printf("\n");
}

/* (description): Prints out a sudoku puzzle that follows the pretty format.
 * The exact syntax of this format is described and shown above.
 *
 * (inputs): A sudoku struct, this must be non-NULL. If a given puzzle has
 * a non-NULL board it must be that this board is a fully-initialized board
 * according to the dimensions given in `sudoku->dim`.
 *
 * (outputs): The function will not return anything; however, the function will
 * print to `stdout` the formatted puzzle.
 *
 * (error handling): Returns nothing when the given is NULL.
 *
 */
void display(sudoku_t *puzzle)
{
  int box_size;

  if (puzzle == NULL || puzzle->board == NULL)
    return;

  box_size = sqrt(puzzle->dim);
  
  for (int i = 0; i < puzzle->dim; i++) {
    // If the row represents the first "box" row, then we print out the 
    // division of the boxes.
    if (i % (int) sqrt(puzzle->dim) == 0) {
      pborder(puzzle->dim);
    }
    printf("| ");
    for (int j = 0; j < puzzle->dim; j++) {
      // If a number exists at the current square, then we print that number.
      if (puzzle->board[i][j]->num != 0) {
        if (puzzle->dim == 16)
          printf("%2d", puzzle->board[i][j]->num); 
        else
          printf("%d", puzzle->board[i][j]->num); 
      // Otherwise, we print the place holder: the . character.
      } else  {
        if (puzzle->dim == 16)
          printf(" .");
        else 
          printf(".");
      }
      // Format boxes with the pipe character.
      if ((j + 1) % box_size == 0)
        printf(" | ");
      else
        printf(" ");
    }
    printf("\n");
  } 
  pborder(puzzle->dim);
}

/* (description): Prints out a sudoku puzzle that follows a simple format. 
 * The exact syntax of this format is described and shown above.
 *
 * (inputs): A sudoku struct, this must be non-NULL. If a given puzzle has
 * a non-NULL board it must be that this board is a fully-initialized board
 * according to the dimensions given in `sudoku->dim`. 
 *
 * (outputs): The function will not return anything; however, the function 
 * will print to `stdout` the formatted puzzle.
 *
 * (error handling): Returns nothing when the given is NULL.
 *
 */
void sdisplay(sudoku_t *puzzle)
{
  if (puzzle == NULL || puzzle->board == NULL)
    return;

  for (int i = 0; i < puzzle->dim; i++) {
    for (int j = 0; j < puzzle->dim; j++) {
      printf("%d ", puzzle->board[i][j]->num);
    }
    printf("\n");
  }
}


/**************************************************************************
 **************************************************************************
 **************************************************************************
 *                              Unit Tests
 **************************************************************************
 **************************************************************************
 **************************************************************************
 */
#ifdef UNIT_TEST
#include<stdlib.h>
#define SIZE 16 

void test_invalids_simple(void);
void test_invalids_pretty(void);
void test_simple_simple(void);
void test_simple_pretty(void);

int main(void)
{
  // Expect to print nothing.
  test_invalids_simple();
  // Expect to print nothing.
  test_invalids_pretty();
  for (int i = 0; i < 9; i++) {
  test_simple_simple();
  test_simple_pretty();
  }
}

// Test printing null board. Should print nothing.
void test_invalids_simple(void)
{
  sudoku_t *s = malloc(sizeof(sudoku_t *));
  s->board = NULL;
  sdisplay(NULL);
  sdisplay(s);
  free(s);
}

// Test printing null board. Should print nothing.
void test_invalids_pretty(void)
{
  sudoku_t *s = malloc(sizeof(sudoku_t *));
  s->board = NULL;
  display(NULL);
  display(s);
  free(s);
}

// Test printing random board in a simple format.
void test_simple_simple(void)
{
  sudoku_t *s = malloc(sizeof(sudoku_t));
  s->board = calloc(SIZE, sizeof(box_t **));
  s->dim = SIZE;
  for (int i = 0; i < SIZE; i++) {
    s->board[i] = calloc(SIZE, sizeof(box_t *));
    for (int j = 0; j < SIZE; j++) {
      s->board[i][j] = malloc(sizeof(box_t));
      s->board[i][j]->num = rand() % (SIZE + 1); 
    }
  }
  sdisplay(s);
  for (int i = 0; i < SIZE; i++) { 
    for (int j = 0; j < SIZE; j++)
      free(s->board[i][j]);
    free(s->board[i]);
  }
  free(s->board);
  free(s);
}

// Test printing random board in a pretty format.
void test_simple_pretty(void)
{
  sudoku_t *s = malloc(sizeof(sudoku_t));
  s->board = calloc(SIZE, sizeof(box_t **));
  s->dim = SIZE;
  for (int i = 0; i < SIZE; i++) {
    s->board[i] = calloc(SIZE, sizeof(box_t *));
    for (int j = 0; j < SIZE; j++) {
      s->board[i][j] = malloc(sizeof(box_t));
      s->board[i][j]->num = rand() % (SIZE + 1); 
    }
  }
  display(s);
  for (int i = 0; i < SIZE; i++) { 
    for (int j = 0; j < SIZE; j++)
      free(s->board[i][j]);
    free(s->board[i]);
  }
  free(s->board);
  free(s);
}

#endif

