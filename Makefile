all: prog

prog: main.o automat.o
	gcc -Wall main.o automat.o -o prog
	
main.o: main2.c
	gcc -Wall -c main2.c -o main.o

automat.o: automat.c
	gcc -Wall -c automat.c -o automat.o

.PHONY: clean
clean:
	rm -rf *.o

