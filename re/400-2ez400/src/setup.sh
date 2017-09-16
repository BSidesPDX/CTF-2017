#!/bin/bash

/usr/bin/env python rot13.py

git clone https://github.com/RobinDavid/LSB-Steganography.git
cd LSB-Steganography
virtualenv -p python3 venv
. venv/bin/activate
pip3 install -r requirements.txt
python3 LSBSteg.py encode -i ../bsidesPDX.png -o ../bsidesPDX-STEG.png -f ../wallOfText
cd ..

echo -n 'static unsigned char magicFile[] = "' > challenge.h
hexdump -ve '/1 "\\x%02x"' < bsidesPDX-STEG.png >> challenge.h
echo '";' >> challenge.h
gcc challenge.c -o challenge
