all: unimips
unimips: unimips.c
	mips-linux-gnu-gcc -Wno-unused-result -O0 unimips.c -static -o unimips
	mips-linux-gnu-strip unimips
clean:
	rm unimips
