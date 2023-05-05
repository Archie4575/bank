#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "macros.h"
#include "params.h"
#include "customer.h"

void* customer(void* arg) {
	/* Thread routine to add customers to queue */
	Parameters* params = (Parameters*) arg;
	Queue* queue = params->queue;
	customer_t* customer = NULL;
	int push_sucess = FALSE;

	/* Open customer file */
	FILE* file = fopen(C_FILE, "r");

	if (file == NULL ) {
		perror("Error reading file.");
	} else {
		while(!feof(file)) {
			/* For every line in the file, read into a Customer struct */
			customer = create_customer();
			fscanf(file, "%i %c ", &customer->n, &customer->type);

			/* Sleep for specified time interval */
			sleep(params->tc);

			/* Push customer to Queue */
			push_sucess = FALSE;
			pthread_mutex_lock(&queue->lock);
			while (!push_sucess) {
				if (queue->list->length < params->m) { /* Check Queue has room for one more */
					insertStart(queue->list, customer);
					push_sucess = TRUE;

					/* Unblock a teller to serve the customer by signalling */
					pthread_cond_signal(&queue->new_customer);

					printLinkedList(queue->list, print_customer);
				} else {
					/* Block thread if there is no space */
					pthread_cond_wait(&queue->not_full, &queue->lock);
				}
			}
			pthread_mutex_unlock(&queue->lock);
		}
		/* End of file, no more incoming customer */
		pthread_mutex_lock(&queue->lock);
		queue->incoming = FALSE; /* Set incoming flag to false so tellers terminate */
		pthread_mutex_unlock(&queue->lock);
	}

	return NULL;
}

customer_t* create_customer() {
	customer_t* customer = (customer_t*) malloc(sizeof(customer_t));
	printf("Created customer at %p\n", (void*)customer);
	customer->n = 0;
	customer->type = ' ';
	return customer;
}

void print_customer(void* customer) {
	customer_t* c = (customer_t*)customer;
	printf("#%i: '%c'\n", c->n, c->type);
	return;
}