#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    time_t rawtime;
    struct tm *pTime;

    // Hide cursor
    printf("\033[?25l");
    fflush(stdout);

    printf("\n\n");  // reserve 2 lines

    while (1) {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);

        rawtime = ts.tv_sec;
        pTime = localtime(&rawtime);

        long ms = ts.tv_nsec / 1000000;

        // Move cursor up 2 lines to redraw
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
        nanosleep(&(struct timespec){0, 1000000}, NULL);
    }

    // Show cursor again
    printf("\033[?25h");
    fflush(stdout);

    return 0;
}

