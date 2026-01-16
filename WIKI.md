# BetterDate Wiki

## Home

**BetterDate** is an improved version of the standard Unix `date` command. It's a feature-rich terminal-based clock written in C that displays real-time updates with configurable precision (milliseconds, microseconds, or nanoseconds), timezone support, customizable date/time formats, and a built-in stopwatch timer.

### Features
- ⏰ Real-time clock with configurable precision (milliseconds, microseconds, nanoseconds)
- 🕐 Both 24-hour (default) and 12-hour format support with AM/PM
- 🌍 Timezone support - view time in any timezone worldwide
- 📅 Unix epoch timestamp display (optional)
- 🇺🇸 US date format support - switch between DD/MM/YYYY and MM/DD/YYYY
- ⏱️ Built-in stopwatch - countdown timer with alarm beeps
- 🎛️ Customizable display - hide seconds, hide milliseconds, show high precision
- 🖥️ Clean, in-place updating display without flickering or scrolling
- ⚡ Efficient - automatically adjusts update rate based on precision level
- 🛑 Graceful exit handling with Ctrl+C
- 🐧 Multi-platform support (Linux, macOS, all BSDs, Windows)
- 📖 No external dependencies

### Platform Support
Works on Linux (full nanosecond precision), macOS (microsecond precision), FreeBSD, OpenBSD, NetBSD, DragonflyBSD, and Windows (via MinGW/Cygwin/MSYS2).

### Example Output

**Default (DD/MM/YYYY, milliseconds):**
```
Epoch: 1737000000
Date: 15/01/2026  Time: 18:41:13.123
```

**US format (MM/DD/YYYY):**
```
Epoch: 1737000000
Date: 01/15/2026  Time: 18:41:13.123
```

**12-hour with no milliseconds:**
```
Epoch: 1737000000
Date: 15/01/2026  Time: 06:41:13 PM
```

**No seconds (HH:MM only):**
```
Epoch: 1737000000
Date: 15/01/2026  Time: 18:41
```

**With nanoseconds:**
```
Epoch: 1737000000
Date: 15/01/2026  Time: 18:41:13.123.456.789
```

**Stopwatch:**
```
Stopwatch started for 5.000000 minutes. Press Ctrl+C to stop.
Time left: 04:59
```

All displays refresh smoothly in place.

---

## Installation

### Quick Install (from source)

```bash
# Clone the repository
git clone https://github.com/ThatGuyCodes605/BetterDate.git
cd BetterDate

# Build and install
make
sudo make install
```

The program will be installed to `/usr/local/bin/betterdate`.

### Uninstall

```bash
cd BetterDate
sudo make uninstall
```

---

## Usage

### Basic Usage

**Default display (24-hour, DD/MM/YYYY, milliseconds, with epoch):**
```bash
betterdate
```

**12-hour format with AM/PM:**
```bash
betterdate -12
```

**US date format (MM/DD/YYYY):**
```bash
betterdate -US
```

**Hide milliseconds:**
```bash
betterdate -NM
```
Output: `Time: 18:41:13`

**Hide seconds:**
```bash
betterdate -NS
```
Output: `Time: 18:41`

**Microseconds precision:**
```bash
betterdate -ms
```
Output: `Time: 18:41:13.123.456`

**Nanoseconds precision:**
```bash
betterdate -ns
```
Output: `Time: 18:41:13.123.456.789`

**Hide epoch timestamp:**
```bash
betterdate -ne
```

**Change timezone:**
```bash
betterdate -tz UTC
betterdate -tz America/New_York
betterdate -tz Europe/London
betterdate -tz Asia/Tokyo
```

**Start stopwatch:**
```bash
betterdate -sw 5      # 5 minutes
betterdate -sw 0.5    # 30 seconds
betterdate -sw 0.1    # 6 seconds
```

**Show help:**
```bash
betterdate -h
betterdate --help
```

**Show version:**
```bash
betterdate -v
betterdate --version
```

### Combining Options

You can combine multiple flags:

```bash
# 12-hour US format with no milliseconds in Tokyo
betterdate -12 -US -NM -tz Asia/Tokyo

# 24-hour UTC with nanoseconds, no epoch
betterdate -tz UTC -ns -ne

# 12-hour format with no seconds
betterdate -12 -NS

# US format with microseconds and no epoch
betterdate -US -ms -ne
```

### Available Flags

| Flag | Description | Example |
|------|-------------|---------|
| `-12` | Use 12-hour format with AM/PM | `betterdate -12` |
| `-ne` | Hide epoch timestamp | `betterdate -ne` |
| `-ms` | Show microseconds (milliseconds + microseconds) | `betterdate -ms` |
| `-ns` | Show nanoseconds (milliseconds + microseconds + nanoseconds) | `betterdate -ns` |
| `-tz <timezone>` | Display time in specified timezone | `betterdate -tz UTC` |
| `-US` | Use US date format (MM/DD/YYYY) | `betterdate -US` |
| `-NM` | Hide milliseconds (No Milliseconds) | `betterdate -NM` |
| `-NS` | Hide seconds (No Seconds) | `betterdate -NS` |
| `-sw <minutes>` | Start stopwatch countdown timer | `betterdate -sw 5` |
| `-h, --help` | Show help message | `betterdate -h` |
| `-v, --version` | Show version information | `betterdate -v` |

### Date Format Options

**Default (DD/MM/YYYY):**
- 15/01/2026 (15th of January, 2026)
- International standard format

**US Format (-US - MM/DD/YYYY):**
- 01/15/2026 (January 15th, 2026)
- Common in United States

### Time Display Options

**Precision Levels:**

- **Default**: Milliseconds only (3 digits after seconds)
  - Format: `HH:MM:SS.mmm`
  - Updates every 1ms with sleep to save CPU

- **Microseconds (-ms)**: Milliseconds + Microseconds (6 digits total)
  - Format: `HH:MM:SS.mmm.uuu`
  - Updates as fast as possible (no sleep)

- **Nanoseconds (-ns)**: Milliseconds + Microseconds + Nanoseconds (9 digits total)
  - Format: `HH:MM:SS.mmm.uuu.nnn`
  - Updates as fast as possible (no sleep)

**Visibility Options:**

- **No Milliseconds (-NM)**: Hide all decimal precision
  - Format: `HH:MM:SS`
  - Shows seconds only

- **No Seconds (-NS)**: Hide seconds and milliseconds
  - Format: `HH:MM`
  - Shows hours and minutes only
  - Updates every minute, minimal CPU usage

**Note:** `-NM` and `-NS` take priority over `-ms` and `-ns` flags.

### Stopwatch Feature

The stopwatch is a countdown timer that accepts time in minutes (supports decimals):

```bash
# Basic usage
betterdate -sw <minutes>

# Examples
betterdate -sw 5        # 5 minutes
betterdate -sw 1.5      # 1 minute 30 seconds
betterdate -sw 0.5      # 30 seconds
betterdate -sw 0.1      # 6 seconds
betterdate -sw 0.0167   # 1 second
```

**Stopwatch behavior:**
- Displays countdown in MM:SS format
- Updates every second
- Beeps 5 times when timer finishes (using system bell)
- Press Ctrl+C to stop early
- Automatically exits after completion

**Example output:**
```
Stopwatch started for 5.000000 minutes. Press Ctrl+C to stop.
Time left: 04:59
Time left: 04:58
Time left: 04:57
...
Time left: 00:01
Time left: 00:00

Stopwatch finished!
[beep beep beep beep beep]
```

### Common Timezones

**Americas:**
- `America/New_York` - Eastern Time
- `America/Chicago` - Central Time
- `America/Denver` - Mountain Time
- `America/Los_Angeles` - Pacific Time
- `America/Sao_Paulo` - Brazil
- `America/Mexico_City` - Mexico

**Europe:**
- `Europe/London` - UK
- `Europe/Paris` - France/CET
- `Europe/Berlin` - Germany
- `Europe/Moscow` - Russia

**Asia:**
- `Asia/Tokyo` - Japan
- `Asia/Shanghai` - China
- `Asia/Dubai` - UAE
- `Asia/Kolkata` - India
- `Asia/Singapore` - Singapore

**Pacific:**
- `Australia/Sydney` - Australia East
- `Pacific/Auckland` - New Zealand

**Other:**
- `UTC` - Universal Coordinated Time

### Exiting the Program
Press `Ctrl+C` to exit. The program will gracefully restore your terminal cursor.

---

## How It Works

### Technical Details

**Time Retrieval:**
- Uses `clock_gettime()` with `CLOCK_REALTIME` for high-precision time
- Provides up to nanosecond resolution on supported platforms
- Calculates milliseconds, microseconds, and nanoseconds from `tv_nsec`

**Display Method:**
- Uses ANSI escape codes to control terminal cursor
- `\033[?25l` - Hides cursor for cleaner display
- `\033[2A` - Moves cursor up 2 lines (with epoch)
- `\033[1A` - Moves cursor up 1 line (without epoch)
- `\033[?25h` - Shows cursor again on exit
- Overwrites same lines for smooth, flicker-free updates

**Time Conversion:**
- Unix epoch: raw timestamp (seconds since January 1, 1970)
- Date formatting:
  - Default: DD/MM/YYYY
  - US format: MM/DD/YYYY (swaps day and month)
- Time precision breakdown:
  - Milliseconds: `tv_nsec / 1000000` (0-999)
  - Microseconds: `(tv_nsec / 1000) % 1000` (0-999)
  - Nanoseconds: `tv_nsec % 1000` (0-999)
- 12-hour conversion handles midnight (0 → 12 AM) and noon (12 → 12 PM)

**Signal Handling:**
- Catches `SIGINT` (Ctrl+C) for graceful shutdown
- `handle_exit()` function ensures cursor is restored before program exits
- Prevents terminal from being left in a corrupted state

**Timezone Support:**
- Uses `setenv("TZ", timezone, 1)` to set timezone
- Calls `tzset()` to apply timezone change
- Only affects the running program, not system settings
- Defaults to system timezone if `-tz` not specified

**Stopwatch Implementation:**
- Uses `time()` for second-level precision
- Calculates elapsed time and remaining time
- Simple countdown display with MM:SS format
- Uses `system("tput bel")` for beep sound (5 times)
- Hides cursor during countdown, restores on exit

**Performance Optimization:**
- Default mode: sleeps 1ms between updates (~0.1% CPU)
- High-precision modes (-ms, -ns): no sleep for maximum update rate (~5-10% CPU)
- No seconds mode (-NS): updates every minute (~0% CPU)
- Automatic adjustment based on precision requirements

---

## Building from Source

### Prerequisites
- GCC or compatible C compiler
- Make
- Unix-like operating system (Linux, macOS, BSD, Windows with MinGW/Cygwin)
- POSIX-compliant C library

### Build Process

1. **Clone the repository:**
   ```bash
   git clone https://github.com/ThatGuyCodes605/BetterDate.git
   cd BetterDate
   ```

2. **Compile:**
   ```bash
   make
   ```

3. **Test locally (without installing):**
   ```bash
   make run
   # or
   ./betterdate
   ```

4. **Install system-wide:**
   ```bash
   sudo make install
   ```

5. **Clean build files:**
   ```bash
   make clean
   ```

### Makefile Targets
- `make` or `make all` - Build the program and show detected platform
- `make install` - Install to `/usr/local/bin` (requires sudo, or doas on OpenBSD)
- `make uninstall` - Remove from system (requires sudo/doas)
- `make clean` - Remove build files
- `make run` - Build and run locally
- `make help` - Show all available commands and platform info

### Platform-Specific Notes

**Linux:**
- Full nanosecond precision support
- Requires `-lrt` flag for real-time library
- Best platform for high-precision timing

**macOS:**
- Microsecond precision (nanoseconds will show as 000)
- No `-lrt` flag needed
- Uses system's built-in time functions

**FreeBSD, NetBSD, DragonflyBSD:**
- Similar to Linux but no `-lrt` needed
- Good precision support

**OpenBSD:**
- Uses `doas` instead of `sudo` for installation
- Security-focused platform

**Windows (MinGW/Cygwin/MSYS2):**
- Limited precision support
- Creates `betterdate.exe`
- Terminal ANSI support may vary

---

## Troubleshooting

### Common Issues

**Problem: Command not found after installation**
- Ensure `/usr/local/bin` is in your PATH
- Check with: `echo $PATH`
- Add to PATH: `export PATH=$PATH:/usr/local/bin`
- Make permanent by adding to `~/.bashrc` or `~/.zshrc`

**Problem: Permission denied during installation**
- Use `sudo make install` (Linux, macOS, most BSDs)
- Use `doas make install` (OpenBSD)

**Problem: Display flickering or not updating smoothly**
- Your terminal may not fully support ANSI escape codes
- Try different terminal emulators (GNOME Terminal, Konsole, iTerm2, Alacritty)
- Ensure `TERM` environment variable is set correctly

**Problem: Nanoseconds always show 000**
- This is expected on macOS - hardware limitation
- macOS provides microsecond precision, not nanosecond
- True nanosecond precision requires Linux
- Microseconds should still be updating correctly

**Problem: Stopwatch doesn't beep**
- Your terminal may not support the bell character
- Check terminal settings for "Terminal bell" or "Audible bell"
- Try a different terminal emulator
- System volume may be muted

**Problem: -NS and -NM don't work with -ns or -ms**
- This is intentional - visibility flags take priority
- `-NS` hides all time precision
- `-NM` hides millisecond precision
- Use either precision flags OR visibility flags, not both

**Problem: Time appears incorrect**
- Check system time: `date`
- Verify timezone: `timedatectl` (Linux) or System Preferences (macOS)
- Sync system clock: `sudo ntpdate pool.ntp.org`

**Problem: Timezone doesn't change**
- Verify timezone name is correct (case-sensitive)
- List available timezones: `ls /usr/share/zoneinfo/`
- Use full path format: `America/New_York` not `EST`

**Problem: High CPU usage**
- This is expected when using `-ms` or `-ns` flags
- These modes update as fast as possible for precision
- Use default mode or `-NM` for lower CPU usage

**Problem: Unknown option error**
- Check that flag is spelled correctly
- Flags are case-sensitive: `-US`, `-NS`, `-NM`
- Use `-h` to see all available options

---

## Usage Examples

### Clock Display Examples

```bash
# Simple 24-hour clock
betterdate

# 12-hour clock in US format
betterdate -12 -US

# UTC time with nanoseconds
betterdate -tz UTC -ns

# Tokyo time, no milliseconds, no epoch
betterdate -tz Asia/Tokyo -NM -ne

# Simple HH:MM display
betterdate -NS -ne

# High precision European time
betterdate -tz Europe/Paris -ns
```

### Stopwatch Examples

```bash
# Pomodoro timer (25 minutes)
betterdate -sw 25

# Short break (5 minutes)
betterdate -sw 5

# Tea timer (3 minutes)
betterdate -sw 3

# Quick timer (30 seconds)
betterdate -sw 0.5

# Precise 10 second timer
betterdate -sw 0.167
```

---

## Performance Notes

### CPU Usage
- **Default mode**: ~0.1% CPU (updates every 1ms with sleep)
- **Microsecond mode (-ms)**: ~5-10% CPU (continuous updates)
- **Nanosecond mode (-ns)**: ~5-10% CPU (continuous updates)
- **No seconds mode (-NS)**: ~0% CPU (updates every minute)
- **Stopwatch mode**: ~0% CPU (updates every second)

### Memory Usage
- Minimal: ~1-2 MB resident memory
- No dynamic memory allocation in main loop
- Fixed-size buffers and stack variables

### Update Rates
- **Default**: 1000 updates/second (1ms interval)
- **-ms/-ns**: Limited only by system scheduler (~10,000+ updates/second)
- **-NS**: 1 update/minute
- **Stopwatch**: 1 update/second

---

## Contributing

### How to Contribute

1. **Fork the repository** on GitHub
2. **Create a feature branch:**
   ```bash
   git checkout -b feature-name
   ```
3. **Make your changes** and test thoroughly
4. **Commit your changes:**
   ```bash
   git commit -m "Add feature description"
   ```
5. **Push to your fork:**
   ```bash
   git push origin feature-name
   ```
6. **Submit a Pull Request** on GitHub

### Code Style Guidelines
- Use clear, descriptive variable names
- Add comments for complex logic
- Follow existing code formatting and indentation
- Keep code beginner-friendly (this is a learning project!)
- Test on multiple platforms if possible

### Reporting Bugs
Open an issue on GitHub with:
- Description of the problem
- Steps to reproduce
- Expected vs actual behavior
- System information (OS, distribution, kernel version, terminal emulator)
- Command used and output received
- Output of `make help` showing detected platform

### Feature Requests
Open an issue on GitHub describing:
- The feature you'd like to see
- Why it would be useful
- How you envision it working
- Whether you'd be willing to implement it yourself

### Good First Issues
Looking to contribute but not sure where to start? Some ideas:
- Add support for ISO 8601 date format (YYYY-MM-DD)
- Add color customization options
- Add option to show day of week
- Improve stopwatch with hours support
- Add alarm feature (beep at specific time)
- Add support for displaying multiple timezones simultaneously
- Write additional documentation or examples
- Add configuration file support

---

## Why BetterDate?

BetterDate is a great project for learning:
- **C programming basics** - time functions, command-line arguments, loops, signal handling
- **Terminal control** - ANSI escape codes for cursor manipulation
- **POSIX functions** - `clock_gettime()`, `nanosleep()`, `localtime()`, `setenv()`
- **Build systems** - Cross-platform Makefiles with conditional compilation
- **System programming** - Working with timestamps, signals, and real-time display
- **Precision timing** - Understanding nanoseconds, microseconds, and milliseconds
- **User interface design** - Creating clean, intuitive command-line interfaces

The code is intentionally kept simple and readable, making it perfect for beginners to study and modify while still being useful for daily use.

---

## License

BetterDate - An improved version of the date command for Unix  
Copyright (C) 2026 ThatGuyCodes605

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/

---

## Acknowledgments

- Built with C and Make
- Uses POSIX real-time extensions
- Inspired by the classic Unix `date` command
- Created as a learning project for C programming and terminal control
- Thanks to all contributors and users!

---

## Support

If you encounter any issues or have questions:
- Open an issue on GitHub
- Check the troubleshooting section above
- Review existing issues to see if your problem has been addressed
- Use `-h` flag to see all available options

For general C programming questions or terminal control help, consider:
- Stack Overflow
- The C Programming subreddit
- Linux/BSD terminal emulator documentation

---

## Fun Facts

- The program can display time down to the nanosecond (0.000000001 seconds)
- On Linux, it can update over 10,000 times per second in high-precision mode
- The entire program is under 400 lines of C code
- Works on 7+ different operating systems with one Makefile
- Can display any timezone in the world without changing system settings
- The stopwatch accepts fractional minutes (e.g., 0.1 minutes = 6 seconds)
- Supports both international (DD/MM/YYYY) and US (MM/DD/YYYY) date formats