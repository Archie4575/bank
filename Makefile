CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic -g
EXEC = cq
OBJ = main.o linkedlist.o customer.o queue.o

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c macros.h linkedlist.h customer.h queue.h
	$(CC) $(CFLAGS) -pthread -c main.c

customer.o: customer.c customer.h macros.h queue.h
	$(CC) $(CFLAGS) -pthread -c customer.c

queue.o: queue.c queue.h linkedlist.h
	$(CC) $(CFLAGS) -pthread -c queue.c

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -c linkedlist.c