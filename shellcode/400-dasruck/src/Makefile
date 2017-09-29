all: dasruck
dasruck: dasruck.c
	gcc -g -O3 dasruck.c -o dasruck -fno-stack-protector -fpic -pie
	#strip dasruck
clean:
	rm dasruck
