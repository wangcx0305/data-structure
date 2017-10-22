all: prog

prog: bst.o compare.o
	gcc -g -Wall -std=c99 -ansi -o prog bst.o compare.o main.c

compare.o: compare.c structs.h
	gcc -g -Wall -std=c99 -ansi -c  compare.c
		
bst.o: bst.c bst.h
	gcc -g -Wall -std=c99 -ansi -c bst.c

clean:	
	rm bst.o
	rm compare.o
	rm prog
