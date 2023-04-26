CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic -g
EXEC = cq
OBJ = main.o linkedlist.o

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c
	$(CC) $(CFLAGS) -pthread -c main.c

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -c linkedlist.c