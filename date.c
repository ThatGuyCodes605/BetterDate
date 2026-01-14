/*
 * betterdate - Real-time clock display
 * Copyright (C) 2026 ThatGuyCodes605
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[]) {
    int use_12hour = 0;
    time_t rawtime;
    struct tm *pTime;

    // Hide cursor
    printf("\033[?25l");
    if (argc > 1 && strcmp(argv[1], "-12") == 0) {
    use_12hour = 1;
}
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
        if (use_12hour) {
            int hour = pTime->tm_hour;
            char *am_pm = "AM";
            if (hour >= 12) {
                am_pm = "PM";
            }
            if(hour > 12){
                hour -= 12;
            }
            if(hour == 0){
                hour = 12;
            }   
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d.%03ld %s\n",
                   pTime->tm_mday,
                   pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   hour,
                   pTime->tm_min,
                   pTime->tm_sec,
                   ms,
                   am_pm);
        }
        else {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d.%03ld\n",
                   pTime->tm_mday,
                   pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   pTime->tm_hour,
                   pTime->tm_min,
                   pTime->tm_sec,
                   ms);
        }
        fflush(stdout);
        nanosleep(&(struct timespec){0, 1000000}, NULL);
    }
    // Show cursor again
    printf("\033[?25h");
    fflush(stdout);

    return 0;
}

