#ifndef PARAMS_H
#define PARAMS_H
#include "queue.h"

typedef struct {
	int num_tellers;
    int tallies[4];
    pthread_mutex_t lock;
} TellerTotals;

TellerTotals* initTellerTotals(void);
void freeTellerTotals(TellerTotals* totals);

typedef struct {
    Queue* queue;
    const int m;
    const int tc;
    const int td;
    const int tw;
    const int ti;
    TellerTotals* totals;
} Parameters;


#endif