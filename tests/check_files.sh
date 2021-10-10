#!/bin/sh
./test & 
gcc -o tests/client2_dom2 tests/client2_dom2.c
./tests/client2_dom2
FILE="INFO1110/Steve_WR"
if [[ -f "$FILE" ]]; then
    echo "File exists!"
fi
FILE="INFO1110/Steve_RD"
if [[ -f "$FILE" ]]; then
    echo "File exists!"
fi
killall test
echo "Passed check files!!!"
