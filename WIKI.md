# BetterDate Wiki

Complete documentation for BetterDate - the feature-rich terminal clock

---

## Table of Contents

1. [Installation](#installation)
2. [Basic Usage](#basic-usage)
3. [All Features](#all-features)
4. [Stopwatch & Timers](#stopwatch--timers)
5. [Display Modes](#display-modes)
6. [Troubleshooting](#troubleshooting)

---

## Installation

### From Source

```bash
git clone https://github.com/ThatGuyCodes605/BetterDate.git
cd BetterDate
make
sudo make install
```

### Uninstall

```bash
cd BetterDate
sudo make uninstall
```

---

## Basic Usage

### Default Clock

```bash
betterdate
```

Shows:
```
Epoch: 1737000000
Date: 15/01/2026  Time: 18:41:13.123
```

### Common Options

```bash
betterdate -12              # 12-hour format
betterdate -US              # US date format (MM/DD/YYYY)
betterdate -iso             # ISO format (YYYY-MM-DD)
betterdate -ND              # Time only
betterdate -NE              # Hide epoch
betterdate -tz UTC          # Change timezone
```

---

## All Features

### Display Format Flags

| Flag | Description | Example Output |
|------|-------------|----------------|
| `-12` | 12-hour with AM/PM | `06:41:13 PM` |
| `-US` | US date format | `01/15/2026` |
| `-iso` | ISO 8601 format | `2026-01-15` |
| `-dw` | Full day name | `Wednesday Date: ...` |
| `-DW` | Abbreviated day | `Wed Date: ...` |
| `-ds <char>` | Custom separator | `15-01-2026` (with `-ds -`) |
| `-bin` | Binary format | `00010010:00101001` |
| `-hex` | Hexadecimal | `12:29:0D` |

### Visibility Flags (Capital = Hide)

| Flag | What It Hides | Result |
|------|---------------|--------|
| `-NE` | Epoch timestamp | No first line |
| `-ND` | Date | `Time: 18:41:13.123` |
| `-NM` | Milliseconds | `Time: 18:41:13` |
| `-NS` | Seconds | `Time: 18:41` |

### Precision Flags

| Flag | Precision | Format |
|------|-----------|--------|
| Default | Milliseconds | `SS.mmm` |
| `-ms` | Microseconds | `SS.mmm.uuu` |
| `-ns` | Nanoseconds | `SS.mmm.uuu.nnn` |

**Note:** In binary/hex modes, `-ns` always shows full precision.

### Timezone Support

```bash
betterdate -tz <timezone>
```

**Examples:**
- `betterdate -tz UTC`
- `betterdate -tz America/New_York`
- `betterdate -tz Asia/Tokyo`
- `betterdate -tz Europe/London`

Find timezones: `ls /usr/share/zoneinfo/`

---

## Stopwatch & Timers

### Stopwatch (Counts Up)

```bash
betterdate -sw
```

Output:
```
Stopwatch started. Press Ctrl+C to stop.
Elapsed time: 00:05:23
```

Counts up indefinitely. Shows HH:MM:SS.

### Alarm Timer (Counts Down)

```bash
betterdate -al <HH:MM:SS>
```

**Examples:**
```bash
betterdate -al 01:30:00    # 1 hour 30 minutes
betterdate -al 00:25:00    # 25 minutes (Pomodoro)
betterdate -al 00:03:00    # 3 minutes (Tea timer)
betterdate -al 00:00:30    # 30 seconds
```

Beeps 5 times when finished.

### Date Countdown

```bash
betterdate -cd \"<YYYY-MM-DD HH:MM:SS>\"
```

**Important:** Use quotes!

**Examples:**
```bash
betterdate -cd \"2026-12-31 23:59:59\"
betterdate -cd \"2026-06-15 12:00:00\"
betterdate -cd \"2027-01-01 00:00:00\"
```

Output:
```
Counting down to 2026-12-31 23:59:59
Time remaining: 349 days, 05:18:42
```

---

## Display Modes

### Binary Mode

```bash
betterdate -bin
```

Shows everything in binary (base 2):
```
Epoch in Binary: 01100111 11010110 00110100 00000000
Binary Time: 00010010:00101001:00001101
```

**Combine with other flags:**
```bash
betterdate -bin -12        # Binary with AM/PM
betterdate -bin -ns        # Binary with nanoseconds
betterdate -bin -ND        # Binary time only
```

### Hexadecimal Mode

```bash
betterdate -hex
```

Shows everything in hex (base 16):
```
Epoch in Hex: 67D63400
Hex Time: 12:29:0D.07B
```

**Combine with other flags:**
```bash
betterdate -hex -12        # Hex with AM/PM
betterdate -hex -ns        # Hex with nanoseconds
betterdate -hex -iso       # Hex with ISO date
```

### Day of Week

```bash
betterdate -dw             # Full name
betterdate -DW             # Abbreviated
```

Output:
```
Wednesday Date: 15/01/2026  Time: 18:41:13.123
Wed Date: 15/01/2026  Time: 18:41:13.123
```

---

## Combining Flags

You can combine multiple flags:

```bash
# Professional display
betterdate -iso -dw -12 -NE

# Programmer's clock
betterdate -hex -ns -ND

# Minimal display
betterdate -ND -NS -NE

# International format
betterdate -iso -dw -tz UTC

# US format with day
betterdate -US -DW -12
```

---

## Platform Support

### Full Support
- ? **Linux** - Full nanosecond precision
- ? **macOS** - Microsecond precision
- ? **FreeBSD**
- ? **OpenBSD** (uses `doas` instead of `sudo`)
- ? **NetBSD**
- ? **DragonflyBSD**

### Limited Support
- ?? **Windows** - Via MinGW/Cygwin/MSYS2, limited precision

### Precision Notes

**Linux:**
- True nanosecond precision
- Best performance

**macOS:**
- Microsecond precision (nanoseconds show as 000)
- Hardware limitation, not a bug

**BSD:**
- Similar to Linux
- Good precision support

---

## Troubleshooting

### Command Not Found

**Problem:** `betterdate: command not found`

**Solution:**
```bash
echo $PATH                           # Check PATH
export PATH=$PATH:/usr/local/bin    # Add to PATH
```

Make permanent: Add to `~/.bashrc` or `~/.zshrc`

### Permission Denied

**Problem:** Can't install

**Solution:**
```bash
sudo make install                    # Linux, macOS, most BSDs
doas make install                    # OpenBSD
```

### Nanoseconds Always 000

**Problem:** Third precision digit always shows 000

**Explanation:** This is normal on macOS. The hardware only provides microsecond precision. On Linux, you'll see real nanosecond values.

### Countdown Format Error

**Problem:** `Invalid format. Use: YYYY-MM-DD HH:MM:SS`

**Solution:** Always use quotes around the date-time:
```bash
# Wrong
betterdate -cd 2026-12-31 23:59:59

# Correct
betterdate -cd \"2026-12-31 23:59:59\"
```

### Terminal Cursor Hidden

**Problem:** Cursor disappeared after crash

**Solution:**
```bash
printf '\033[?25h'    # Restore cursor
# or
reset                 # Full terminal reset
```

### Stopwatch/Timer Won't Beep

**Problem:** No sound when alarm finishes

**Solution:**
- Check terminal settings for \"Terminal bell\" or \"Audible bell\"
- Check system volume
- Try a different terminal emulator

### High CPU Usage

**Problem:** Program using a lot of CPU

**Explanation:** This is normal with `-ms` or `-ns` flags. They update as fast as possible for precision.

**Solution:** Use default mode or `-NM` for lower CPU usage.

---

## Tips & Tricks

### Quick Alias

Add to `~/.bashrc` or `~/.zshrc`:

```bash
alias clock='betterdate -ND -12'
alias timer='betterdate -al'
alias countdown='betterdate -cd'
alias watch='betterdate -sw'
```

### Background Timer

```bash
betterdate -al 00:25:00 &
```

Runs in background, beeps when done.

### Log Timestamps

```bash
while true; do
    betterdate -ND -iso >> log.txt
    sleep 1
done
```

### Multiple Timezones

Open multiple terminals:
```bash
# Terminal 1
betterdate -tz America/New_York

# Terminal 2  
betterdate -tz Europe/London

# Terminal 3
betterdate -tz Asia/Tokyo
```

---

## Performance

### CPU Usage
- **Default:** ~0.1% (1ms updates)
- **-ms/-ns:** ~5-10% (continuous updates)
- **-NS:** ~0% (1 minute updates)
- **Stopwatch/Timer:** ~0% (1 second updates)

### Memory
- ~1-2 MB resident memory
- No dynamic allocation in main loop

---

## Building from Source

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt install build-essential

# macOS (install Xcode Command Line Tools)
xcode-select --install

# FreeBSD
pkg install gmake
```

### Compile
```bash
make                # Build
make run            # Test locally
sudo make install   # Install
make clean          # Clean build files
make help           # Show all targets
```

---

## Contributing

1. Fork on GitHub
2. Create feature branch
3. Make changes
4. Test thoroughly
5. Submit Pull Request

**Code Style:**
- Clear variable names
- Comment complex logic
- Follow existing formatting
- Test on multiple platforms

---

## License

GPL-3.0 License

Copyright (C) 2026 ThatGuyCodes605

Free to use, modify, and distribute.
See LICENSE file for details.

---

## Support

- ? **Bug Reports:** Open GitHub issue
- ? **Feature Requests:** Open GitHub issue  
- ? **Questions:** Check existing issues
- ? **Star the repo** if you find it useful!

---

## Links

- **GitHub:** https://github.com/ThatGuyCodes605/BetterDate
- **Issues:** https://github.com/ThatGuyCodes605/BetterDate/issues

---

**Version:** 1.8  
**Last Updated:** January 2026
