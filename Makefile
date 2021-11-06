# Alan Sun, Arden Guo
# CS50, Fall 2021, Sudoku Project
# 
# This Makefile builds and compiles the querier program and unittests in
# sudoku.c and its associated modules.

CFLAGS = -Wall -pedantic -std=c11 -ggdb 
LIBS = -lm
CC = gcc

.PHONY: clean 

all: 


display.o: display.c display.h
	$(CC) $(CFLAGS) -c display.c

display_test: display.c display.h
	$(CC) $(CFLAGS) -DUNIT_TEST display.c $(LIBS) -o display_test

test: 
	./testing.sh &> testing.out

valgrind:
	./testing.sh CHECK_MEMORY &> testing.out

clean:
	rm -rf testing.out
	rm -rf $$(ls | grep "^test[0-9]*$$" | tr "\n" " ") 
	rm -rf *.x *.o
