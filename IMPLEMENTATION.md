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
	- 
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

- Blank grids of the board
	- Param: borad
	- Rerturn: an array of indices for blank grids

- Possible number array (intersection of row/column/box arrays)
	- Params: `row used`, `column used` and `box used`
	- Return: an array of 0s and 1s
	- Implementation: 
		```
			create an array for the result
			loop through index of the arrays
				the result = bit & operation of the corresponding three elements  
		```

- Display sodoku
	- Params: the board
				
		


