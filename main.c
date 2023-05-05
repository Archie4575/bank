#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "params.h"
#include "macros.h"
#include "customer.h"
#include "teller.h"

int main (int argc, char** argv) {
	Queue* queue = createQueue();
	Parameters params = {
		queue, 
		atoi(argv[1]), /* M */
		atoi(argv[2]), /* tc */
		atoi(argv[3]), /* tw */
		atoi(argv[4]), /* td */
		atoi(argv[5]), /* ti */
	};

	pthread_t customer_th;
	pthread_t teller_th;

	pthread_create(&customer_th, NULL, &customer, &params);
	pthread_create(&teller_th, NULL, &teller, &params);
	
	pthread_join(customer_th, NULL);
	pthread_join(teller_th, NULL);

	freeQueue(queue, &free);
	return 0;
}

