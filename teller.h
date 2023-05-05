#ifndef TELLER_H
#define TELLER_H

#include "params.h"
#include "customer.h"

void* teller (void* arg);
void teller_serve(Parameters* params, int teller_id, customer_t* customer);
void increment_tallies(Parameters* params, int teller_id);

#endif