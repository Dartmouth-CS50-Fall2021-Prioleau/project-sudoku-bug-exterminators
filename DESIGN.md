# Design Specifications for Sudoku 3.0
This is the design spec for our sudoku project. It includes an overview of the 
data structures that we will be using as well as some of the functions we 
plan to implement. 

## Data Structures
In this subsection, we overview the data structures that the project will use. This 
primarily includes two structs: `box_t` and `sudoku_t`. The former represents a struct
representing a square on the sudoku board, and the latter represents a struct representing
the sudoku board itself. We start by describing the `box_t` struct. 

The *`box_t`* struct represents a square on the sudoku board. It needs to store the value
that this square manifests. For ease of computation, the struct also had another member
which represented the possibilities that this square could take on. The declaration for
this structure is shown below:
```C
typedef struct box {
  int num;
  int possible;
} box_t;
```
The second member `int possible` is the possiblities represented as a bit string, such
that the lower-order bits code for the numbers `1, 2, 3, ...`. Where, 1 represents that
the number is possible, and 0 represents that the number at that index is not possible.

The *`sudoku_t`* struct represents a sudoku board. It must contain a 2D array of `box_t`
square. It also contains its dimensions as an `int`. Similar to the `box_t` structure,
for ease of computation, the numbers that already exist in each column, box, and row
are also stored in bit strings. Where, 1 represents that the number already exists in
that row/column/box, and 0 represents that that number does not already exist in that
row/column/box. The declaration for this structure is shown below:
```C
typdef struct sudoku {
  box_t ***board;
  int *rows;
  int *columns;
  int *boxes;
  int dim;
}
```

## Functions
In this subsection, we overview the basic functions/modules that our program must 
implement, and the relationship between these various modules. 

To implement all of the required functionality, our program has four distinct modules:
  - Display (displays the board in a pretty and simple format).
  - Read (reads a given sudoku board from `stdin`, initalizes a board struct that is associated wwit this given board)
  - Solve (given a board struct, the solve module is able to check if a given board is unique as well as solve the board completely, while adhere to the rules of sudoku)
  - Create (based on the given level of difficulty, this module creates a board whose number of givens correspond to the level of required difficulty)
  - Sudoku (includes the main function that parses the arguments associated with the program)

The interactions between these modules are detailed in the pseudocode subsection. This section exclusively gives a systematic overview of these modules.
 
### Sudoku
This module holds the `main` function of the program. It parses the command line arguments and
then returns the appropriate functionalities. The user can use the program in two modes: create
or solve. An example of each of these modes in use is shown below:
```bash
./sudoku create hard 
./sudoku create easy
```

```bash
./sudoku solve
```
We note that in the latter example, the program will then prompt the user to enter in a 
sudoku puzzle. This puzzle need not have a unique solution, but it should be solvable. 
Moreover, it is expected that this puzzle conforms to the format of either the pretty sudoku
or the simple one shown below.

### Display
Our design for the pretty sudoku board is shown below:
	```
	+-------+-------+-------+
	| 9 . . | . . . | . . 1 |
	| . . . | . . 2 | . . . |
	| . . . | . . 3 | . . . |
	+-------+-------+-------+
	| 8 . . | 4 . . | . . 3 |
	| 2 . . | . . . | . . . |
	| . . 1 | . . . | . 4 . |
	+-------+-------+-------+
	| . . 4 | 5 . 6 | 3 . . |
 	| . . . | . . . | . . . | 
	| 6 1 . | . 2 . | 5 9 7 |
	+-------+-------+-------+
	```
We used the `.` character to represent empty cells, while the numbers represents the values
of the cells that are filled in. Our design module is also able to print out the board in
a simple format:
  ```
 0 0 3 0 2 0 6 0 0
 9 0 0 3 0 5 0 0 1
 0 0 1 8 0 6 4 0 0
 0 0 8 1 0 2 9 0 0
 7 0 0 0 0 0 0 0 8
 0 0 6 7 0 8 2 0 0
 0 0 2 6 0 9 5 0 0
 8 0 0 2 0 3 0 0 9
 0 0 5 0 1 0 3 0 0
  ```
Here, 0s represent empty cells, while non-zero values represent the values of non-empty cells.

### Read
The read module reads in a sudoku board from `stdin` and intializes a `sudoku_t` structure.
The read module also contains functions that will support the `sudoku_t` structure, such 
allocating and freeing these dynamically create structures. We note that when the read 
module reads in from `stdin`, it will also initialize the possible-value bit strings
for each column, row, box.

### Solve 
The solve module contains two main functionalities: solving a given board, and checking
if a given board is unique. Our sudoku solver uses a backtracking algorithm that 
solves a sudoku puzzle through brute force. On the other hand, the module can also
check if a given sudoku puzzle has a unique solution. It does this by checking if 
all the possible values for a given square work -- regardless of whether or not
a solution has already been found. 

### Create
The create module creates a sudoku puzzle with a unique solution, given the level of
difficulty:
  - Easy : 37 givens
  - Hard : 25 givens
The program will randomly generate a solved puzzle first; this guarantees that a solution 
exists. Then, a puzzle will be created by plucking out numbers from the board until 
the number of numbers plucked out equals to the toal numbers - the numbers of givens 
for that difficulty level. At each pluck, the uniqueness of the puzzle will be checked.

## High-level Pseudocode
1. Parse arguments associated with the program, if invalid then exit.
2. If create mode, the create sudoku.
3. If solve, then read in sudoku board from stdin.
4. Display the result to stdout.
  
