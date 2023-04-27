#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "macros.h"
#include "customer.h"

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

int customer_push(Queue* c_queue, customer_t* customer) {
	int success = FALSE;
	printf("Trying to push customer ");
	print_customer(customer);
	
	pthread_mutex_lock(&c_queue->lock);
	if (c_queue->list->length < M) {
		insertLast(c_queue->list, customer);
		printLinkedList(c_queue->list, print_customer);
		success = TRUE;
	}

	pthread_mutex_unlock(&c_queue->lock);
	return success;
}


void* customer(void* q) {
	Queue* c_queue = (Queue*) q;
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

	printLinkedList(c_queue->list, &print_customer);

	freeQueue(c_queue, &free);
	return NULL;
}