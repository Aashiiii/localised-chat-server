#!/bin/sh
./test &
gcc -o tests/client1_dom1 tests/client1_dom1.c
./tests/client1_dom1
gcc -o tests/client2_dom1 tests/client2_dom1.c
./tests/client2_dom1
gcc -o tests/client1_dom2 tests/client1_dom2.c
./tests/client1_dom2
gcc -o tests/client2_dom2 tests/client2_dom2.c
./tests/client2_dom2
gcc -o tests/client1_dom1_say_cont1 tests/client1_dom1_say_cont1.c
gcc -o tests/client2_dom1_receive_cont1 tests/client2_dom1_receive_cont1.c
./tests/client2_dom1_receive_cont1 &
PID1=$!
./tests/client1_dom1_say_cont1
gcc -o tests/client1_dom2_say tests/client1_dom2_say.c
gcc -o tests/client2_dom2_receive tests/client2_dom2_receive.c
./tests/client2_dom2_receive &
./tests/client1_dom2_say
diff tests/actual_one_domain_say tests/expected_one_domain_say
diff tests/actual_one_domain_say_recv_cont1 tests/actual_one_domain_say_recv_cont1
diff tests/actual_one_domain_say_recv_cont2 tests/actual_one_domain_say_recv_cont2
killall test
kill $PID1
echo "Passed mixed say saycont!!"
