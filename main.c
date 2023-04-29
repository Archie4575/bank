#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "queue.h"
#include "macros.h"
#include "customer.h"
#include "teller.h"

int main (int argc, char** argv) {
	Queue* c_queue = createQueue();

	pthread_t customer_th;
	pthread_t teller_th;
	
	pthread_create(&customer_th, NULL, &customer, c_queue);
	pthread_create(&teller_th, NULL, &teller, c_queue);
	

	pthread_join(customer_th, NULL);
	pthread_join(teller_th, NULL);

	freeQueue(c_queue, &free);
	return 0;
}

