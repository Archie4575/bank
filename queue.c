#include <pthread.h>
#include <stdlib.h>
#include "queue.h"
#include "macros.h"

Queue* createQueue() {
    Queue* q = (Queue*) malloc(sizeof(Queue));

    q->list = createLinkedList();
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->not_full, NULL);
    pthread_cond_init(&q->new_customer, NULL);
    q->incoming = TRUE;

    return q;
}

void freeQueue(Queue* q, listFunc func) {
    freeLinkedList(q->list, func);
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->not_full);
    pthread_cond_destroy(&q->new_customer);
}