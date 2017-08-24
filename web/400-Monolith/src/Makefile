all: rfcsearch
	./prep.sh
	gcc rfcsearch.c -O0 -fstack-protector -fPIC -pie -o rfcsearch
	strip rfcsearch
clean:
	rm -f rfcsearch
	echo "Not cleaning the rfcs... make distclean to clean everything!"
distclean:
	rm -rf rfcs index.txt rfcs.tgz 
