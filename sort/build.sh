#!/bin/bash

$(gcc -c insert_sort/src/*.c)
$(gcc -c distribution_sort/src/*.c)
$(gcc -c select_sort/src/*.c)
$(gcc -c swap_sort/src/*.c)
$(gcc -c merge_sort/*.c)
$(gcc -c main.c && gcc *.o -o main)
$(rm *.o)
