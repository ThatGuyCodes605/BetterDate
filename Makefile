# Makefile for betterdate

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lrt

# Program name
TARGET = betterdate
SOURCE = date.c

# Installation directory (usually /usr/local/bin is in PATH)
INSTALL_DIR = /usr/local/bin

# Default target: build the program
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)

# Install to system PATH (requires sudo)
install: $(TARGET)
	@echo "Installing $(TARGET) to $(INSTALL_DIR)..."
	@sudo cp $(TARGET) $(INSTALL_DIR)/$(TARGET)
	@sudo chmod 755 $(INSTALL_DIR)/$(TARGET)
	@echo "Installation complete! You can now run: betterdate"

# Uninstall from system
uninstall:
	@echo "Removing $(TARGET) from $(INSTALL_DIR)..."
	@sudo rm -f $(INSTALL_DIR)/$(TARGET)
	@echo "Uninstall complete!"

# Clean build files
clean:
	rm -f $(TARGET)

# Run the program locally (without installing)
run: $(TARGET)
	./$(TARGET)

.PHONY: all install uninstall clean run
