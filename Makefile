all: prog
	

main.o: main2.c
			gcc -c -o main.o main2.c
automat.o: automat.c
			gcc -c -o automat.o automat.c
prog: main.o automat.o
			gcc -Wall -o prog main.o automat.o

