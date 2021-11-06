#include "read.h"
#include "display.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


/* Alan Sun, Arden Guo
 * CS50, Fall 2021, Sudoku Project
 * Read from Stdin (read.c)
 * This module contains a read function that reads a sudoku puzzle
 * from stdin, extracts and stores the numbers in the sudoku data 
 * structure.
 * 
 * The read function support both simple sudoku and pretty sudoku.
 * In the case of pretty sudoku, the read function saves the dot . as 0
 * in the board for further processing.
 */

/* (description): Reads a sudoku puzzle from stdin, 
 *                extracts and stores the numbers in 
 *                the sudoku data structure.
 *
 * (inputs): A boolean value indicates if it is a difficult mode
 *
 * (outputs): The function will return a pointer to sudoku.
 * 
 * (Support): Right now, the read function supports two-digit numbers as well
 * 
 * (TODO):  Before exiting for each case, need to free the momery.
 *
 */

sudoku_t *read(bool difficult)
{
    // create sudoku
    sudoku_t* sudoku = malloc(sizeof(sudoku_t));
    if(sudoku == NULL){
        fprintf(stderr, "Failed to malloc for sudoku.\n");
        exit(2);
    }

    // dim information
    int dim = difficult ? 16 : 9;
    sudoku->dim = dim;

    // create board
    box_t ***board = malloc(sizeof(box_t**) * dim);
    if(board == NULL){
        fprintf(stderr, "Failed to malloc for board.\n");
        exit(2);
    }
    for(int i=0 ;i<dim; i++){
        board[i] = malloc(sizeof(box_t*)*dim);
        if(board[i] == NULL){
            fprintf(stderr, "Failed to malloc for board row.\n");
            exit(2);
        }
    }
    sudoku->board = board;


    // read from stdin
    char c;
    int c_number;
    int row = 0;
    int col = 0;
    int num_ttl = 0;
    int num_given = 0;

    while((c = getchar()) != EOF){
        if(isdigit(c) || c == '.'){
            // increase num_ttl
            num_ttl++;
            if(c != '.' && c != '0'){
                num_given++;
            }

            if(num_ttl > dim * dim){
                fprintf(stderr, "Input number of numbers exceeds the required amount.\n");
                exit(3);
            }    

            // '.' is specific to our design of blank grid
            c_number = c == '.' ? 0 : c - '0';
            
            // for the two-digit number
            if((c = getchar()) != EOF && isdigit(c)){
                int current = c - '0';
                c_number = c_number* 10 + current;
            }


            // create the grid
            board[row][col] = malloc(sizeof(box_t));
            if(board[row][col] == NULL){
                fprintf(stderr, "Failed to malloc for board grid.\n");
                exit(2);
            }

            // set the number 
            (board[row][col])->num = c_number;

            // set the index for the next input
            col++;
            if(col >= dim){
                row++;
                col = 0;
            }
        }
    }

    // checking the input number
    /*
    if(!difficult && num_given != 37){
        fprintf(stderr, "37 numbers should be provided for easy mode. You gave %d numbers. \n", num_ttl);
        exit(4);
    }

    if(difficult && num_given != 25){
        fprintf(stderr, "25 numbers should be provided for easy mode. You gave %d numbers. \n", num_ttl);
        exit(4);
    }*/

    return sudoku;
}

int main(){
    sudoku_t* puzzle = read(false);
    display(puzzle);
}
