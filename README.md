# Bug Exterminators 
## Alan Sun, Arden Guo
## CS50 Fall 2021, Final Project - Sudoku 2.0

GitHub usernames: alansun17904, ArdenDartmouth

## Modularity and Motivation (Directory Tree and functions)
```
project
├── .gitignore
├── README.md		
├── DESIGN.md
├──	IMPLEMENTATION.md
├──	Makefile
|	
├──	board.h			# data structure
|
├──	read.h			# read the puzzle, initialize data structure
├──	read.c
|
├──	create.h		# create sudoku puzzle
├──	create.c
|
├──	solve.h			# solve sudoku puzzle (optimization)
├──	solve.c
|
├──	display.h		# display sudoku puzzle
├──	display.c
|
├──	sudoku.c		# the main program
│
├── testing.sh		# test cases
├── testing.out

```
- Different functions has been written within different places for better modularity.

## Usage

- run `make` to complie
- Create:
    - `./sudoku create easy/hard`
- Solve
    - `./sudoku solve`
- run `make test` to test

## Functionality

- `read module`: read the puzzle
```c
sudoku_t *read_sudoku(bool difficult);
sudoku_t *sudoku_ini(bool difficulty, sudoku_t* sudoku);
int* array_create(int dim, sudoku_t* sudoku);
int box_index(int row, int col, int dim);
void delete_sudoku(sudoku_t* sudoku);
char* binary_format(int n, int len);
```
- The above function:
    - read the puzzle from stdin, which accepts both standard format and our prettier format
    - initialize the data structure
    - create an array using dynamic memory allocator
    - map the current cell to the index of the box it is in
    - clean up the memory of the sudoku board
    - return the binary format of an integer (easy for us to debug)

- `display module`
```c
void display(sudoku_t *board);
void sdisplay(sudoku_t *board);
```
- The above function:
    - display the sudoku board in pretty format
    - display the sudoku board in standard format

- `create module`
```c
sudoku_t *create(bool difficulty, int dim);
```
The function create the sudoku puzzle according to the difficulty specified

- `solve module`
```c
bool solve_board(sudoku_t *board, bool random);
int is_unique(sudoku_t *puzzle);
void set_square(sudoku_t *, box_t *, int num, int i, int j);
void unset_square(sudoku_t *, box_t *, int num, int i, int j);
```
- The above function:
    - solve the puzzle using back tracking
    - check the uniqueness of the puzzle
    - set the cell to a number and update the corresponding row, column and box 
    - unset the cell and revert the row, column and box back to the origin

- `sudoku module`
The main function which checks the arguments and tries to either create or solve a puzzle according to 
use's specification of mode and difficulty levels 



