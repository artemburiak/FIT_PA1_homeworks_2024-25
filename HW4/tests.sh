#!/bin/bash

for X in {0000..0100} ; do 

if [ ! -e CZE/${X}_in.txt ] ; then
printf "All OK!\n"
exit 0
fi

printf "Testing: CZE/${X}_in.txt\n"

./a.out < CZE/${X}_in.txt > /tmp/out.txt

if ! diff -q CZE/${X}_out.txt /tmp/out.txt ; then
printf "Mismatch CZE/${X}_in.txt\n"
exit 1
fi

done


