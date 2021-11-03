# Implementation Specification for Sudoku 2.0

## Data Structures

- Sudoku board:  2D array of type interger
- Row Used: an array of sets
- Column Used: an array of sets
- Box Used: an array of sets (need to think about the index mapping)


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
- Display sodoku
				
		


