# Implementation Specification for Sudoku 3.0

## Data Structures
- Box (Cell in the puzzle)
	- The number in the box
	- The possible numbers that the box(cell) could use (Using an integer for this, the corresponding binary bit representation would contains all the information)
```C
typedef struct box {
	int num;
	int possible;
} box_t;
```
- Sudoku board:  2D array of type interger
	- Row Used: an array of integers, the binary representation of each integer indicates used numbers with 1s
	- Column Used: an array of integers, the binary representation of each integer indicates used numbers with 1s
	- Box Used: an array of integers, the binary representation of each integer indicates used numbers with 1s

```C
typedef struct sudoku {
  box_t ***board;
  int *rows;
  int *columns;
  int *boxes;
  int dim;
} sudoku_t;
```

- Visualization of possible numbers implementation for each cell, row, column, box
```c
 Example 
 int possible = 13;

 Binary Representation of 13:

 +---+---+---+---+---+---+---+---+---+
 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 1 |
 +---+---+---+---+---+---+---+---+---+
                       |   |       |
                       |   |       |
                       v   v       v
   9   8   7   6   5   4   3   2   1


 "So int possible = 13 means for a cell means that 1, 3, and 4 are available for this cell"
 "While int possible = 13 for a row/ column/ box means that 1, 3, and 4 has been used"
```

## Functions Implementation - Creator and Solver

- Sudoku solver (Backtracking)
	- Return: boolean
	- Implementation:
		```
		loop through the board 
			for blank grid
				get the range of possible numbers
				for each number in the range
					set the grid to the numnber 
					update the row/column/box used
					 
					if (! solver()) 

						set the grid back to 0
						update the row/column/box back
		```

- Sudoku solver (Backtracking & Optimization)
	- Return: boolean
	- Implementation:
		```
		get an array of blank grids of the board
		loop through the blank grid of the board 
			for blank grid
				get the range of possible numbers
				for each number in the range
					set the grid to the numnber 
					update the row/column/box used
					 
					if (! solver()) 

						set the grid back to 0
						update the row/column/box back
		```

- Creator
	- Implementation
	```
	step 1: solve an empty board by calling the solve function
			(randomly choose the number for each cell from the list of possible numbers)
	
	step 2: randomly pluck numbers from the board
			an array of indices is created, each index corresponds to one cell in the sudoku board (e.g. 0 -- 80)
			randomly shuffle the indices
			start pluck numbers from cells with indices starting in the array

	step 3: checking uniqueness
			use backtracking to see if there is only one solution to the puzzle ( similar to solver)

	```

## Other function Implementation

- read function
```
step 1: create the sudoku board using dynamic memory allocator (malloc)
step 2: read input from stdin
		the function reads character by character
		if it is a non-zero number -> put the number into the board
		if it is a zero or a dot '.' -> put zero into the board (blank cell)
step 3: initialize the row, column, box array by using dynamic memory allocator
		this corresponds to the data structure described in the section of data structure
		the function also check if there is duplicated numbers within each row, column and box
		by checking the bit representation of the possible
```

- display function
The project displays a puzzle in the following format. The function loop through the board and print out the puzzle.
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

- Helper function

A series helper functions have been implemented, please refer to the detailed descriptions.

## Optimization

- Instead of looping through the 2D array puzzle and tries the possible numbers for each blank cell,
we start fill the blank cell with the least possible number of numbers. However, it turned out to be 2 to 4
times slower than our original algorithm.

- Thoughts
	- We think the slowing down might be caused by the time used for pre-sorting the blank cells.


## Error Handling and Recovery

- Malloc Error
	- The program always checks NULL pointer after malloc
	- If NULL pointer is found, we start delete all the memory created by looping throught the whole puzzle
	- Then exit with value `2`

- Arguments Error
	- The program checks if the number of arguments is correct: either 2 or 3 is fine
	- If the number of argument is 2, then the program mode should be checked if it is `solve`
	- If the number of argument is 3, then the program mode should be checked if it is `create`
	- If create mode is called, the program should check if the difficulty matches `easy` or `hard`
	- The errors from the above tests result in a return (exit) with value `1` 

## Testing
Please refer testing.md for more information


	
				
		


