#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "teller.h"
#include "macros.h"
#include "queue.h"


void teller_serve(customer_t* customer) {
    printf("T: customer %p", (void*) customer);
    switch (customer->type) {
        case 'W':
            printf("T: Customer #%i wants to withdraw money.\n", customer->n);
            sleep(3);
            printf("T: Customer #%i was served.\n", customer->n);
            break;
        case 'D':
            printf("T: Customer #%i wants to deposit money.\n", customer->n);
            sleep(2);
            printf("T: Customer #%i was served.\n", customer->n);
            break;
        case 'I':
            printf("T: Customer #%i wants to ask a question about money.\n", customer->n);
            sleep(1);
            printf("T: Customer #%i was served.\n", customer->n);
            break;
        default:
            printf("T: Customer #%i was thrown out of the bank.\n", customer->n);
            break;
    }
}

void* teller(void* arg) {
    teller_args* targs = (teller_args*) arg;
    Queue* c_queue = targs->c_queue;
    while (TRUE) {
        pthread_mutex_lock(&c_queue->lock);
        if (c_queue->list->length > 0) {
            customer_t* customer = (customer_t*) removeLast(c_queue->list);
            printf("T: Teller is serving C%i # '%c'\n", customer->n, customer->type);
            pthread_mutex_unlock(&c_queue->lock);
            teller_serve(customer);
            free(customer);
        } else {
            pthread_mutex_unlock(&c_queue->lock);
        }
    }
}