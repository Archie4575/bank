#ifndef TELLER_H
#define TELLER_H

#include "customer.h"

typedef struct {
	int n; 
	int served;
} teller_t;

void* teller (void* arg);
void teller_serve(customer_t* customer);

#endif