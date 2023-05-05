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
		.queue = queue, 
		.m = atoi(argv[1]), 
		.tc = atoi(argv[2]),
		.tw = atoi(argv[3]),
		.td = atoi(argv[4]),
		.ti = atoi(argv[5]),
		.totals = initTellerTotals()
	};

	pthread_t customer_th;
	pthread_t teller_th[4];
	int i;

	/* Create threads */
	pthread_create(&customer_th, NULL, &customer, &params);
	for (i=0; i<4; i++) {
		pthread_create(&teller_th[i], NULL, &teller, &params);
	}
	
	/* Join threads */
	pthread_join(customer_th, NULL);
	for (i=0; i<4; i++) {
		pthread_join(teller_th[i], NULL);
	}

	freeQueue(queue, &free);
	freeTellerTotals(params.totals);
	return 0;
}

