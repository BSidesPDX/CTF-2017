CC?=gcc
OBJ=cookie
CFLAGS=-fno-stack-protector -zexecstack -m32

cookiectf: ${OBJS}
	${CC} ${CFLAGS} -o cookie ctf.c cookie.c
	strip cookie

clean:
	@rm $(OBJ)
