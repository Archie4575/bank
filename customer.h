#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "queue.h"

typedef struct {
    int n;
    char type;
} customer_t;

customer_t* create_customer();
void print_customer(void* customer);
int customer_push(Queue* c_queue, customer_t* customer);
void* customer(void* queue);

#endif