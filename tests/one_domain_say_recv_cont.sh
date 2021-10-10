#!/bin/sh 
./test &
gcc -o tests/client1_dom1 tests/client1_dom1.c
./tests/client1_dom1
gcc -o tests/client2_dom1 tests/client2_dom1.c
./tests/client2_dom1
gcc -o tests/client1_dom1_say_cont1 tests/client1_dom1_say_cont1.c
gcc -o tests/client1_dom1_say_cont2 tests/client1_dom1_say_cont2.c
gcc -o tests/client1_dom1_say_cont3 tests/client1_dom1_say_cont3.c
gcc -o tests/client2_dom1_receive_cont1 tests/client2_dom1_receive_cont1.c
gcc -o tests/client2_dom1_receive_cont2 tests/client2_dom1_receive_cont2.c
gcc -o tests/client2_dom1_receive_cont3 tests/client2_dom1_receive_cont3.c
./tests/client2_dom1_receive_cont1 &
PID1=$!
./tests/client1_dom1_say_cont1
./tests/client2_dom1_receive_cont2 &
PID2=$!
./tests/client1_dom1_say_cont2
diff tests/actual_one_domain_say_recv_cont1 tests/actual_one_domain_say_recv_cont1
diff tests/actual_one_domain_say_recv_cont2 tests/actual_one_domain_say_recv_cont2
killall test
echo "Passed one domain say recv cont!!!"

