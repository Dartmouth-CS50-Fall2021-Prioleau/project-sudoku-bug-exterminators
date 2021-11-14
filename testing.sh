#!/bin/bash
# Arden Guo, Alan Sun
# CS50, Fall 2021, Sudoku Project
# Integration testing for the sudoku creator and solver
#
# This script acts as a tester for the sudoku project. For testing cases that 
# are valid, the tester must check the validity of the output themselves 
# through visual insepection. Each test will have a brief explanation of what
# the test is and its expected results. To run these tests with `valgrind` 
# the tester can simply project the argument `CHECK_MEMORY` to the testing
# script.

# ******************** Test Setup *********************************************
if [ ! -z "$1" ]; then
  if [ $1 == "CHECK_MEMORY" ]; then
    VALGRIND="valgrind --leak-check=full --show-leak-kinds=all" 
    echo The following tests will check for memory leaks.
  fi 
else
  VALGRIND=""
  echo The following tests will run without checking for memory leaks.
fi

make

# ******************** Test Part I - Argument Validation ************************

# 1. number of arguments less than 2
$VALGRIND ./sudoku 

# 2. number of arguments more than 3
$VALGRIND ./sudoku create easy more

# 3. sudoku with 3 arguments (should be creator)
$VALGRIND ./sudoku solve easy

# 4. sudoku with 3 arguments (creator) with incorrect difficulty
$VALGRIND ./sudoku create mid

# 5. sudoku with 2 arguments (should be solve)
$VALGRIND ./sudoku create

# 6. sudoku with 2 arguments but mode is not solve or create
$VALGRIND ./sudoku other

# 7. sudoku with 3 arguments but mode is not solve or create
$VALGRIND ./sudoku other easy


# ******************** Test Part II - Testing Creator ************************

# 8. create easy puzzle
$VALGRIND ./sudoku create easy

# 9. create hard puzzle
$VALGRIND ./sudoku create hard


# ******************** Test Part III - Testing Solver ************************

# 10. solve easy puzzle
$VALGRIND ./sudoku create easy | ./sudoku solve

# 11. solve hard puzzle
$VALGRIND ./sudoku create hard | ./sudoku solve


# ******************** Test Part IV - Average Time Testing ************************

# 12. average time for creating 50 easy puzzle
start=`date +%s.%N`
for i in {1..50}
do
    ./sudoku create easy
done
end=`date +%s.%N`
runtime=$( echo "($end - $start) / 50 " | bc -l )
echo "Average time for creating an easy puzzle: $runtime"

# 13. average time for creating 50 hard puzzle
start=`date +%s.%N`
for i in {1..50}
do
    ./sudoku create hard
done
end=`date +%s.%N`
runtime=$( echo "($end - $start) / 50 " | bc -l )
echo "Average time for creating a hard puzzle: $runtime"

# 14. average time for creating and solving 50 easy puzzle
start=`date +%s.%N`
for i in {1..50}
do
    ./sudoku create easy | ./sudoku solve
done
end=`date +%s.%N`
runtime=$( echo "($end - $start) / 50 " | bc -l )
echo "Average time for creating and solvng an easy puzzle: $runtime"

# 15. average time for creating and solving 50 hard puzzle
start=`date +%s.%N`
for i in {1..50}
do
    ./sudoku create hard | ./sudoku solve
done
end=`date +%s.%N`
runtime=$( echo "($end - $start) / 50 " | bc -l )
echo "Average time for creating and solving a hard puzzle: $runtime"
