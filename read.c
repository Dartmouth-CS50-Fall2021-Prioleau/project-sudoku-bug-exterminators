#include "read.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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
    int num_of_grid = dim * dim;
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

    while((c = getchar()) != EOF){
        if(isdigit(c) || c == '.'){
            // '.' is specific to our design of blank grid
            c_number = c == '.' ? 0 : c - '0';
            
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

    return sudoku;
}
