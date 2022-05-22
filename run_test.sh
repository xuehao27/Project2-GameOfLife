#!/bin/bash
gcc -Wall -DTEST -o test test.c main.c game.h
./test
if [ 0 -eq $? ]; then
    echo "Pass the test."
else
    echo "Test failed."
fi