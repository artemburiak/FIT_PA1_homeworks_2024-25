#!/bin/bash

for X in {0000..0100} ; do 

if [ ! -e tests/${X}_in.txt ] ; then
printf "All OK!\n"
exit 0
fi

printf "Testing: tests/${X}_in.txt\n"

./a.out < tests/${X}_in.txt > /tmp/out.txt

if ! diff -q tests/${X}_out.txt /tmp/out.txt ; then
printf "Mismatch tests/${X}_in.txt\n"
exit 1
fi

done