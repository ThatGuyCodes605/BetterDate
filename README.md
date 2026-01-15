# BetterDate

A feature-rich terminal-based clock written in C that displays real-time date, time, and Unix epoch with customizable precision and timezone support.

---

## Example Output

**Default (milliseconds):**
```
Epoch: 1737000000
Date: 15/01/2026  Time: 18:41:13.123
```

**With microseconds (-ms):**
```
Epoch: 1737000000
Date: 15/01/2026  Time: 18:41:13.123.456
```

**With nanoseconds (-ns):**
```
Epoch: 1737000000
Date: 15/01/2026  Time: 18:41:13.123.456.789
```

**12-hour format (-12):**
```
Epoch: 1737000000
Date: 15/01/2026  Time: 06:41:13.123 PM
```

All displays update smoothly in place without scrolling.

---

## Features

* ⏰ **Real-time clock** with configurable precision (milliseconds, microseconds, or nanoseconds)
* 🕐 **12-hour or 24-hour format** with AM/PM display
* 🌍 **Timezone support** - view time in any timezone
* 📅 **Unix epoch timestamp** display (optional)
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
# Default (24-hour, milliseconds, with epoch)
betterdate

# 12-hour format with AM/PM
betterdate -12

# Show microseconds precision
betterdate -ms

# Show nanoseconds precision (includes milliseconds and microseconds)
betterdate -ns

# Hide epoch timestamp
betterdate -ne

# Change timezone
betterdate -tz UTC
betterdate -tz America/New_York
betterdate -tz Europe/London
betterdate -tz Asia/Tokyo

#Stopwatch
betterdate -sw 8 #sets a stopwatch for 8 seconds
```

### Combining Options

```bash
# 12-hour format in Tokyo timezone with microseconds, no epoch
betterdate -12 -tz Asia/Tokyo -ms -ne

# 24-hour format in UTC with nanoseconds
betterdate -tz UTC -ns

# 12-hour format with nanoseconds
betterdate -12 -ns
```

### Available Flags

| Flag | Description |
|------|-------------|
| `-12` | Use 12-hour format with AM/PM |
| `-ne` | Hide epoch timestamp (no epoch) |
| `-ms` | Show microseconds (format: SS.mmm.uuu) |
| `-ns` | Show nanoseconds (format: SS.mmm.uuu.nnn) |
| `-tz <timezone>` | Display time in specified timezone |
| `-sw <seconds>` | Starts Stopwatch in specified number of seconds |

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
- ✅ **Linux** (full precision support)
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

---

## Performance

- **Default mode**: Updates every 1ms, minimal CPU usage
- **Microsecond mode (-ms)**: Updates as fast as possible for precision
- **Nanosecond mode (-ns)**: Updates as fast as possible for maximum precision

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
