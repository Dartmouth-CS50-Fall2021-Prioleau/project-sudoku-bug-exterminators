# Implementation Specification for Sudoku 2.0

## Data Structures
- Box
	- The number in the box
	- The possible numbers that the box could contain
```C
typdef struct box {
	int num;
	int *possible;
} box_t;
```
- Sudoku board:  2D array of type interger
	- Row Used: an array of 0s and 1s
	- Column Used: an array of 0s and 1s
	- Box Used: an array of 0s and 1s (need to think about the index mapping)

```C
typdef struct sudoku {
  box_t **board;
  int **rows;
  int **columns
  int **boxes;
  int dim;
} sudoku_t;

```

## Functions Implementation

- Row checker	
	
	- Params: `Row Used`, `Row index` and `current number`
	- Return: boolean		
		- true - if current number not in current row
		- false - if current number in current row
	- Implementation
		- `row index` to get the set of current row used numbers
		-  use set_find to check the exisitance
		-  return the result

```C

```

- Column checker	
	- Params: `Column Used`, `Column Index` and `current number`
 	- Return: similar to Row checker
	- Implementation: Similar to Row checker

- Box checker	
	- Params: `Box Used`, `Row index`, `Column index` and `current number`
	- Return: similar to Row checker
	- Implementation: similar to Row checker
		- Use `Index Mapping for Box` to get the index of the box

- Index mapping for box
	- Params: `Row index`, `Column index`, `box size`
	- Return: Index of the corresponding box in the array 
	- Implementation: 
		```c
			// params
			int row_index;
			int col_index;
			int box_size;

			return (row_index % box_size) + (col_index % box_size);
		```

- Range of numbers
	- Description: get the range of numbers possible for the current grid
	- Params: `Row index` and `column index`
	- Return: An array of 0s and 1s 
	- Implementation: Intersect the three arrays to get the result (i.e. `row used`, `column used` and `box used`)

- Sudoku solver
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


- Display sodoku
				
		


