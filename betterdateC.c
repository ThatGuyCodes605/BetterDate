#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    time_t rawtime;
    struct tm *pTime;

    printf("\n\n");

    while (1) {
        time(&rawtime);
        pTime = localtime(&rawtime);

        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        long ms = ts.tv_nsec / 1000000;

        printf("\033[2A");

        printf("Epoch: %ld\n", rawtime);

        printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d.%03ld\n",
               pTime->tm_mday,
               pTime->tm_mon + 1,
               pTime->tm_year + 1900,
               pTime->tm_hour,
               pTime->tm_min,
               pTime->tm_sec,
               ms);

        fflush(stdout);
    }

    return 0;
}
