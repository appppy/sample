CC = gcc
CFLAG = -g -Wall
LIBRARIES = -pthread
READ_OBJ = sread.o
WRITE_OBJ = swrite.o

all: sread swrite

clean:
	rm sread
	rm swrite
	rm sread.o
	rm swrite.o

sread: $(READ_OBJ)
	$(CC) $(READ_OBJ) $(CFLAGS) $(LIBRARIES) -o sread

swrite: $(WRITE_OBJ)
	$(CC) $(WRITE_OBJ) $(CFLAGS) $(LIBRARIES) -o swrite

