#!/bin/bash
k=2
rm ../output/$1_sort/time.txt
for ((i=4;i<131073;i=i*8))
do 
    g++ $1.cc -D number=$i -std=c++11
    ./a.out >> ../output/$1_sort/time.txt
    mv ../output/$1_sort/result_$i.txt ../output/$1_sort/result_$k.txt
    k=$[k+3] 
done
