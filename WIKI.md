# BetterDate Wiki
Welcome to the BetterDate wiki!
## Home

**BetterDate** is an improved version of the standard Unix `date` command. It's a simple terminal-based clock written in C that displays real-time updates with millisecond precision directly in your terminal.

### Features
- ⏰ Real-time clock with millisecond precision
- 🕐 Both 24-hour (default) and 12-hour format support (use `-12` flag)
- 📅 Displays Unix epoch timestamp
- 🖥️ Clean, in-place updating display without flickering or scrolling
- ⚡ Lightweight and efficient with no external dependencies
- 🐧 Works on any Linux terminal

### Platform Support
**Linux only** - Uses POSIX real-time functions (`clock_gettime`, `nanosleep`) and ANSI escape codes optimized for Linux terminals.

### Example Output

24-hour format (default):
```
Epoch: 1732812345
Date: 28/11/2025  Time: 18:41:13.123
```

12-hour format (with `-12` flag):
```
Epoch: 1732812345
Date: 28/11/2025  Time: 06:41:13.123 PM
```

Both lines refresh smoothly in place.

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

**24-hour format (default):**
```bash
betterdate
```

**12-hour format with AM/PM:**
```bash
betterdate -12
```

### Exiting the Program
Press `Ctrl+C` to exit and restore your terminal cursor.

---

## How It Works

### Technical Details

**Time Retrieval:**
- Uses `clock_gettime()` with `CLOCK_REALTIME` for high-precision time
- Provides nanosecond resolution, displayed as milliseconds
- Updates continuously every 1 millisecond using `nanosleep()`

**Display Method:**
- Uses ANSI escape codes to control terminal cursor
- `\033[?25l` - Hides cursor for cleaner display
- `\033[2A` - Moves cursor up 2 lines to redraw in place
- `\033[?25h` - Shows cursor again on exit
- No flickering or scrolling - overwrites the same two lines

**Time Conversion:**
- Unix epoch: raw timestamp (seconds since January 1, 1970)
- Date formatting: `DD/MM/YYYY`
- Time formatting: `HH:MM:SS.mmm` (milliseconds)
- 12-hour conversion handles midnight (0 → 12 AM) and noon (12 → 12 PM)

---

## Building from Source

### Prerequisites
- GCC or compatible C compiler
- Make
- Linux operating system
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
- `make` or `make all` - Build the program
- `make install` - Install to `/usr/local/bin` (requires sudo)
- `make uninstall` - Remove from system (requires sudo)
- `make clean` - Remove build files
- `make run` - Build and run locally

---

## Troubleshooting

### Common Issues

**Problem: Command not found after installation**
- Ensure `/usr/local/bin` is in your PATH
- Check with: `echo $PATH`
- Add to PATH if needed: `export PATH=$PATH:/usr/local/bin`
- Add to your shell config file (`~/.bashrc` or `~/.zshrc`) to make permanent

**Problem: Permission denied during installation**
- Use `sudo make install` instead of `make install`

**Problem: Display flickering or not updating smoothly**
- Your terminal may not fully support ANSI escape codes
- Try a different terminal emulator (GNOME Terminal, Konsole, xterm, etc.)
- Ensure your terminal is set to a standard terminal type (TERM=xterm)

**Problem: Compilation errors with `clock_gettime`**
- Ensure you're on a Linux system
- Check that you have the development libraries installed
- On some systems you may need to install `build-essential` package

**Problem: Time appears incorrect**
- Check your system time: `date`
- Verify timezone settings: `timedatectl`
- Sync your system clock: `sudo ntpdate pool.ntp.org` or `sudo timedatectl set-ntp true`

**Problem: Library 'rt' not found (macOS)**
- This is expected - the program is designed for Linux only
- The Makefile detects macOS and removes the `-lrt` flag, but full functionality is not guaranteed on non-Linux systems

---

## Project Structure

```
BetterDate/
├── date.c       # Main source code
├── Makefile     # Build configuration
├── LICENSE      # GPL-3.0 license
└── README.md    # Project overview
```

---

## Contributing

### How to Contribute

1. **Fork the repository** on GitHub
2. **Create a feature branch:**
   ```bash
   git checkout -b feature-name
   ```
3. **Make your changes** and test thoroughly on Linux
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
- Test on Linux before submitting

### Reporting Bugs
Open an issue on GitHub with:
- Description of the problem
- Steps to reproduce
- Expected vs actual behavior
- System information (Linux distribution, kernel version, terminal emulator)
- Any relevant error messages or screenshots

### Feature Requests
Open an issue on GitHub describing:
- The feature you'd like to see
- Why it would be useful
- How you envision it working
- Whether you'd be willing to implement it yourself

### Good First Issues
Looking to contribute but not sure where to start? Some ideas:
- Add support for different date formats (MM/DD/YYYY, YYYY-MM-DD, etc.)
- Add timezone display
- Add color customization options
- Improve error handling
- Add more command-line options
- Write additional documentation or examples

---

## Why BetterDate?

BetterDate is a great intro project for learning:
- **C programming basics** - time functions, command-line arguments, loops
- **Terminal control** - ANSI escape codes for cursor manipulation
- **POSIX functions** - `clock_gettime()`, `nanosleep()`, `localtime()`
- **Build systems** - Understanding Makefiles
- **System programming** - Working with timestamps and real-time display

The code is intentionally kept simple and readable, making it perfect for beginners to study and modify.

---

## Releases

### v1.1 (Latest)
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

---

## Support

If you encounter any issues or have questions:
- Open an issue on GitHub
- Check the troubleshooting section above
- Review existing issues to see if your problem has been addressed

For general C programming questions or terminal control help, consider:
- Stack Overflow
- The C Programming subreddit
- Linux terminal emulator documentation
