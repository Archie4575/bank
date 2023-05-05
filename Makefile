CC = gcc
CFLAGS = -Wall -Werror -pedantic -g
EXEC = cq
OBJ = main.o linkedlist.o customer.o queue.o teller.o params.o

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -pthread -o $(EXEC)

main.o: main.c macros.h linkedlist.h customer.h queue.h teller.h params.h
	$(CC) $(CFLAGS) -pthread -c main.c

customer.o: customer.c customer.h macros.h queue.h params.h
	$(CC) $(CFLAGS) -pthread -c customer.c

params.o: params.c params.h queue.h
	$(CC) $(CFLAGS) -pthread -c params.c

queue.o: queue.c queue.h linkedlist.h
	$(CC) $(CFLAGS) -pthread -c queue.c

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -c linkedlist.c

teller.o: teller.c teller.h macros.h queue.h customer.h params.h
	$(CC) $(CFLAGS) -pthread -c teller.c 

clean:
	rm -f *.o
	rm $(EXEC)