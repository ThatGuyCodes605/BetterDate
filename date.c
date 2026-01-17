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
void start_countdown(char *datetime_str) {
    struct tm target_time = {0};

    // Parse YYYY-MM-DD HH:MM:SS format
    if (sscanf(datetime_str, "%d-%d-%d %d:%d:%d",
               &target_time.tm_year, &target_time.tm_mon, &target_time.tm_mday,
               &target_time.tm_hour, &target_time.tm_min, &target_time.tm_sec) != 6) {
        printf("Invalid format. Use: YYYY-MM-DD HH:MM:SS (e.g., 2026-12-31 23:59:59)\n");
        printf("\033[?25h");
        return;
    }

    // Adjust for tm structure
    target_time.tm_year -= 1900;  // Years since 1900
    target_time.tm_mon -= 1;       // Months are 0-11
    target_time.tm_isdst = -1;     // Auto detect DST

    time_t target = mktime(&target_time);

    if (target == -1) {
        printf("Invalid date/time.\n");
        printf("\033[?25h");
        return;
    }

    printf("\033[?25l");  // Hide cursor
    printf("Counting down to %s\n", datetime_str);
    printf("Press Ctrl+C to stop.\n\n");

    while (1) {
        time_t now = time(NULL);
        double diff = difftime(target, now);

        if (diff <= 0) {
            printf("\r🎉 Time reached!                              \n");
            for (int i = 0; i < 5; i++) {
                system("tput bel");
                sleep(1);
            }
            printf("\033[?25h");
            fflush(stdout);
            break;
        }

        long total_seconds = (long)diff;
        long days = total_seconds / 86400;
        long hours = (total_seconds % 86400) / 3600;
        long minutes = (total_seconds % 3600) / 60;
        long seconds = total_seconds % 60;

        printf("\rTime remaining: %ld days, %02ld:%02ld:%02ld", days, hours, minutes, seconds);
        fflush(stdout);
        sleep(1);
    }
}
void print_binary(int num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

const char *day_names[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char *day_abbrev[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
void print_datetime(struct tm *pTime, int hour, int use_12hour, char *am_pm,
                    long ms, long us, long ns,
                    int use_us_date, int hide_date, int hide_seconds,
                    int hide_milliseconds, int show_ms, int show_ns, int show_day_name, 
                    int show_day_abbrev, int use_iso_date, char date_separator) {
    // Print day of the week (if requested)
    if (show_day_name) {
        printf("%s ", day_names[pTime->tm_wday]);
    } else if (show_day_abbrev) {
        printf("%s ", day_abbrev[pTime->tm_wday]);
    }
    // Print date (if not hidden)
    if (!hide_date && !use_iso_date) {
        printf("Date: %02d%c%02d%c%d  ",
               use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                date_separator,
               use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                date_separator,
               pTime->tm_year + 1900);
    }
    if (!hide_date && use_iso_date) {
        printf("Date: %d%c%02d%c%02d  ",
               pTime->tm_year + 1900,
               date_separator,
               pTime->tm_mon + 1,
               date_separator,
               pTime->tm_mday);
    
    }


    // Print time label
    printf("Time: ");

    // Print hours and minutes
    printf("%02d:%02d", hour, pTime->tm_min);

    // Print seconds (if not hidden)
    if (!hide_seconds) {
        printf(":%02d", pTime->tm_sec);

        // Print precision (if seconds are shown and milliseconds not hidden)
        if (!hide_milliseconds) {
            if (show_ns) {
                printf(".%03ld.%03ld.%03ld", ms, us, ns);
            } else if (show_ms) {
                printf(".%03ld.%03ld", ms, us);
            } else {
                printf(".%03ld", ms);
            }
        }
    }

    // Print AM/PM for 12-hour format
    if (use_12hour) {
        printf(" %s", am_pm);
    }

    printf("\n");
}
void handle_exit(int sig) {
    (void)sig;  // Suppress unused parameter warning
    // Show cursor
    printf("\033[?25h");
    fflush(stdout);
    exit(0);
}
void start_stopwatch(){
    time_t start = time(NULL);
    time_t end;
    
    printf("\033[?25l");  // Hide cursor
    printf("Stopwatch started. Press Ctrl+C to stop.\n");
    
    while (1) {
        end = time(NULL);
        time_t elapsed = end - start;
        
        long hours = elapsed / 3600;
        long minutes = (elapsed % 3600) / 60;
        long seconds = elapsed % 60;
        
        printf("\rElapsed time: %02ld:%02ld:%02ld", hours, minutes, seconds);
        fflush(stdout);
        sleep(1);
    }
}

void start_alarm(char *time_str) {
    int target_hours = 0, target_minutes = 0, target_seconds = 0;
    
    // Parse HH:MM:SS format
    sscanf(time_str, "%d:%d:%d", &target_hours, &target_minutes, &target_seconds);
    
    time_t total_seconds = (target_hours * 3600) + (target_minutes * 60) + target_seconds;
    
    if (total_seconds <= 0) {
        printf("Invalid time format. Use HH:MM:SS (e.g., 01:30:00 for 1 hour 30 minutes)\n");
        printf("\033[?25h");
        return;
    }
    
    time_t start = time(NULL);
    time_t end;
    
    printf("\033[?25l");  // Hide cursor
    printf("Alarm set for %02d:%02d:%02d. Press Ctrl+C to cancel.\n", 
           target_hours, target_minutes, target_seconds);
    
    while (1) {
        end = time(NULL);
        time_t elapsed = end - start;
        time_t remaining = total_seconds - elapsed;
        
        if (remaining <= 0) {
            printf("\rAlarm finished!                    \n");
            for (int i = 0; i < 5; i++) {
                system("tput bel");
                sleep(1);
            }
            printf("\033[?25h");
            fflush(stdout);
            break;
        }
        
        long hours = remaining / 3600;
        long minutes = (remaining % 3600) / 60;
        long seconds = remaining % 60;
        
        printf("\rTime remaining: %02ld:%02ld:%02ld", hours, minutes, seconds);
        fflush(stdout);
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
    int hide_date = 0;
    int show_day_name = 0;      
    int show_day_abbrev = 0;
    int use_iso_date = 0;
    char date_separator = '/';  // Default date separator
    int show_binary = 0;
    int show_hex = 0;
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
    } else if (strcmp(argv[i], "-NE") == 0) {
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
    } else if (strcmp(argv[i], "-sw") == 0) {
        start_stopwatch();
        printf("\033[?25h");  // Show cursor after stopwatch
        fflush(stdout);
        return 0;
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
        printf("Usage: betterdate [options]\n");
        printf("Options:\n");
        printf("  -12           Use 12-hour time format\n");
        printf("  -NE           Do not show epoch time\n");
        printf("  -ns           Show nanoseconds\n");
        printf("  -ms           Show milliseconds and microseconds\n");
        printf("  -tz <zone>    Set timezone (e.g., 'UTC', 'America/New_York')\n");
        printf("  -sw           Start stopwatch mode\n");
        printf("  -al <HH:MM:SS> Set an alarm for the specified time\n");
        printf("  -US           Use US date format (MM/DD/YYYY)\n");
        printf("  -NM           Hide milliseconds\n");
        printf("  -NS           Hide seconds\n");
        printf("  -ND           Hide date\n");
        printf("  -dw           Show day of the week (full name)\n");
        printf("  -DW           Show day of the week (abbreviated)\n");
        printf("  -iso          Use ISO date format (YYYY-MM-DD)\n");
        printf("  -ds <char>    Set date separator character (default is '/')\n");
        printf("  -bin          Show time in binary format\n");
        printf("  -hex          Show time in hexadecimal format\n");
        printf("  -cd <YYYY-MM-DD HH:MM:SS> Start countdown to specified date/time\n");
        printf("  -h, --help    Show this help message\n");
        printf("  -v, --version Show version information\n");
        printf("\033[?25h");  // Show cursor
        fflush(stdout);
        return 0;
    } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
        printf("betterdate version 1.8\n");
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
    } 
    else if (strcmp(argv[i], "-ND") == 0) {  
        hide_date = 1;
    }
    else if (strcmp(argv[i], "-dw") == 0) {
    show_day_name = 1;
    } else if (strcmp(argv[i], "-DW") == 0) {
         show_day_abbrev = 1;
    }
    else if (strcmp(argv[i], "-iso") == 0) {
        use_iso_date = 1;
    }
    else if (strcmp(argv[i], "-ds") == 0) {
        if (i + 1 < argc) {
            date_separator = argv[i + 1][0];
            i++;
        }
    }
    else if (strcmp(argv[i], "-bin") == 0) {
        show_binary = 1;
    }
    else if (strcmp(argv[i], "-hex") == 0) {
        show_hex = 1;
    
    }
    else if (strcmp(argv[i], "-al") == 0) {
        if (i + 1 < argc) {
            start_alarm(argv[i + 1]);
            printf("\033[?25h");  // Show cursor after alarm
            fflush(stdout);
            return 0;
        } else {
            printf("Error: No time specified for alarm.\n");
            printf("\033[?25h");  // Show cursor
            fflush(stdout);
            return 1;
        }
    
    }
    else if (strcmp(argv[i], "-cd") == 0) {
        if (i + 1 < argc) {
            start_countdown(argv[i + 1]);
            printf("\033[?25h");  // Show cursor after countdown
            fflush(stdout);
            return 0;
        } else {
            printf("Error: No date/time specified for countdown.\n");
            printf("\033[?25h");  // Show cursor
            fflush(stdout);
            return 1;
        }
    
    }
    else {
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
        
        if (show_epoch && !show_binary && !show_hex) {
           printf("Epoch: %ld\n", rawtime);
        }
        
        int hour = pTime->tm_hour;
        char *am_pm = "";

        if (use_12hour) {
            am_pm = (pTime->tm_hour >= 12) ? "PM" : "AM";
            if (hour > 12) {
                hour -= 12;
            } else if (hour == 0) {
                hour = 12;
            }
        }
                if (show_binary) {
            if (show_epoch) {
                printf("Epoch in Binary: ");
                for (int i = 31; i >= 0; i--) {
                    printf("%ld", (rawtime >> i) & 1);
                    if (i % 8 == 0 && i != 0) printf(" ");
                }
                printf("\n");
            }
            
            if (!hide_date) {
                int day = use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday;
                int month = use_us_date ? pTime->tm_mday : pTime->tm_mon + 1;
                int year = pTime->tm_year + 1900;
                
                if (use_iso_date) {
                    day = pTime->tm_mday;
                    month = pTime->tm_mon + 1;
                    year = pTime->tm_year + 1900;
                    printf("Date: ");
                    for (int i = 15; i >= 0; i--) printf("%d", (year >> i) & 1);
                    printf("%c", date_separator);
                    print_binary(month);
                    printf("%c", date_separator);
                    print_binary(day);
                    printf("  ");
                } else {
                    printf("Date: ");
                    print_binary(day);
                    printf("%c", date_separator);
                    print_binary(month);
                    printf("%c", date_separator);
                    for (int i = 15; i >= 0; i--) printf("%d", (year >> i) & 1);
                    printf("  ");
                }
            }
            
            printf("Binary Time: ");
            print_binary(hour);
            printf(":");
            print_binary(pTime->tm_min);
            if (!hide_seconds || show_ns) {
                printf(":");
                print_binary(pTime->tm_sec);
                if (!hide_milliseconds || show_ns) {
                    printf(".");
                    for (int i = 9; i >= 0; i--) printf("%ld", (ms >> i) & 1);
                    if (show_ms || show_ns) {
                        printf(".");
                        for (int i = 9; i >= 0; i--) printf("%ld", (us >> i) & 1);
                    }
                    if (show_ns) {
                        printf(".");
                        for (int i = 9; i >= 0; i--) printf("%ld", (ns >> i) & 1);
                    }
                }
            }
            if (use_12hour) {
                printf(" %s", am_pm);
            }
            printf("\n");
        } else if (show_hex) {
            if (show_epoch) {
                printf("Epoch in Hex: %lX\n", rawtime);
            }
            
            if (!hide_date) {
                if (use_iso_date) {
                    printf("Date: %04X%c%02X%c%02X  ",
                           pTime->tm_year + 1900,
                           date_separator,
                           pTime->tm_mon + 1,
                           date_separator,
                           pTime->tm_mday);
                } else {
                    printf("Date: %02X%c%02X%c%04X  ",
                           use_us_date ? pTime->tm_mon + 1 : pTime->tm_mday,
                           date_separator,
                           use_us_date ? pTime->tm_mday : pTime->tm_mon + 1,
                           date_separator,
                           pTime->tm_year + 1900);
                }
            }
            
            printf("Hex Time: %02X:%02X", hour, pTime->tm_min);
            if (!hide_seconds || show_ns) {
                printf(":%02X", pTime->tm_sec);
                if (!hide_milliseconds || show_ns) {
                    printf(".%03lX", ms);
                    if (show_ms || show_ns) {
                        printf(".%03lX", us);
                    }
                    if (show_ns) {
                        printf(".%03lX", ns);
                    }
                }
            }
            if (use_12hour) {
                printf(" %s", am_pm);
            }
            printf("\n");
        } else {
            print_datetime(pTime, hour, use_12hour, am_pm, ms, us, ns,
                          use_us_date, hide_date, hide_seconds, 
                          hide_milliseconds, show_ms, show_ns,
                          show_day_name, show_day_abbrev, use_iso_date, date_separator);
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
