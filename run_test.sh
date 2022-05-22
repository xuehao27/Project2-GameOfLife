#!/bin/bash
gcc -Wall -DTEST -DDISPLAY -o test test.c main.c game.h
echo "The test is running..."
./test
if [ 0 -eq $? ]; then
    echo "Pass the test."
else
    echo "Test failed."
fi