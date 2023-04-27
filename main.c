#include <stdio.h>
#include <pthread.h>
#include "linkedlist.h"
#include "macros.h"
#include "customer.h"

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

