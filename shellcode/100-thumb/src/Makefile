all: thumb
thumb: thumb.c
	arm-linux-gnueabi-gcc -g -Wno-unused-result -O3 thumb.c -static -o thumb
	#arm-linux-gnueabi-strip thumb
clean:
	rm thumb
