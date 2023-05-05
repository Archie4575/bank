#include <pthread.h>
#include <stdlib.h>
#include "params.h"

TellerTotals* initTellerTotals() {
    TellerTotals* totals = (TellerTotals*) malloc(sizeof(TellerTotals));
    int i;

    totals->num_tellers = 0;
    for (i=0; i<4; i++) {
        totals->tallies[i] = 0;
    }

    pthread_mutex_init(&totals->lock, NULL);

    return totals;
}

void freeTellerTotals(TellerTotals* totals) {
    pthread_mutex_destroy(&totals->lock);
    free(totals);
}