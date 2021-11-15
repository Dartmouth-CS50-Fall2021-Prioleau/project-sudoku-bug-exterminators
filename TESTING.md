## Testing Spec

- Unit Test
	- Unit test has been implemented within each module, except sudoku which use the `testing.sh`
	- The unit tests need the `tests folder`

- Our testing consists of four parts:
	- Part I: Argument Validation
	- Part II: Testing creator 
	- Part III: Testing solver
	- Part Iv: Testing average time for creating and solving 
	- run: `bash -v testing.sh`

Each part consists of a series of test cases. Please refer to the description of each cases for detailed information.

- Time (Our average time is based on 50 times of running the command)

	`./sudoku create easy`
	- Average time for creating an easy puzzle: .00856987266000000000 s

	`./sudoku create hard`
	- Average time for creating a hard puzzle: .14232855268000000000 s

	`./sudoku create easy | ./sudoku solve`
	- Average time for creating and solvng an easy puzzle: .00924671768000000000 s

	`./sudoku create hard | ./sudoku solve`
	- Average time for creating and solving a hard puzzle: .12921507648000000000 s

