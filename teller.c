#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "macros.h"
#include "params.h"
#include "teller.h"

void* teller(void* arg) {
    /* Thread routine to serve customers in the queue */
    Parameters* params = (Parameters*) arg;
    Queue* queue = params->queue;
    int teller_id = 0;
    pthread_mutex_lock(&params->totals->lock);
    if (params->totals->num_tellers < 4) {
        params->totals->num_tellers++;
        teller_id = params->totals->num_tellers;
        pthread_mutex_unlock(&params->totals->lock);
    } else {
        pthread_mutex_unlock(&params->totals->lock);
        printf("Too many tellers already.\n");
        return NULL;
    }
    
    
    while (TRUE) {

        pthread_cond_wait(&queue->new_customer, &queue->lock);
        customer_t* customer = (customer_t*) removeLast(queue->list);

        printf("T%i: serving C%i%c\n", teller_id, customer->n, customer->type);

        pthread_mutex_unlock(&queue->lock);
        pthread_cond_signal(&queue->not_full);

        teller_serve(params, teller_id, customer);
        free(customer);

        increment_tallies(params, teller_id);

        pthread_mutex_lock(&queue->lock);
        if (!queue->incoming) break;

    }
    pthread_mutex_unlock(&queue->lock);
    printf("Teller %i terminating.\n", teller_id);

    return NULL;
}

void teller_serve(Parameters* params, int teller_id, customer_t* customer) {
    switch (customer->type) {
        case 'W':
            printf("T%i: Customer #%i wants to withdraw money.\n", teller_id, customer->n);
            sleep(params->tw);
            printf("T%i: Customer #%i was served.\n", teller_id, customer->n);
            break;
        case 'D':
            printf("T%i: Customer #%i wants to deposit money.\n", teller_id, customer->n);
            sleep(params->td);
            printf("T%i: Customer #%i was served.\n", teller_id, customer->n);
            break;
        case 'I':
            printf("T%i: Customer #%i wants to ask a question about money.\n", teller_id, customer->n);
            sleep(params->ti);
            printf("T%i: Customer #%i was served.\n", teller_id, customer->n);
            break;
        default:
            printf("T%i: Customer #%i was thrown out of the bank.\n", teller_id, customer->n);
    }
}

void increment_tallies(Parameters* params, int teller_id) {
    pthread_mutex_unlock(&params->totals->lock);
    params->totals->tallies[teller_id - 1] += 1;
    pthread_mutex_lock(&params->totals->lock);
}