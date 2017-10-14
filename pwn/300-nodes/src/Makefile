TARGET=nodes

CC=gcc
CFLAGS=-fno-stack-protector -zexecstack -m32

all: $(TARGET)
	strip nodes

clean:
	@rm $(TARGET)
