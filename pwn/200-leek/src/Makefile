CC?=gcc
OBJ=leek
CFLAGS=-Wall -fno-stack-protector -zexecstack

leek: ${OBJS}
	${CC} -m32 ${CFLAGS} -o leek leek.c
	strip leek

clean:
	rm -rf *.o leek 
