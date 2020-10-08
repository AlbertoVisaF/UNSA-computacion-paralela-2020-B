#!/bin/sh
gcc -g -Wall -o pth_pi_mutex pth_pi_mutex.c -lm -lpthread
./pth_pi_mutex 2 100000000
./pth_pi_mutex 4 100000000 
./pth_pi_mutex 8 100000000
./pth_pi_mutex 16 100000000
./pth_pi_mutex 32 100000000
./pth_pi_mutex 64 100000000

