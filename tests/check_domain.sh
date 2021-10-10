#!/bin/sh
./test & 
gcc -o tests/client1_dom2 tests/client1_dom2.c
./tests/client1_dom2
gcc -o tests/client2_dom2 tests/client2_dom2.c
./tests/client2_dom2
DOMAIN="INFO1110"
if [[ -d "$DOMAIN" ]]; then
    echo "Folder present!"
else
    echo "Failed!"
fi
killall test
echo "Passed check domain!!!"
