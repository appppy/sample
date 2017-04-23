CC=gcc
CFLAG=-g
READ_OBJ=sread.o
WRITE_OBJ=swrite.o

all: sread swrite

clean:
	rm sread
	rm swrite
	rm sread.o
	rm swrite.o

read: $(READ_OBJ)
	$(CC) -o sread $(READ_OBJ)

write: $(WRITE_OBJ)
	$(CC) -o swrite $(WRITE_OBJ)

