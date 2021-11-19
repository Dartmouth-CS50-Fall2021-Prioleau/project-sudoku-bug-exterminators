
# Project rubric: Bug Exterminators

## **GRADES**

|Problem|Score|
|:-------|------:|
|Design Review|5/5|
|Documentation & Testing|15/15|
|Code Quality, Style, Git Practices|40/40|
|Functionality|34/35|
|Project Demo|5/5|
|Extra Credits|0/5|
|**TOTAL**|**99**|

<!--* include your perspective on each student's contribution to the project -->

## (5/5) Design review

## (15/15) Documentation and testing

* (5/5) `DESIGN.md`, which describes the abstract design with no language-specific details.
  * (2) description of input and output of each module, and data flow.
  * (1) clear description of data structure designs.
  * (2) clear description of the proposed Suduko solving algorithm.

* (3/3) `IMPLEMENTATION.md`, which describes implementation details.
  * (1) pseudo code for each main component/function
  * (1) detailed data structure design (e.g., struct names and members)
  * (1) definitions of APIs, interfaces, function prototypes.  

* (1/1) `README.md`, which says how to build the program, assumptions made by the program, etc.
* (6/6) `TESTING.md` or `testing.sh`, which summarizes testing strategies (e.g., unit test, fuzz test), testing results, possibly categorizes the test cases.

## (40/40) Code quality and style, git use

### (5/5) Makefile

* (3) builds executables with no compilation errors or warnings, -1 point per compilation warning, -5 at most.
* (1) has an appropriate `clean` rule.
* (1) uses CS50 standard CC flags.

### (10/10) Memory leaks, according to valgrind

* (4) free of *memory errors*.
* (4) free of *lost memory blocks*.
* (2) free of *still reachable* memory blocks.  
**Note: no points taken off if memory leaks come from existing libraries (e.g., Gtk).**

### (5/5) Git repo requirements

* (1) Proper file structure with appropriate `.gitignore`.
* (1) Proper tagging of the final version `projsubmit`.
* (1) Git repo should not track any data files, core dumps or compiled objects.
* (2) Regular use of git to commit code as the code evolves

### (20/20) Visual Representation and Coding Style

* (5) Visual Representation
* [CS50 C program coding style](http://www.cs.dartmouth.edu/~cs50/Resources/CodingStyle.html)
  * (2) proper comments in the code
  * (2) minimize the number of global variables
  * (6) Modular design (cohesion/coupling):
    * have a component (e.g., checking if an updated cell still make the puzzle valid) implemented as a separate function if it is reused at multiple places, rather than repeating the code block at multiple places.
    * good cohesion within each function (no super long functions)
    * avoid deep nested loops
    * clean and well-designed interface among functions
  * (2) Clean separation between application-specific functionalities and data structure modules.
  * (4) Proper use of dynamic memory allocation (malloc/calloc/realloc) for variables with unknown sizes, rather than using fixed-size arrays, which can easily break if array size is not large enough.
  * (4) The code should be rigorous in error-handling, i.e., checking for errors after memory allocation (malloc/calloc/realloc), fopen(), read()/write(), struct constructors, etc, so that the code exits gracefully if any unexpected errors in these operations.

## (34/35) Functionality

### (25 for *3-person teams*) Difficulty Level: Easy *(30 for 2-person team)*

* (2/2) Validation of command-line arguments
  * check the number of arguments
  * check the provided options

  * (16/16) Soduku creator:
    * (10) Create a puzzle with a unique solution
    * (2) There are at least 40 missing numbers in created puzzles
    * (3) Created puzzles are randomized
    * (1) Printing puzzle to stdout.

  * (16/17) Sudoku solver:
    * (1/1) Read the puzzle from stdin and print the solution to stdout
    * (15/16) Able to find one possible solution for a given puzzle

> There's a case in which your solver unit test seg-faults:
> The error seems to come from the `test_unique_hard2()`.

```text
./solve_test
Test Unique Simple.
Test Unique Hard 1.
At least 25 numbers should be given.
Segmentation fault
```

>
> There's an additional segmentation when your solver is given a puzzle with only 8 rows, as is the case with [invalid 3](./Testing/test-invalid3.txt)

```text
Invalid 3

./grading.sh: line 16:  9673 Segmentation fault      ./sudoku solve < "$dir/test-invalid3.txt"
```

### (5/5) Difficulty Level: Hard

* solved within "reasonable" time  
  > Your solution is super-fast!

### (5 for *3-person teams*) Successful Implementation of 1 Topping Option*(Does not apply to 2-person teams)*

1. **Graphical UI:** Implement and show the game progress using a graphics software.
   * Your graphics component need not run on Linux servers.
   * It doesn’t have to be written in C.
   * You can dump your sequence of moves to a file and show the animation using a program independent of your Sudoku project. That program can be in any programming language of your choice.
2. **Sudoku variants:**
  Given the large number of Sudoku variants, your program can implement another variant in addition to the basic 9x9 grid form. The user can choose the type of Sudoku to create or solve. As an example, a 3D Sudoku can be in the form of a 9x9x9 cube, where numbers need to be filled in this cube satisfying the Sudoku rules.
3. **Sudoku across machines:**
  While we have not talked about socket programming you are invited to review the lecture notes on this topic and you can actually apply socket programming to realize a client-server model for your Sudoku program. The Sudoku creator runs at one server and Sudoku solver runs at another. The solver requests a Sudoku challenge from the creator and then solves it. To implement it, you will need to think about how to send the Sudoku puzzle using sockets.

## (5) Project demo and presentation

* clear presentation of the code design and algorithm.
* successful demo
* clarity in answering questions

## (+0) Extra credits

* (5) Fastest solve times on difficulty level `hard`
* (5) Successful implementation of a second ["topping" option from the given options](https://www.cs.dartmouth.edu/~cs50/Project/#choose-your-topping) or implement other interesting ideas that go above and beyond

## Penalties: **0*
