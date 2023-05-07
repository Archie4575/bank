#include <pthread.h>
#include <stdlib.h>
#include <time.h>
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

LogFile* openLogFile(char* filename) {
    LogFile* logfile = (LogFile*) malloc(sizeof(LogFile));
    logfile->fd = fopen(filename, "w+");
    setbuf(logfile->fd, NULL);
    
    pthread_mutex_init(&logfile->lock, NULL);

    return logfile;
}

void closeLogFile(LogFile* logfile) {
    fclose(logfile->fd);

    pthread_mutex_destroy(&logfile->lock);

    free(logfile);
}

void getlocaltime(char* timestr) {
    time_t epochtime = time(NULL);
    struct tm local; 
    localtime_r(&epochtime, &local);
    snprintf(timestr, 9, "%02d:%02d:%02d", local.tm_hour, local.tm_min, local.tm_sec);
}