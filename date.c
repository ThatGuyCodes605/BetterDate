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
#include <signal.h>
#include <stdlib.h>
void handle_exit(int sig) {
    (void)sig;  // Suppress unused parameter warning
    // Show cursor
    printf("\033[?25h");
    fflush(stdout);
    exit(0);
}
void start_stopwatch(double minutes){
    time_t start = time(NULL);
    time_t end;
    time_t total_seconds = minutes * 60;
    printf("Stopwatch started for %lf minutes. Press Ctrl+C to stop.\n", minutes);
    while (1) {
        end = time(NULL);
        fflush(stdout);
        printf("time left: %02ld:%02ld\r", (total_seconds - (end - start)) / 60, (total_seconds - (end - start)) % 60);
        if ((end - start) >= total_seconds) {
            printf("\nStopwatch finished!\n");
            system("tput bel");
            sleep(1);
            system("tput bel");
            sleep(1);
            system("tput bel");
            sleep(1);
            system("tput bel");
            sleep(1);
            system("tput bel");
            sleep(1);
            printf("\033[?25h");
            fflush(stdout);
            break;
        }
        sleep(1);
    }
}
int main(int argc, char *argv[]) {
    int use_12hour = 0;
    int show_epoch = 1;
    int show_ns = 0;
    int show_ms = 0;
    int use_us_date = 0;      
    int hide_milliseconds = 0; 
    int hide_seconds = 0;
    char *timezone = NULL;
    time_t rawtime;
    struct tm *pTime;
    // Set up signal handler for Ctrl+C
    signal(SIGINT, handle_exit);

    // Hide cursor
    printf("\033[?25l");

    for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-12") == 0) {
        use_12hour = 1;
    } else if (strcmp(argv[i], "-ne") == 0) {
        show_epoch = 0;
    } else if (strcmp(argv[i], "-ns") == 0) {
        show_ns = 1;
    } else if (strcmp(argv[i], "-ms") == 0) {
        show_ms = 1;
    } else if (strcmp(argv[i], "-tz") == 0) {
        if (i + 1 < argc) {
            timezone = argv[i + 1];
            i++;
        }
    } else if (strcmp(argv[i], "-sw") == 0 && i + 1 < argc) {
        double minutes = atof(argv[i + 1]);
        start_stopwatch(minutes);
        printf("\033[?25h");  // Show cursor after stopwatch
        fflush(stdout);
        return 0;
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
        printf("Usage: betterdate [options]\n");
        printf("Options:\n");
        printf("  -12           Use 12-hour time format\n");
        printf("  -ne           Do not show epoch time\n");
        printf("  -ns           Show nanoseconds\n");
        printf("  -ms           Show milliseconds and microseconds\n");
        printf("  -tz <zone>    Set timezone (e.g., 'UTC', 'America/New_York')\n");
        printf("  -sw <minutes> Start a stopwatch for the specified number of minutes\n");
        printf("  -US           Use US date format (MM/DD/YYYY)\n");
        printf("  -NM           Hide milliseconds\n");
        printf("  -NS           Hide seconds\n");
        printf("  -h, --help    Show this help message\n");
        printf("  -v, --version Show version information\n");
        printf("\033[?25h");  // Show cursor
        fflush(stdout);
        return 0;
    } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
        printf("betterdate version 1.6\n");
        printf("Copyright (C) 2026 ThatGuyCodes605\n");
        printf("This program comes with ABSOLUTELY NO WARRANTY.\n");
        printf("This is free software, and you are welcome to redistribute it\n");
        printf("under certain conditions. See the GPL-3.0 license for details.\n");
        printf("\033[?25h");  // Show cursor
        fflush(stdout);
        return 0;
    } else if (strcmp(argv[i], "-US") == 0) {
        use_us_date = 1;
    } else if (strcmp(argv[i], "-NM") == 0) {
        hide_milliseconds = 1;
    } else if (strcmp(argv[i], "-NS") == 0) {
        hide_seconds = 1;
    } else {
        printf("Unknown option: %s\n", argv[i]);
        printf("Use -h or --help for usage information.\n");
        printf("\033[?25h");  // Show cursor
        fflush(stdout);
        return 1;
    }
}
     
    if (timezone != NULL) {
    setenv("TZ", timezone, 1);
    tzset();
}
    fflush(stdout);
    int IsRunning = 1;
    printf(show_epoch ? "\n\n" : "\n");

    while (IsRunning) {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);

        rawtime = ts.tv_sec;
        pTime = localtime(&rawtime);

        long ms = ts.tv_nsec / 1000000;
        long us = (ts.tv_nsec / 1000) % 1000;
        long ns = ts.tv_nsec % 1000;
        printf(show_epoch ? "\033[2A" : "\033[1A");
        
        if (show_epoch) {
           printf("Epoch: %ld\n", rawtime);
        }
        
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
    
    if (show_ns) {
        if (hide_seconds) {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d %s\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   hour,
                   pTime->tm_min,
                   am_pm);
        } else if (hide_milliseconds) {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d %s\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   hour,
                   pTime->tm_min,
                   pTime->tm_sec,
                   am_pm);
        } else {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d.%03ld.%03ld.%03ld %s\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   hour,
                   pTime->tm_min,
                   pTime->tm_sec,
                   ms,
                   us,
                   ns,
                   am_pm);
        }
    } else if (show_ms) {
        if (hide_seconds) {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d %s\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   hour,
                   pTime->tm_min,
                   am_pm);
        } else if (hide_milliseconds) {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d %s\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   hour,
                   pTime->tm_min,
                   pTime->tm_sec,
                   am_pm);
        } else {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d.%03ld.%03ld %s\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   hour,
                   pTime->tm_min,
                   pTime->tm_sec,
                   ms,
                   us,
                   am_pm);
        }
    } else {
        if (hide_seconds) {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d %s\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   hour,
                   pTime->tm_min,
                   am_pm);
        } else if (hide_milliseconds) {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d %s\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   hour,
                   pTime->tm_min,
                   pTime->tm_sec,
                   am_pm);
        } else {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d.%03ld %s\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   hour,
                   pTime->tm_min,
                   pTime->tm_sec,
                   ms,
                   am_pm);
        }
    }
}
else {
    if (show_ns) {
        if (hide_seconds) {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   pTime->tm_hour,
                   pTime->tm_min);
        } else if (hide_milliseconds) {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   pTime->tm_hour,
                   pTime->tm_min,
                   pTime->tm_sec);
        } else {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d.%03ld.%03ld.%03ld\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   pTime->tm_hour,
                   pTime->tm_min,
                   pTime->tm_sec,
                   ms,
                   us,
                   ns);
        }
    } else if (show_ms) {
        if (hide_seconds) {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   pTime->tm_hour,
                   pTime->tm_min);
        } else if (hide_milliseconds) {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   pTime->tm_hour,
                   pTime->tm_min,
                   pTime->tm_sec);
        } else {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d.%03ld.%03ld\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   pTime->tm_hour,
                   pTime->tm_min,
                   pTime->tm_sec,
                   ms,
                   us);
        }
    } else {
        if (hide_seconds) {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   pTime->tm_hour,
                   pTime->tm_min);
        } else if (hide_milliseconds) {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   pTime->tm_hour,
                   pTime->tm_min,
                   pTime->tm_sec);
        } else {
            printf("Date: %02d/%02d/%d  Time: %02d:%02d:%02d.%03ld\n",
                   use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                   use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                   pTime->tm_year + 1900,
                   pTime->tm_hour,
                   pTime->tm_min,
                   pTime->tm_sec,
                   ms);
        }
    }
}
 
        fflush(stdout);
        
        // Only sleep if not showing high precision time
        if (!show_ns && !show_ms) {
            nanosleep(&(struct timespec){0, 1000000}, NULL);
        }
    }
    
    // Show cursor again
    printf("\033[?25h");
    fflush(stdout);
    return 0;
}
