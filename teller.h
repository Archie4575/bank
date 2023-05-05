#ifndef TELLER_H
#define TELLER_H

#include "params.h"
#include "customer.h"

void* teller (void* arg);
void teller_serve(Parameters* params, customer_t* customer);

#endif