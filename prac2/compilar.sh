#!/bin/sh
gcc -g -Wall -o mat_vec pth_mat_vec.c -lpthread
   ./mat_vec 1  8000000 8
   ./mat_vec 1  800 800
   ./mat_vec 1 8 8000000
  ./mat_vec 2  8000000 8
 ./mat_vec 2  800 800
  ./mat_vec 2 8 8000000
 ./mat_vec 4  8000000 8
  ./mat_vec 4  800 800
   ./mat_vec 4 8 8000000
 

