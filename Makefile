# Alan Sun, Arden Guo
# CS50, Fall 2021, Sudoku Project
# 
# This Makefile builds and compiles the querier program and unittests in
# sudoku.c and its associated modules.

CFLAGS = -Wall -pedantic -std=c11 -ggdb 
LIBS = -lm
CC = gcc
PROG = sudoku
OBJS = sudoku.o create.o solve.o read.o display.o

.PHONY: clean 

all: $(PROG)
$(PROG): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROG)

sudoku.o: create.h solve.h read.h display.h board.h
#	$(CC) $(CFLAGS) -c sudoku.c

create_test: create.c solve.o board.h display.o read.o read.h
	$(CC) $(CFLAGS) -DUNIT_TEST create.c read.o \
					display.o solve.o $(LIBS) -o create_test

create.o: create.c board.h solve.h read.h display.h create.h
	$(CC) $(CFLAGS) -c create.c

read.o: read.c read.h 
	$(CC) $(CFLAGS) -c read.c 

display.o: display.c display.h board.h
	$(CC) $(CFLAGS) -c display.c

display_test: display.c display.h board.h
	$(CC) $(CFLAGS) -DUNIT_TEST display.c $(LIBS) -o display_test

solve.o: solve.c solve.h board.h
	$(CC) $(CFLAGS) -c solve.c

solve_test: solve.c solve.h board.h display.o read.h read.o
	$(CC) $(CFLAGS) -DUNIT_TEST solve.c read.o display.o $(LIBS) -o solve_test

test: 
	./testing.sh &> testing.out

valgrind:
	./testing.sh CHECK_MEMORY &> val.out

clean:
	rm -rf testing.out
	rm -rf $$(ls | grep "^test[0-9]*$$" | tr "\n" " ") 
	rm -rf *.x *.o
	rm -f sudoku create_test display_test test solve_test read
