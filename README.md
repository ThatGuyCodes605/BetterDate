# BetterDate                                                                                                                                           


<img width="136" height="68" alt="gplv3-with-text-136x68" src="https://github.com/user-attachments/assets/32759ed1-1c55-4ce9-ac0d-9a6980ddb2f2" />


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

