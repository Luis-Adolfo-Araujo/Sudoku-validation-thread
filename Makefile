CC=gcc
all: main

main: sudoku.c
	$(CC) -o sudoku sudoku.c

clean:
	rm -f sudoku