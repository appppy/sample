CC=gcc
CFLAG=-g

R_OBJ=read.o
W_OBJ=write.o

all: read write

clean:
	rm read    \
	rm read.o  \
    rm write   \
	rm write.o \

read: $(ROBJ)
	$(CC) -o read $(ROBJ)

write: $(WOBJ)
	$(CC) -o write $(WOBJ)
