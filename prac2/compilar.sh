#!/bin/sh
gcc -g -Wall -o mat_vec pth_mat_vec.c -lpthread
echo "1 800000*8"
./mat_vec 1  8000000 8
echo "2 800000*8"
./mat_vec 2  8000000 8
echo "4 800000*8"
./mat_vec 4  8000000 8
echo "1 8000*8000"
./mat_vec 1  8000 8000
echo "2 8000*8000"
./mat_vec 2  8000 8000
echo "4 8000 8000"
./mat_vec 4  8000 8000
echo "1 8*800000"
./mat_vec 1 8 8000000
echo "2 8*800000"
./mat_vec 2 8 8000000
echo "4 8*800000"
./mat_vec 4 8 8000000
 

