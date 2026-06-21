CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -O2

INCLUDES = -Iinclude

SRC = \
	src/main.c \
	src/cli.c \
	src/tree.c \
	src/bitstream.c \
	src/archive.c \
	src/file_io.c \
	src/compress.c \
	src/decompress.c

OBJ = $(SRC:.c=.o)

TARGET = huffman

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(TARGET)

run:
	./$(TARGET)

.PHONY: all clean run