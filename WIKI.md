# BetterDate Wiki

## Home

**BetterDate** is an improved version of the standard Unix `date` command. It's a feature-rich terminal-based clock written in C that displays real-time updates with configurable precision (milliseconds, microseconds, or nanoseconds) and timezone support.

### Features
- ⏰ Real-time clock with configurable precision (milliseconds, microseconds, nanoseconds)
- 🕐 Both 24-hour (default) and 12-hour format support with AM/PM
- 🌍 Timezone support - view time in any timezone worldwide
- 📅 Unix epoch timestamp display (optional)
- 🖥️ Clean, in-place updating display without flickering or scrolling
- ⚡ Efficient - automatically adjusts update rate based on precision level
- 🛑 Graceful exit handling with Ctrl+C
- 🐧 Multi-platform support (Linux, macOS, all BSDs, Windows)
- 📖 No external dependencies

### Platform Support
Works on Linux (full nanosecond precision), macOS (microsecond precision), FreeBSD, OpenBSD, NetBSD, DragonflyBSD, and Windows (via MinGW/Cygwin/MSYS2).

### Example Output

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

**Without epoch (-ne):**
```
Date: 15/01/2026  Time: 18:41:13.123
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

**Default display (24-hour, milliseconds, with epoch):**
```bash
betterdate
```

**12-hour format with AM/PM:**
```bash
betterdate -12
```

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

### Combining Options

You can combine multiple flags:

```bash
# 12-hour format with microseconds in Tokyo, no epoch
betterdate -12 -ms -tz Asia/Tokyo -ne

# 24-hour UTC with nanoseconds
betterdate -tz UTC -ns

# 12-hour format with nanoseconds
betterdate -12 -ns
```

### Available Flags

| Flag | Description | Example |
|------|-------------|---------|
| `-12` | Use 12-hour format with AM/PM | `betterdate -12` |
| `-ne` | Hide epoch timestamp | `betterdate -ne` |
| `-ms` | Show microseconds (milliseconds + microseconds) | `betterdate -ms` |
| `-ns` | Show nanoseconds (milliseconds + microseconds + nanoseconds) | `betterdate -ns` |
| `-tz <timezone>` | Display time in specified timezone | `betterdate -tz UTC` |

### Precision Levels

- **Default**: Milliseconds only (3 digits after seconds)
  - Format: `HH:MM:SS.mmm`
  - Updates every 1ms with sleep to save CPU

- **Microseconds (-ms)**: Milliseconds + Microseconds (6 digits total)
  - Format: `HH:MM:SS.mmm.uuu`
  - Updates as fast as possible (no sleep)

- **Nanoseconds (-ns)**: Milliseconds + Microseconds + Nanoseconds (9 digits total)
  - Format: `HH:MM:SS.mmm.uuu.nnn`
  - Updates as fast as possible (no sleep)

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
- Date formatting: `DD/MM/YYYY`
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

**Performance Optimization:**
- Default mode: sleeps 1ms between updates to reduce CPU usage
- High-precision modes (-ms, -ns): no sleep for maximum update rate
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

**Problem: Compilation errors with `clock_gettime`**
- Ensure you have development tools installed
- Linux: `sudo apt install build-essential` (Ubuntu/Debian)
- macOS: Install Xcode Command Line Tools
- Check that you're using a modern C compiler

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
- Use default mode for lower CPU usage
- Default mode includes 1ms sleep to reduce CPU

**Problem: Cursor stays hidden after crash**
- Run: `printf '\033[?25h'` to restore cursor manually
- Or: `reset` command to reset terminal
- Program should handle this automatically with Ctrl+C

---

## Project Structure

```
BetterDate/
├── date.c       # Main source code
├── Makefile     # Multi-platform build configuration
├── LICENSE      # GPL-3.0 license
├── README.md    # Project overview
└── WIKI.md      # This documentation
```

---

## Performance Notes

### CPU Usage
- **Default mode**: ~0.1% CPU (updates every 1ms with sleep)
- **Microsecond mode (-ms)**: ~5-10% CPU (continuous updates)
- **Nanosecond mode (-ns)**: ~5-10% CPU (continuous updates)

### Memory Usage
- Minimal: ~1-2 MB resident memory
- No dynamic memory allocation in main loop
- Fixed-size buffers and stack variables

### Update Rates
- **Default**: 1000 updates/second (1ms interval)
- **-ms/-ns**: Limited only by system scheduler (~10,000+ updates/second)

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
- Any relevant error messages or screenshots
- Output of `make help` showing detected platform

### Feature Requests
Open an issue on GitHub describing:
- The feature you'd like to see
- Why it would be useful
- How you envision it working
- Whether you'd be willing to implement it yourself

### Good First Issues
Looking to contribute but not sure where to start? Some ideas:
- Add support for different date formats (MM/DD/YYYY, YYYY-MM-DD, ISO 8601)
- Add color customization options
- Add option to show day of week
- Improve error handling and user messages
- Add support for displaying multiple timezones simultaneously
- Write additional documentation or examples
- Add unit tests

---

## Why BetterDate?

BetterDate is a great project for learning:
- **C programming basics** - time functions, command-line arguments, loops, signal handling
- **Terminal control** - ANSI escape codes for cursor manipulation
- **POSIX functions** - `clock_gettime()`, `nanosleep()`, `localtime()`, `setenv()`
- **Build systems** - Cross-platform Makefiles with conditional compilation
- **System programming** - Working with timestamps, signals, and real-time display
- **Precision timing** - Understanding nanoseconds, microseconds, and milliseconds

The code is intentionally kept simple and readable, making it perfect for beginners to study and modify while still being useful for daily use.

---

## Releases

### v2.0 (Upcoming)
- Added microsecond precision mode (-ms)
- Added nanosecond precision mode (-ns)
- Added timezone support (-tz)
- Added signal handler for graceful Ctrl+C exit
- Improved multi-platform Makefile (added DragonflyBSD)
- Automatic performance optimization based on precision mode
- Better cursor handling

### v1.1
- Added 12-hour time format support with `-12` flag
- Improved terminal compatibility
- Bug fixes and performance improvements

### v1.0
- Initial release
- Basic real-time clock display
- Unix epoch timestamp
- Millisecond precision
- ANSI cursor control for smooth updates

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
- Check `make help` to see detected platform information

For general C programming questions or terminal control help, consider:
- Stack Overflow
- The C Programming subreddit
- Linux/BSD terminal emulator documentation

---

## Fun Facts

- The program can display time down to the nanosecond (0.000000001 seconds)
- On Linux, it can update over 10,000 times per second in high-precision mode
- The entire program is less than 200 lines of C code
- Works on 7+ different operating systems with one Makefile
- Can display any timezone in the world without changing system settings