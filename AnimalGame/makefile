all: animal

animal: animal.o compare.o
	gcc -g -Wall -std=c99 -o animal animal.o compare.o

compare.o: compare.c
	gcc -g -Wall -std=c99 -c compare.c
		
animal.o: animal.c bst.h
	gcc -g -Wall -std=c99 -c animal.c

clean:	
	rm animal.o
	rm compare.o
	rm animal
