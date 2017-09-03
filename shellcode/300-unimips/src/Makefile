all: unimips
unimips: unimips.c
	mipsel-linux-gnu-gcc -g -Wno-unused-result -O0 unimips.c -static -o unimips
	#mipsel-linux-gnu-strip unimips
clean:
	rm unimips
