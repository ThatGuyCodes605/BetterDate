# BetterDate  

A simple terminal-based clock written in C that displays:

- **Epoch time** (Unix timestamp) on the first line  
- **Date + time with milliseconds** on the second line  
- Both lines update **in place** without printing new lines  
- Uses ANSI escape codes for cursor control  
- Use -12 for 12 hour time

---

## Example Output

```
Epoch: 1732812345
Date: 28/11/2025 Time: 18:41:13.123
```

The same two lines refresh smoothly.

---

## Features

- Updates continuously without flickering  
- Overwrites the same two lines using ANSI cursor movement  
- Shows milliseconds using `clock_gettime()`  
- Works on any Linux terminal  
- No external dependencies  
- Great intro project for C time functions and terminal control  
- You can use -12 for 12 hour time
---

## Source Code

```
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
```
## Build & Run
Compile:
```
make && sudo make install
```
Run:
```
betterdate
```


If the Library as you received it specifies that a proxy can decide
whether future versions of the GNU Lesser General Public License shall
apply, that proxy's public statement of acceptance of any version is
permanent authorization for you to choose that version for the
Library.

