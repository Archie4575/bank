#ifndef PARAMS_H
#define PARAMS_H
#include <stdio.h>
#include "queue.h"

typedef struct {
	int num_tellers;
    int tallies[4];
    pthread_mutex_t lock;
} TellerTotals;

TellerTotals* initTellerTotals(void);
void freeTellerTotals(TellerTotals* totals);

typedef struct {
    FILE* fd;
    pthread_mutex_t lock;
} LogFile;

LogFile* openLogFile(char* filename);
void closeLogFile(LogFile* log);

typedef struct {
    const int m;
    const int tc;
    const int td;
    const int tw;
    const int ti;
    Queue* queue;
    TellerTotals* totals;
    LogFile* logfile;
} Parameters;

void getlocaltime(char * timestr);

#endif