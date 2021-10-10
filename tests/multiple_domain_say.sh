#!/bin/sh
./test & 
PID=$!
gcc -o tests/client1_dom1 tests/client1_dom1.c
./tests/client1_dom1
gcc -o tests/client2_dom1 tests/client2_dom1.c
./tests/client2_dom1
gcc -o tests/client3_dom1 tests/client3_dom1.c
./tests/client3_dom1
gcc -o tests/client1_dom3 tests/client1_dom3.c
./tests/client1_dom3
gcc -o tests/client2_dom3 tests/client2_dom3.c
./tests/client2_dom3
gcc -o tests/client1_dom3_say tests/client1_dom3_say.c
gcc -o tests/client2_dom3_receive tests/client2_dom3_receive.c
./tests/client2_dom3_receive &
./tests/client1_dom3_say
killall test
diff tests/actual_multiple_domain_say tests/expected_multiple_domain_say
echo "Passed multiple domain say!!!"
