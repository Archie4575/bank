#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "macros.h"
#include "teller.h"

void* teller(void* arg) {
    /* Thread routine to serve customers in the queue */
    Parameters* params = (Parameters*) arg;
    Queue* queue = params->queue;
    
    while (TRUE) {

        pthread_cond_wait(&queue->new_customer, &queue->lock);
        customer_t* customer = (customer_t*) removeLast(queue->list);

        printf("T: Teller is serving C%i # '%c'\n", customer->n, customer->type);

        pthread_mutex_unlock(&queue->lock);
        pthread_cond_signal(&queue->not_full);

        teller_serve(params, customer);
        free(customer);

        pthread_mutex_lock(&queue->lock);
        if (!queue->incoming) break;

    }
    pthread_mutex_unlock(&queue->lock);
    printf("Teller terminating.\n");

    return NULL;
}

void teller_serve(Parameters* params, customer_t* customer) {
    printf("T: customer %p", (void*) customer);
    switch (customer->type) {
        case 'W':
            printf("T: Customer #%i wants to withdraw money.\n", customer->n);
            sleep(params->tw);
            printf("T: Customer #%i was served.\n", customer->n);
            break;
        case 'D':
            printf("T: Customer #%i wants to deposit money.\n", customer->n);
            sleep(params->td);
            printf("T: Customer #%i was served.\n", customer->n);
            break;
        case 'I':
            printf("T: Customer #%i wants to ask a question about money.\n", customer->n);
            sleep(params->ti);
            printf("T: Customer #%i was served.\n", customer->n);
            break;
        default:
            printf("T: Customer #%i was thrown out of the bank.\n", customer->n);
            break;
    }
}
