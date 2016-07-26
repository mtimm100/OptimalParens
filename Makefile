CFLAGS = -g -Wall
CC = gcc

objects = Matrix.o FileIO.o OptimalParensTest.o 

test : $(objects)
	  $(CC) -o test $(objects) 

Matrix.o : Matrix.c Matrix.h FileIO.h
	  gcc -c -Wall Matrix.c
FileIO.o : FileIO.c FileIO.h Matrix.h
	  gcc -c -Wall FileIO.c
OptimalParensTest.o : OptimalParensTest.c Matrix.h FileIO.h 
	  gcc -c -Wall OptimalParensTest.c

.PHONY : clean
clean : 
	  rm test $(objects)
