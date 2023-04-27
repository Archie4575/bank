#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "linkedlist.h"

#define TRUE 1
#define FALSE !TRUE
#define C_FILE "c_file.txt"
#define M 3
#define TC 2

pthread_mutex_t c_queue_lock;

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

int customer_push(LinkedList* c_queue, customer_t* customer) {
	int success = FALSE;
	printf("Trying to push customer ");
	print_customer(customer);
	
	pthread_mutex_lock(&c_queue_lock);
	if (c_queue->length < M) {
		insertLast(c_queue, customer);
		printLinkedList(c_queue, print_customer);
		success = TRUE;
	}

	pthread_mutex_unlock(&c_queue_lock);
	return success;
}


void* customer(void* queue) {
	LinkedList* c_queue = (LinkedList*) queue;
	FILE* file = fopen(C_FILE, "r");
	customer_t* customer = NULL;
	int push_sucess = TRUE;

	if (file == NULL ) {
		perror("Error reading file.");
	} else {
		while(!feof(file)) {
			customer = create_customer();
			fscanf(file, "%i %c", &customer->n, &customer->type);
			sleep(TC);
			push_sucess = customer_push(c_queue, customer);
			while(!push_sucess) {
                sleep(TC);
				push_sucess = customer_push(c_queue, customer);
			}
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

	pthread_mutex_init(&c_queue_lock, NULL);

	pthread_create(&customer_th, NULL, &customer, c_queue);

	pthread_join(customer_th, NULL);

	pthread_mutex_destroy(&c_queue_lock);

	return 0;
}

