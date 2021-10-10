#!/bin/bash

# USYD CODE CITATION ACKNOWLEDGEMENT
# I declare that i have copied the following lines of code from INFO1110 unit
# assignment resources, with only few changes. The changes i have made include # changing the programming language in which tests files need to be run, and 
# some minor changes in the echo statements. It is not my own work.
#
# URL- https://canvas.sydney.edu.au/courses/20732

echo "TESTING!"

count=0

for test in tests/*.sh; do
	name=$(basename $test .sh)
	bash tests/$name.sh
	count=$((count+1))
done

echo "Finished running $count tests!"
