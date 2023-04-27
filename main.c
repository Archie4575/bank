#include <stdio.h>
#include <pthread.h>
#include "queue.h"
#include "macros.h"
#include "customer.h"

/* Teller Code */
typedef struct {
	int n; 
	int served;
} teller_t;
/* End of teller code */

int main (int argc, char** argv) {
	Queue* c_queue = createQueue();

	pthread_t customer_th;
	pthread_create(&customer_th, NULL, &customer, c_queue);

	pthread_join(customer_th, NULL);

	return 0;
}

