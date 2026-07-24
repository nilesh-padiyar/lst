CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

SRC = $(wildcard src/*.c)
OUT = main

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)


