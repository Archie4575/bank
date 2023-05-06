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
    
    pthread_mutex_lock(&queue->lock);
    while (TRUE) {
        /* If no customers in queue, block */
        if (queue->list->length <= 0) {
            pthread_cond_wait(&queue->new_customer, &queue->lock);
        }
        /* Pop last customer from queue and signal not_full */
        customer_t* customer = (customer_t*) removeLast(queue->list);
        pthread_cond_signal(&queue->not_full);
        pthread_mutex_unlock(&queue->lock);

        /* Serve customer */
        printf("T%i: serving C%i%c\n", teller_id, customer->n, customer->type);
        teller_serve(params, teller_id, customer);
        free(customer);

        /* Update total customers served */
        increment_tallies(params, teller_id);

        /* Terminate if there are no more incoming customers */
        pthread_mutex_lock(&queue->lock);
        if (!queue->incoming) break;
    }
    pthread_mutex_unlock(&queue->lock);

    pthread_mutex_lock(&params->queue->lock);
    printf("Teller %i terminating, served %i customers\n", teller_id, params->totals->tallies[teller_id-1]);
    pthread_mutex_unlock(&params->queue->lock);

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