#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include "linkedlist.h"

typedef struct {
    LinkedList* list;
    pthread_mutex_t lock;
    pthread_cond_t cond_nonempty;
} Queue;

Queue* createQueue();
void freeQueue(Queue* q, listFunc func);

#endif