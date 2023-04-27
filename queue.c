#include <stdlib.h>
#include "queue.h"

Queue* createQueue() {
    Queue* q = (Queue*) malloc(sizeof(Queue));

    q->list = createLinkedList();
    pthread_mutex_init(&q->lock, NULL);

    return q;
}

void freeQueue(Queue* q, listFunc func) {
    freeLinkedList(q->list, func);
    pthread_mutex_destroy(&q->lock);
}