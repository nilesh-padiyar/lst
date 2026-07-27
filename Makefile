
# --- COMPILATION --- #

CC = gcc
CFLAGS = -std=c11 -g -Wall -Wextra -pedantic

SRC = $(wildcard src/*.c)
OUT = lst

PREFIX = /usr/local

.PHONY: all clean install uninstall

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

# --- INSTALLATION ENGIE --- #

install: all
	@echo "Install lst to $(PREFIX)/bin..."
	mkdir -p $(PREFIX)/bin
	cp $(OUT) $(PREFIX)/bin/$(OUT)
	chmod 755 $(PREFIX)/bin/$(OUT)
	@echo "lst installed successfully! Try running 'lst' from anywhere."

uninstall:
	@echo "Removing 'lst' from $(PREFIX)/bin..."
	rm -f $(PREFIX)/bin/$(OUT)
	@echo "lst uninstalled successfully."
	@echo "submit any issue to "https://github.com/nilesh-padiyar/lst/""
