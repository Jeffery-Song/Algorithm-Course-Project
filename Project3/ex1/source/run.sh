#!/bin/bash
for k in 12 24 36 48 60
do
g++ Tree.cc -std=c++11 -Dnumber=$k
./a.out
done
