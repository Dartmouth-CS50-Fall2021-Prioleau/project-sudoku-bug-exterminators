
# ******************** Test Part I - Argument Validation ************************

# 1. number of arguments less than 2
./sudoku 

# 2. number of arguments more than 3
./sudoku create easy more

# 3. sudoku with 3 arguments (should be creator)
./sudoku solve easy

# 4. sudoku with 3 arguments (creator) with incorrect difficulty
./sudoku create mid

# 5. sudoku with 2 arguments (should be solve)
./sudoku create

# 6. sudoku with 2 arguments but mode is not solve or create
./sudoku other

# 7. sudoku with 3 arguments but mode is not solve or create
./sudoku other easy


# ******************** Test Part II - Testing Creator ************************

# 8. create easy puzzle
./sudoku create easy

# 9. create hard puzzle
./sudoku create hard


# ******************** Test Part III - Testing Solver ************************

# 10. solve easy puzzle
./sudoku create easy | ./sudoku solve

# 11. solve hard puzzle
./sudoku create hard | ./sudoku solve


# ******************** Test Part IV - Average Time Testing ************************

# 12. average time for creating 50 easy puzzle
start=$SECONDS
for i in {1..50}
do
    ./sudoku create easy
done
duration=$(( SECONDS - start ))
