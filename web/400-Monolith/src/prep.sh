#!/bin/bash
cd "$(dirname "$0")"
if [[ ! -f rfcs.tgz ]]; then
    wget https://www.rfc-editor.org/in-notes/tar/RFC-all.tar.gz -O rfcs.tgz
else
    echo "Skipping RFC download. rfc.tgz found!"
fi

if [[ ! -f rfcs/rfc117.txt ]]; then
    echo "Making directory..."
    mkdir rfcs
    echo "Extracting RFCs..."
    tar -xzC rfcs -f rfcs.tgz
    echo "Removing non txt RFCs"
    rm -rf rfcs/a
    find rfcs | grep -v "txt$" | xargs rm
else
    echo "Skipping RFC extract, some rfcs exist!"
fi

if [[ ! -f index.txt ]]; then
    echo "Generating index.txt..."
    python makeIndex.py > index.txt
else
    echo "Skipping index generation, index.txt found."
fi
