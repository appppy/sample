CC=gcc
CFLAG=-g
OBJ=test.o

all: test

clean:
	rm test
	rm test.o

crc32: $(OBJ)
	$(CC) -fsanitize=address -o test $(OBJ)

