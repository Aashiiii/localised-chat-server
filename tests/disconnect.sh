#!/bin/sh
./test & 
gcc -o tests/client1_dom2 tests/client1_dom2.c
./tests/client1_dom2
gcc -o tests/client2_dom2 tests/client2_dom2.c
./tests/client2_dom2
gcc -o tests/client1_dom2_disconnect tests/client1_dom2_disconnect.c
./tests/client1_dom2_disconnect
FILE="INFO1110/Jay_WR"
if [[ -f "$FILE" ]]; then
    echo "FAILED!!!."
fi
FILE="INFO1110/Jay_RD"
if [[ -f "$FILE" ]]; then
    echo "FAILED!!!."
fi
killall test
echo "Passed disconnect test case!!"
