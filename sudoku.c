#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "create.h"
#include "solve.h"
#include "board.h"
#include "read.h"

int main(const int argv, char* argc[]){
    // get the program
    char* program = argc[0];

    // check the number of arguments
    if(argv != 3){
        fprintf(stderr, "Usage: %s mode difficulty\n", program);
        return 1;
    }

    // check mode
    char* mode = argc[1];
    if(strcmp(mode, "create") != 0 && strcmp(mode, "solve") != 0){
        fprintf(stderr, "Usage: %s mode difficulty, mode should be either \"create\" or \"solve\"\n", program);
        return 1;
    }

    // check difficulty
    char* difficulty = argc[2];
    if(strcmp(difficulty, "easy")!=0 && strcmp(difficulty, "hard")!=0){
        fprintf(stderr, "Usage: %s mode difficulty, difficulty should be either \"easy\" or \"hard\"\n", program);
        return 1;
    }

    // calling the functions
    bool difficult = strcmp(difficulty,"hard") == 0;
    int dim = 9;
    if(strcmp(mode,"create")==0){
        // creator
        create(difficult, dim);
    }else{
        // solver
        sudoku_t* sudoku = read_sudoku(false); // TODO: need to corresponds the param to the dim
        if(sudoku == NULL){
            fprintf(stderr, "Failed to read from sudoku.\n");
            return 1;
        }
        solve_board(sudoku);
    }

    return 0;
}
