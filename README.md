# BetterDate

A feature-rich terminal-based clock written in C that displays real-time date, time, and Unix epoch with customizable precision, timezone support, and a built-in stopwatch.

---

## Example Output

**Default (milliseconds):**
```
Epoch: 1737000000
Date: 15/01/2026  Time: 18:41:13.123
```

**US date format (-US):**
```
Epoch: 1737000000
Date: 01/15/2026  Time: 18:41:13.123
```

**Time only (-ND):**
```
Time: 18:41:13.123
```

**12-hour format with no milliseconds (-12 -NM):**
```
Epoch: 1737000000
Date: 15/01/2026  Time: 06:41:13 PM
```

**No seconds (-NS):**
```
Epoch: 1737000000
Date: 15/01/2026  Time: 18:41
```

**With nanoseconds (-ns):**
```
Epoch: 1737000000
Date: 15/01/2026  Time: 18:41:13.123.456.789
```

**Stopwatch mode (-sw 0.5):**
```
Stopwatch started for 0.500000 minutes. Press Ctrl+C to stop.
Time left: 00:29
```

All displays update smoothly in place without scrolling.

---

## Features

* ⏰ **Real-time clock** with configurable precision (milliseconds, microseconds, or nanoseconds)
* 🕐 **12-hour or 24-hour format** with AM/PM display
* 🌍 **Timezone support** - view time in any timezone
* 📅 **Unix epoch timestamp** display (optional)
* 🇺🇸 **US date format** - switch between DD/MM/YYYY and MM/DD/YYYY
* ⏱️ **Built-in stopwatch** - countdown timer with alarm
* 🎛️ **Customizable display** - hide date, epoch, seconds, or milliseconds
* 🖥️ **Clean in-place updates** using ANSI escape codes - no flickering or scrolling
* ⚡ **Efficient** - automatically adjusts update rate based on precision level
* 🛑 **Graceful exit** - Ctrl+C properly restores cursor
* 🐧 **Multi-platform Makefile** - auto-detects Linux, macOS, FreeBSD, OpenBSD, NetBSD, DragonflyBSD, and Windows
* 📖 **No external dependencies** - pure C with standard libraries

---

## Installation

### Quick Install

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

### Basic Commands

```bash
# Default (24-hour, milliseconds, with epoch, DD/MM/YYYY)
betterdate

# 12-hour format with AM/PM
betterdate -12

# US date format (MM/DD/YYYY)
betterdate -US

# Time only (no date)
betterdate -ND

# Hide epoch timestamp
betterdate -NE

# Hide milliseconds (show seconds only)
betterdate -NM

# Hide seconds (show HH:MM only)
betterdate -NS

# Show microseconds precision
betterdate -ms

# Show nanoseconds precision
betterdate -ns

# Change timezone
betterdate -tz UTC
betterdate -tz America/New_York

# Start a stopwatch (in minutes, supports decimals)
betterdate -sw 5      # 5 minutes
betterdate -sw 0.5    # 30 seconds
betterdate -sw 0.1    # 6 seconds

# Show help
betterdate -h

# Show version
betterdate -v
```

### Combining Options

```bash
# 12-hour US format with no milliseconds in Tokyo timezone
betterdate -12 -US -NM -tz Asia/Tokyo

# Time only in UTC with nanoseconds
betterdate -ND -tz UTC -ns

# 12-hour format with no seconds, time only
betterdate -12 -NS -ND

# US format with microseconds, no epoch
betterdate -US -ms -NE
```

### Available Flags

| Flag | Description | Example |
|------|-------------|---------|
| `-12` | Use 12-hour format with AM/PM | `betterdate -12` |
| `-NE` | Hide epoch timestamp (No Epoch) | `betterdate -NE` |
| `-ND` | Hide date (No Date) - show time only | `betterdate -ND` |
| `-NM` | Hide milliseconds (No Milliseconds) | `betterdate -NM` |
| `-NS` | Hide seconds (No Seconds) | `betterdate -NS` |
| `-ms` | Show microseconds (format: SS.mmm.uuu) | `betterdate -ms` |
| `-ns` | Show nanoseconds (format: SS.mmm.uuu.nnn) | `betterdate -ns` |
| `-tz <timezone>` | Display time in specified timezone | `betterdate -tz UTC` |
| `-US` | Use US date format (MM/DD/YYYY) | `betterdate -US` |
| `-sw <minutes>` | Start stopwatch timer | `betterdate -sw 5` |
| `-h, --help` | Show help message | `betterdate -h` |
| `-v, --version` | Show version information | `betterdate -v` |

### Stopwatch Feature

The stopwatch counts down from the specified time and beeps when finished:

```bash
# 5 minute timer
betterdate -sw 5

# 30 second timer
betterdate -sw 0.5

# 10 second timer
betterdate -sw 0.167
```

Output:
```
Stopwatch started for 5.000000 minutes. Press Ctrl+C to stop.
Time left: 04:59
Time left: 04:58
...
Time left: 00:01
Time left: 00:00

Stopwatch finished!
[beeps 5 times]
```

### Common Timezones

- `UTC` - Universal Coordinated Time
- `America/New_York` - Eastern Time (US)
- `America/Los_Angeles` - Pacific Time (US)
- `America/Chicago` - Central Time (US)
- `Europe/London` - United Kingdom
- `Europe/Paris` - France/Central Europe
- `Asia/Tokyo` - Japan
- `Asia/Shanghai` - China
- `Australia/Sydney` - Australia

---

## Platform Support

BetterDate works on:
- ✅ **Linux** (full nanosecond precision support)
- ✅ **macOS** (microsecond precision)
- ✅ **FreeBSD**
- ✅ **OpenBSD**
- ✅ **NetBSD**
- ✅ **DragonflyBSD**
- ⚠️ **Windows** (via MinGW/Cygwin/MSYS2 - limited precision)

**Note:** Nanosecond precision availability depends on hardware and OS. Linux typically provides true nanosecond precision, while macOS is limited to microsecond precision.

---

## Building from Source

### Prerequisites
- GCC or compatible C compiler
- Make
- Unix-like operating system

### Build Process

```bash
# Clone the repository
git clone https://github.com/ThatGuyCodes605/BetterDate.git
cd BetterDate

# Compile
make

# Test locally without installing
make run

# Install system-wide (requires sudo)
sudo make install

# Clean build files
make clean
```

### Makefile Targets
- `make` or `make all` - Build the program
- `make install` - Install to `/usr/local/bin` (requires sudo)
- `make uninstall` - Remove from system (requires sudo)
- `make clean` - Remove build files
- `make run` - Build and run locally
- `make help` - Show all available commands

---

## How It Works

### Technical Details

**Time Retrieval:**
- Uses `clock_gettime()` with `CLOCK_REALTIME` for high-precision time
- Provides nanosecond resolution on supported platforms
- Automatically adjusts update rate based on precision mode

**Display Method:**
- ANSI escape codes control terminal cursor position
- `\033[?25l` - Hides cursor for cleaner display
- `\033[2A` or `\033[1A` - Moves cursor up to redraw in place
- `\033[?25h` - Shows cursor again on exit

**Signal Handling:**
- Catches `SIGINT` (Ctrl+C) for graceful shutdown
- Properly restores cursor visibility before exit

**Timezone Support:**
- Uses `setenv()` and `tzset()` to change timezone
- Does not affect system-wide timezone settings
- Defaults to system timezone if not specified

**Stopwatch:**
- Simple countdown timer with minute precision (supports decimals)
- Beeps 5 times when finished using system bell
- Press Ctrl+C to stop early

---

## Display Format Options

### Date Formats
- **Default**: DD/MM/YYYY (e.g., 15/01/2026)
- **US Format (-US)**: MM/DD/YYYY (e.g., 01/15/2026)
- **No Date (-ND)**: Time only display

### Time Formats
- **Default**: HH:MM:SS.mmm (24-hour with milliseconds)
- **12-hour (-12)**: HH:MM:SS.mmm AM/PM
- **No Milliseconds (-NM)**: HH:MM:SS
- **No Seconds (-NS)**: HH:MM
- **Microseconds (-ms)**: HH:MM:SS.mmm.uuu
- **Nanoseconds (-ns)**: HH:MM:SS.mmm.uuu.nnn

### Epoch Display
- **Default**: Shown on first line
- **No Epoch (-NE)**: Hidden

All options can be combined freely!

---

## Performance

- **Default mode**: Updates every 1ms, minimal CPU usage (~0.1%)
- **Microsecond mode (-ms)**: Updates as fast as possible (~5-10% CPU)
- **Nanosecond mode (-ns)**: Updates as fast as possible (~5-10% CPU)
- **No seconds mode (-NS)**: Updates every minute, minimal CPU usage

---

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

### Development

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

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

---

## Support

If you find this project useful, please consider giving it a ⭐ on GitHub!

For issues, questions, or suggestions:
- Open an issue on GitHub
- Check existing issues to see if your question has been answered