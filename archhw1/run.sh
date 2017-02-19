#!/bin/bash

rm -f conv
gcc -std=c99 -Werror -O3 -o conv conv.c
./conv 2 1920 1080 4096 2160 8192 4320 16384 8192