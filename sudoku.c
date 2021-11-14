/* 
 * CS50, Fall 2021, Sudoku Project
 *
 * @File: sudoku.c - The sudoku program can either create a puzzle with a difficulty
 *                   specified or solve a puzzle
 * 
 * @Usage: ./sudoku mode difficulty
 *         mode - either create or solve
 *         difficulty - either easy or hard (only required for create mode)
 * 
 * @Author: Alan Sun, Arden Guo
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "create.h"
#include "solve.h"
#include "board.h"
#include "read.h"
#include "display.h"

/*
 * main - takes in either 2 or 3 arguents, creates or solve a sudoku puzzle
 * 
 * @Usage: please refer to the header information  
 */
int main(const int argv, char* argc[]){
    // get the program
    char* program = argc[0];
    srand(time(NULL));
    // check the number of arguments
    if(argv != 3 && argv != 2){
        fprintf(stderr, "Usage: %s mode difficulty (difficulty is only required for create mode)\n", program);
        return 1;
    }

    // check mode
    char* mode = argc[1];
    if(strcmp(mode, "create") != 0 && strcmp(mode, "solve") != 0){
        fprintf(stderr, "Usage: %s mode difficulty (difficulty is only required for create mode), mode should be either \"create\" or \"solve\"\n", program);
        return 1;
    }


    // calling creator or solver
    int dim = 9;
    if(argv == 3){
        /************* calling creator **************/
        // check mode must be create
        if(strcmp(mode, "create") != 0){
        fprintf(stderr, "Usage: %s mode difficulty (difficulty is only required for create mode) \n", program);
        return 1;
        }

        // check difficulty for creator
        char* difficulty = argc[2];
        if(strcmp(difficulty, "easy")!=0 && strcmp(difficulty, "hard")!=0){
            fprintf(stderr, "Usage: %s mode difficulty (difficulty is only required for create mode), difficulty should be either \"easy\" or \"hard\"\n", program);
            return 1;
        }
        bool difficult = strcmp(difficulty,"hard") == 0;

        // create sudoku
        sudoku_t* sudoku = create(difficult, dim);
        if(sudoku == NULL){
            fprintf(stderr, "Failed to create a sudoku.\n");
            return 1;
        }

        // display sudoku
        display(sudoku);

        // clean the memory
        delete_sudoku(sudoku);
    }else{
        /************* calling solver **************/
        // check mode must be solve
        if(strcmp(mode, "solve") != 0){
        fprintf(stderr, "Usage: %s mode difficulty (difficulty is only required for create mode) \n", program);
        return 1;
        }

        // read sudoku
        sudoku_t* sudoku = read_sudoku(false); 
        if(sudoku == NULL){
            fprintf(stderr, "Failed to read from sudoku.\n");
            return 1;
        }

        // solve sudoku
        solve_board(sudoku, false);
        
        // display sudoku
        display(sudoku);

        // clean up memory
        delete_sudoku(sudoku);
    }

    return 0;
}
