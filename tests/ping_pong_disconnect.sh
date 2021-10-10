#!/bin/sh
./test & 
gcc -o tests/client1_dom2 tests/client1_dom2.c
./tests/client1_dom2
sleep 40
FILE="INFO1110/Jay_WR"
if [[ -f "$FILE" ]]; then
    echo "FAILED!!!."
fi
FILE="INFO1110/Jay_RD"
if [[ -f "$FILE" ]]; then
    echo "FAILED!!!."
fi
killall test
echo "Passed ping pong disconnect!!!"
