#!/bin/sh
./test &
gcc -o tests/client1_dom2 tests/client1_dom2.c
./tests/client1_dom2
gcc -o tests/client2_dom2 tests/client2_dom2.c
./tests/client2_dom2
gcc -o tests/client1_dom2_say tests/client1_dom2_say.c
gcc -o tests/client1_dom2_receive tests/client1_dom2_receive.c
./tests/client2_dom2_receive &
./tests/client1_dom2_say
pkill test
diff tests/actual_correct_pipe_receive tests/expected_correct_pipe_receive
echo "Passed correct pipe receive test !!"
