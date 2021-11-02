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
- Solve sudoku. 
  1. Loop through each empty box, generate a random number between 1-9.
  2. Check if this number satisfies all three conditions. 
  3. If it does then insert this number.
- Create sudoku.
  1. Solve board with all empty squares.
  2. Hide number of squares that correspond to difficulty.
  3. Display this sudoku.

./sudoku create hard | ./sudoku solve

+---+---+----- 
| 1 |0 0 |
+---+
| 0 |1 0 |
| 0 0 1 |
5 1 0 0 0 ..
0 0 0 0 0 ..
0 0 0 0 0 ..
0 0 0 0 0 ..
0 0 0 0 0 ..
0 0 0 0 0 ..

