#ifndef PARAMS_H
#define PARAMS_H
#include "queue.h"

typedef struct {
    Queue* queue;
    const int m;
    const int tc;
    const int td;
    const int tw;
    const int ti;
} Parameters;

#endif