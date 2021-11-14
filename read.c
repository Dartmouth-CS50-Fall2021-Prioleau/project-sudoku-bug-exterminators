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

#include "read.h"
#include "display.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

/* (description): Reads a sudoku puzzle from stdin, 
 *                extracts and stores the numbers in 
 *                the sudoku data structure.
 *
 * (inputs): A boolean value indicates if it is a difficult mode
 *
 * (outputs): The function will return a pointer to sudoku.
 * 
 * (Support): So far, the read function supports reading two-digit numbers
 *
 */
sudoku_t *read_sudoku(bool difficult)
{
    // create sudoku
    sudoku_t* sudoku = malloc(sizeof(sudoku_t));
    if(sudoku == NULL){
        fprintf(stderr, "Failed to malloc for sudoku.\n");
        exit(2);
    }

    // dim information (may need to support 16)
    int dim = 9;
    sudoku->dim = dim;

    // create board
    box_t ***board = malloc(sizeof(box_t**) * dim);
    if(board == NULL){
        fprintf(stderr, "Failed to malloc for board.\n");
        // delete before exiting
        delete_sudoku(sudoku);
        exit(2);
    }
    for(int i=0 ;i<dim; i++){
        board[i] = malloc(sizeof(box_t*)*dim);
        if(board[i] == NULL){
            fprintf(stderr, "Failed to malloc for board row.\n");
            // delete before exiting
            delete_sudoku(sudoku);
            exit(2);
        }
    }
    sudoku->board = board;


    // read from stdin
    char c;             // character from stdin
    int c_number;       // character corresponding digit
    int row = 0;        // row index
    int col = 0;        // column index
    int num_ttl = 0;    // total number input (including 0 or .)
    int num_given = 0;  // total number given 

    while((c = getchar()) != EOF){
        if(isdigit(c) || c == '.'){
            // increase num_ttl
            num_ttl++;
            if(c != '.' && c != '0'){
                num_given++;
            }

            if(num_ttl > dim * dim){
                fprintf(stderr, "Input number of numbers exceeds the required amount.\n");
                // delete before exiting
                delete_sudoku(sudoku);
                exit(2);
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
                // delete before exiting
                delete_sudoku(sudoku);
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
    if(num_given < 25){
       fprintf(stderr, "At least 25 numbers should be given.\n");
       delete_sudoku(sudoku);
       exit(4);
    }
    
    //return sudoku;
    return sudoku_ini(difficult, sudoku);
    
}


/* (description): Calls the read function to get the sudoku puzzle. Then it 
 *                initializes the number used for rows, columns, and boxes.
 *                Finally, it compute the possible numbers for each blank grid
 *                by doing the bitwise opeartion.
 *
 * (inputs): A boolean value indicates if it is a difficult mode
 *
 * (Return): The function will return a pointer to sudoku with all data initialized.
 *
 * (support): 
 */
sudoku_t *sudoku_ini(bool difficult, sudoku_t* sudoku)
{
    box_t*** board = sudoku->board;

    // get dim
    int dim = sudoku->dim;
    
    // row used record
    int* row = array_create(dim, sudoku);

    // column used record
    int* col = array_create(dim, sudoku);

    // box used record
    int* box = array_create(dim, sudoku);

    sudoku->rows = row;
    sudoku->columns = col;
    sudoku->boxes = box;

    // initialization of rows, cols, boxes
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            int num = board[i][j]->num;
            if(num != 0){
                int k = box_index(i, j, dim);
                // check duplicates (trail)
                if((row[i] >> (num -1))%2 == 1){
                    fprintf(stderr,"Duplicate %d in the row.\n", num);
                    delete_sudoku(sudoku);
                    exit(2);
                }

                if((col[j] >> (num -1))%2 == 1){
                    fprintf(stderr,"Duplicate %d in the column.\n", num);
                    delete_sudoku(sudoku);
                    exit(2);
                }

                if((box[k] >> (num -1))%2 == 1){
                    fprintf(stderr,"Duplicate %d in the box.\n", num);
                    delete_sudoku(sudoku);
                    exit(2);
                }

                // save records
                row[i] |= 1<<(num-1);
                col[j] |= 1<<(num-1);
                box[k] |= 1<<(num-1);

            }
        }
    }

    return sudoku;
}

/* (description): Calloc for an array of size passed in
 *
 * (inputs): dim - represent the size of the array
 *
 * (Return): a malloced array
 *
 */
int* array_create(int dim, sudoku_t* sudoku)
{
    int* array = calloc(dim, sizeof(int));
    if(array == NULL){
        fprintf(stderr, "Failed to malloc for array\n");
        // delete before exiting
        delete_sudoku(sudoku);
        exit(2);
    }
    return array;
}

/* (description): Maps the position of a specific grid to
 *                the index of the box which current grid is in
 *
 * (inputs): dim is the size of sudoku board for each dimension
 *           row and col are the indices indicating the position of the grid
 *
 * (Return): an integer - the index of the box for the current grid
 *
 */
int box_index(int row, int col, int dim)
{
    int box_size = sqrt(dim);
    return (row / box_size) * box_size + (col / box_size);
}

/*
 * (description): Clean up the memory for the sudoku board
 *
 * (input): sudoku - the puzzle
 * 
 * (implementation): The function starts by freeing each cell,
 *                   then, it frees each row in the 2D board,
 *                   followed by free the whole board. Finally,
 *                   the function frees the rows, columns and 
 *                   boxes.
 */
void delete_sudoku(sudoku_t* sudoku)
{
    if(sudoku != NULL){
        // get dim
        int dim = sudoku->dim;

        // free the board
        box_t*** board = sudoku->board;
        if(board != NULL){
            for(int i=0; i <dim; i++){
                box_t** row = board[i];
                if(row != NULL){
                    for(int j = 0; j<dim; j++){
                        box_t* grid = row[j];
                        if(grid != NULL){
                            //free the grid
                            free(grid);
                        }
                    }
                    // free the row
                    free(row);
                }
            }
            // free the board
            free(board);
        }

        // free the rows / cols / boxes
        if(sudoku->rows != NULL){
            free(sudoku->rows);
        }
        if(sudoku->columns != NULL){
            free(sudoku->columns);
        }
        if(sudoku->boxes != NULL){
            free(sudoku->boxes);
        }
        // free the sudoku
        free(sudoku);
    }
}

/*
 * (Description): The function takes in an integer and returns
 *                a string representing the binary format of the
 *                integer.
 * (Inputs): n - integer
 *           len - the length of the binary format
 * 
 * (Return): a string representing the binary format of the integer
 */
char* binary_format(int n, int len)
{   

    char* binary = malloc(sizeof(char) * len);
    
    // loop index
    int idx = 0;

    for (int i = (1 << (len - 1)); i > 0; i = i / 2) {
        binary[idx] = (n & i) > 0 ? '1' : '0';
        idx++;
    }
    binary[idx] = '\0';


    return binary;
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

int main(){
    sudoku_t* puzzle = read_sudoku(false);
    display(puzzle);
}

#endif

