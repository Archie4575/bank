CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic -g
EXEC = cq
OBJ = main.o

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c
	$(CC) $(CFLAGS) -pthread -c main.c