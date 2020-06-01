CC          =	gcc
# Flags that are sent to the compiler

CFLAGS      =	-Wall -std=c99 -pedantic -g

prog:
	$(CC) $(CFLAGS) src/main.c src/tree.c src/posSystem.c -Iinclude -o bin/runMe

clean:
	rm bin/*