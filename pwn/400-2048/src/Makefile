TARGET=2048
CC=gcc
CFLAGS=-fno-stack-protector -zexecstack -m32

2048: 2048
	git clone https://github.com/sc0ty/2k48
	cd 2k48; git checkout 7ac0035162f7014b7542ff13a2e7b22123bae662 && \
	git apply ../2048.patch
	cp highscore.cpp 2k48/.
	cp highscore.h 2k48/.
	cd 2k48; make DAEMON=1 
	cd 2K48; strip 2k48

clean:
	rm -rf 2k48/
