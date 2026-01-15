# Makefile for betterdate

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Program name
TARGET = betterdate
SOURCE = date.c

# Platform detection
UNAME_S := $(shell uname -s)

# Detect operating system and set appropriate flags
ifeq ($(UNAME_S),Linux)
    PLATFORM = Linux
    LDFLAGS = -lrt
    INSTALL_DIR = /usr/local/bin
endif

ifeq ($(UNAME_S),Darwin)
    PLATFORM = macOS
    LDFLAGS =
    INSTALL_DIR = /usr/local/bin
endif

ifeq ($(UNAME_S),FreeBSD)
    PLATFORM = FreeBSD
    LDFLAGS =
    INSTALL_DIR = /usr/local/bin
endif

ifeq ($(UNAME_S),OpenBSD)
    PLATFORM = OpenBSD
    LDFLAGS =
    INSTALL_DIR = /usr/local/bin
endif

ifeq ($(UNAME_S),NetBSD)
    PLATFORM = NetBSD
    LDFLAGS =
    INSTALL_DIR = /usr/local/bin
endif

ifeq ($(UNAME_S),DragonFly)
    PLATFORM = DragonflyBSD
    LDFLAGS =
    INSTALL_DIR = /usr/local/bin
endif

# Windows detection (Git Bash, Cygwin, MSYS2, WSL)
ifneq (,$(findstring MINGW,$(UNAME_S)))
    PLATFORM = Windows (MinGW)
    LDFLAGS =
    TARGET = betterdate.exe
    INSTALL_DIR = /usr/local/bin
endif

ifneq (,$(findstring CYGWIN,$(UNAME_S)))
    PLATFORM = Windows (Cygwin)
    LDFLAGS =
    TARGET = betterdate.exe
    INSTALL_DIR = /usr/local/bin
endif

ifneq (,$(findstring MSYS,$(UNAME_S)))
    PLATFORM = Windows (MSYS2)
    LDFLAGS =
    TARGET = betterdate.exe
    INSTALL_DIR = /usr/local/bin
endif

# Default target: build the program
all: platform_info $(TARGET)

# Show detected platform
platform_info:
	@echo "Detected platform: $(PLATFORM)"
	@echo "Compiler: $(CC)"
	@echo "Linker flags: $(LDFLAGS)"
	@echo ""

# Compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)
	@echo ""
	@echo "Build complete for $(PLATFORM)!"

# Install to system PATH (requires sudo on Unix-like systems)
install: $(TARGET)
	@echo "Installing $(TARGET) to $(INSTALL_DIR)..."
ifeq ($(PLATFORM),Linux)
	@sudo cp $(TARGET) $(INSTALL_DIR)/$(TARGET)
	@sudo chmod 755 $(INSTALL_DIR)/$(TARGET)
else ifeq ($(PLATFORM),FreeBSD)
	@sudo cp $(TARGET) $(INSTALL_DIR)/$(TARGET)
	@sudo chmod 755 $(INSTALL_DIR)/$(TARGET)
else ifeq ($(PLATFORM),OpenBSD)
	@doas cp $(TARGET) $(INSTALL_DIR)/$(TARGET)
	@doas chmod 755 $(INSTALL_DIR)/$(TARGET)
else ifeq ($(PLATFORM),NetBSD)
	@sudo cp $(TARGET) $(INSTALL_DIR)/$(TARGET)
	@sudo chmod 755 $(INSTALL_DIR)/$(TARGET)
else ifeq ($(PLATFORM),DragonflyBSD)
	@sudo cp $(TARGET) $(INSTALL_DIR)/$(TARGET)
	@sudo chmod 755 $(INSTALL_DIR)/$(TARGET)
else ifeq ($(PLATFORM),macOS)
	@sudo cp $(TARGET) $(INSTALL_DIR)/$(TARGET)
	@sudo chmod 755 $(INSTALL_DIR)/$(TARGET)
else
	@cp $(TARGET) $(INSTALL_DIR)/$(TARGET)
	@chmod 755 $(INSTALL_DIR)/$(TARGET)
endif
	@echo "Installation complete! You can now run: betterdate"

# Uninstall from system
uninstall:
	@echo "Removing $(TARGET) from $(INSTALL_DIR)..."
ifeq ($(PLATFORM),OpenBSD)
	@doas rm -f $(INSTALL_DIR)/betterdate
else
	@sudo rm -f $(INSTALL_DIR)/betterdate
endif
	@echo "Uninstall complete!"

# Clean build files
clean:
	rm -f $(TARGET) betterdate betterdate.exe

# Run the program locally (without installing)
run: $(TARGET)
	./$(TARGET)

# Show help
help:
	@echo "BetterDate Makefile"
	@echo ""
	@echo "Detected platform: $(PLATFORM)"
	@echo ""
	@echo "Available targets:"
	@echo "  make          - Build the program"
	@echo "  make install  - Install to system PATH"
	@echo "  make uninstall- Remove from system"
	@echo "  make clean    - Remove build files"
	@echo "  make run      - Build and run locally"
	@echo "  make help     - Show this help message"
	@echo ""
	@echo "Platform-specific notes:"
	@echo "  Linux:      Uses -lrt for real-time library"
	@echo "  macOS:      No additional libraries needed"
	@echo "  FreeBSD:    No additional libraries needed"
	@echo "  OpenBSD:    Uses 'doas' instead of 'sudo'"
	@echo "  NetBSD:     No additional libraries needed"
	@echo "  DragonflyBSD: No additional libraries needed"
	@echo "  Windows:    Builds .exe (limited terminal support)"
	@echo "  OpenBSD:    Uses 'doas' instead of 'sudo'"

.PHONY: all platform_info install uninstall clean run help
