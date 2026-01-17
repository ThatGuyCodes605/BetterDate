# BetterDate

A feature-rich terminal-based clock written in C that displays real-time date, time, and Unix epoch with customizable precision, timezone support, stopwatch, alarm, and countdown features.

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

**Day of week (-dw):**
```
Wednesday Date: 15/01/2026  Time: 18:41:13.123
```

**Binary format (-bin):**
```
Epoch in Binary: 01100111 11010110 00110100 00000000
Date: 00001111/00000001/0000011111101010  Binary Time: 00010010:00101001:00001101
```

**Hex format (-hex):**
```
Epoch in Hex: 67D63400
Date: 0F/01/07EA  Hex Time: 12:29:0D.07B
```

**Stopwatch (-sw):**
```
Stopwatch started. Press Ctrl+C to stop.
Elapsed time: 00:05:23
```

**Alarm (-al 01:30:00):**
```
Alarm set for 01:30:00. Press Ctrl+C to cancel.
Time remaining: 01:24:37
```

**Countdown (-cd \"2026-12-31 23:59:59\"):**
```
Counting down to 2026-12-31 23:59:59
Press Ctrl+C to stop.

Time remaining: 349 days, 05:18:42
```

---

## Features

* ? **Real-time clock** with configurable precision (milliseconds, microseconds, or nanoseconds)
* ? **12-hour or 24-hour format** with AM/PM display
* ? **Timezone support** - view time in any timezone
* ? **Unix epoch timestamp** display (optional)
* ?? **US date format** - switch between DD/MM/YYYY and MM/DD/YYYY
* ? **ISO 8601 format** - YYYY-MM-DD international standard
* ?? **Day of week display** - full or abbreviated
* ? **Binary and Hex modes** - for the programmers!
* ?? **Stopwatch** - counts up from 00:00:00
* ? **Alarm timer** - countdown from HH:MM:SS with beeps
* ? **Date countdown** - count down to specific date and time
* ?? **Customizable display** - hide date, epoch, seconds, or milliseconds
* ? **Custom date separator** - use /, -, or any character
* ?? **Clean in-place updates** using ANSI escape codes
* ? **Efficient** - automatically adjusts update rate
* ? **Graceful exit** - Ctrl+C properly restores cursor
* ? **Multi-platform** - Linux, macOS, all BSDs, Windows
* ? **No external dependencies**

---

## Quick Start

```bash
git clone https://github.com/ThatGuyCodes605/BetterDate.git
cd BetterDate
make && sudo make install
betterdate
```

---

## Usage Examples

```bash
betterdate              # Default clock
betterdate -12          # 12-hour format
betterdate -iso -dw     # ISO date with day name
betterdate -bin         # Binary mode
betterdate -hex -ns     # Hex with nanoseconds
betterdate -sw          # Stopwatch
betterdate -al 00:05:00 # 5 minute timer
betterdate -cd \"2027-01-01 00:00:00\" # New Year countdown
```

