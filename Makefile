CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic -g
EXEC = cq
OBJ = main.o linkedlist.o customer.o

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c macros.h linkedlist.h customer.h
	$(CC) $(CFLAGS) -pthread -c main.c

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -pthread -c linkedlist.c

customer.o: customer.c customer.h macros.h linkedlist.h
	$(CC) $(CFLAGS) -pthread -c customer.c