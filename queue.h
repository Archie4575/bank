#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include "linkedlist.h"

typedef struct {
    LinkedList* list;
    pthread_mutex_t lock;
} Queue;

Queue* createQueue();
void freeQueue(Queue* q, listFunc func);

#endif