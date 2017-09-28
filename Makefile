target: shellcode web

shellcode:
	make -C ./shellcode/100-thumb/src
	make -C ./shellcode/200-movon/src
	make -C ./shellcode/300-unimips/src

web:
	make -C ./web/400-Monolith/src

clean:
	make -C ./shellcode/100-thumb/src clean
	make -C ./shellcode/200-movon/src clean
	make -C ./shellcode/300-unimips/src clean
	make -C ./web/400-Monolith/src distclean
