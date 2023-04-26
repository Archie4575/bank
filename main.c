#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "linkedlist.h"

#define C_FILE "c_file.txt"

/* Customer Code */
typedef struct {
    int n;
    char type;
} customer_t;

customer_t* create_customer() {
	customer_t* customer = (customer_t*) malloc(sizeof(customer_t));
	customer->n = 0;
	customer->type = ' ';
	return customer;
}

void print_customer(void* customer) {
	customer_t* c = (customer_t*)customer;
	printf("#%i: '%c'\n", c->n, c->type);
	return;
}

void* customer(void* queue) {
	LinkedList* c_queue = (LinkedList*) queue;
	FILE* file = fopen(C_FILE, "r");
	customer_t* customer = NULL;

	if (file == NULL ) {
		perror("Error reading file.");
	} else {
		while(!feof(file)) {
			customer = create_customer();
			fscanf(file, "%i %c", &customer->n, &customer->type);
			insertLast(c_queue, customer);
		}
	}

	printLinkedList(c_queue, &print_customer);

	freeLinkedList(c_queue, &free);
	return NULL;
}
/* End of customer code */

/* Teller Code */
typedef struct {
	int n; /* Teller number */
	int served; /* Customers served tally */
} teller_t;
/* End of teller code */

int main (int argc, char** argv) {
	LinkedList* c_queue = createLinkedList();

	pthread_t customer_th;
	pthread_create(&customer_th, NULL, &customer, c_queue);


	pthread_join(customer_th, NULL);

	return 0;
}

