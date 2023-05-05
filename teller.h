#ifndef TELLER_H
#define TELLER_H

#include <pthread.h>
#include "customer.h"

typedef struct {
	Queue* c_queue;
	int** teller_tallies;
} teller_args;

void* teller (void* arg);
void teller_serve(customer_t* customer);

#endif