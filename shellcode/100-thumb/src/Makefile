all: thumb
thumb: thumb.c
	arm-linux-gnueabi-gcc -O0 thumb.c -static -o thumb
	arm-linux-gnueabi-strip thumb
clean:
	rm thumb
