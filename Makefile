CC = gcc
CFLAGS = -Wall -Werror -pedantic -g
EXEC = cq
OBJ = main.o linkedlist.o customer.o queue.o teller.o

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c macros.h linkedlist.h customer.h queue.h teller.h
	$(CC) $(CFLAGS) -pthread -c main.c

customer.o: customer.c customer.h macros.h queue.h
	$(CC) $(CFLAGS) -pthread -c customer.c

queue.o: queue.c queue.h linkedlist.h
	$(CC) $(CFLAGS) -pthread -c queue.c

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -c linkedlist.c

teller.o: teller.c teller.h macros.h queue.h customer.h
	$(CC) $(CFLAGS) -pthread -c teller.c 

clean:
	rm -f *.o
	rm $(EXEC)