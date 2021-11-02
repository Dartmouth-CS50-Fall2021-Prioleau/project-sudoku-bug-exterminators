# Data Structures
We need a `struct` to store the sudoku. The structure would need the following members:
- 2D array (square)
- The number of items in each row/column
- The "box" size

# Functions
- Check if the sudoku has been solved correctly.
  - Check if number works in the row.
  - Check if number works in column.
  - Check if number works in box.
- Display sudoku.
  - Border around each number.
  - Border around each sub-box.
  - Border around the entire box.
	```c
	+-------+-------+-------+
	| 9 . . | . . . | . . 1 |
	| 0 . . | . . 2 | . . . |
	| . . . | . . 3 | . . . |
	+-------+-------+-------+
	| 8 . . | 4 . . | . . 3 |
	| 2 . 0 | . . . | . . . |
	| . . 1 | . . . | . 4 . |
	+-------+-------+-------+
	| . . 4 | 5 . 6 | 3 . . |
 	| . . . | . . . | . . . | 
	| 6 1 . | 0 2 . | 5 9 7 |
	+-------+-------+-------+
	```
- Solve sudoku. 
  1. Loop through each empty box, generate a random number between 1-9.
  2. Check if this number satisfies all three conditions. 
  3. If it does then insert this number.
- Create sudoku.
  1. Solve board with all empty squares.
  2. Hide number of squares that correspond to difficulty.
  3. Display this sudoku.

  or

  - Randomly generate 27 or 35 numbers on the board depending on the difficulty
  1. Randomly generate a series of positions to fill
  2. For each position, check the range of numbers to generate
  3. For each position randomly generate a number from the range
  
