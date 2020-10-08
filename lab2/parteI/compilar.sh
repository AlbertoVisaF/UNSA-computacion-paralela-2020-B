#!/bin/sh
gcc -g -Wall -o pth_pi_busy2 pth_pi_busy2.c -lm -lpthread
./pth_pi_busy2 2 100000000
./pth_pi_busy2 4 100000000 
./pth_pi_busy2 8 100000000
./pth_pi_busy2 16 100000000
./pth_pi_busy2 32 100000000
./pth_pi_busy2 64 100000000
./pth_pi_busy2 128 100000000
./pth_pi_busy2 256 100000000