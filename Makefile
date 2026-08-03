CC = gcc

CFLAGS = -std=c11 -Werror -Wall -Wextra -pedantic
DEBUGFLAGS = $(CFLAGS) -g -O0

SRC = $(wildcard src/*.c)
TARGET = lst

PREFIX ?= /usr/local

.PHONY: all debug clean format install uninstall

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

debug:
	$(CC) $(DEBUGFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

format:
	clang-format -i $(SRC)

install: all
	@echo "Install lst to $(PREFIX)/bin..."
	mkdir -p $(PREFIX)/bin
	cp $(TARGET) $(PREFIX)/bin/$(TARGET)
	chmod 755 $(PREFIX)/bin/$(TARGET)
	@echo "lst installed successfully! Try running 'lst' from anywhere."

uninstall:
	@echo "Removing 'lst' from $(PREFIX)/bin..."
	rm -f $(PREFIX)/bin/$(TARGET)
	@echo "lst uninstalled successfully."
	@echo "Report issues at: https://github.com/nilesh-padiyar/lst/"
