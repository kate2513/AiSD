#!/bin/bash
make Makefile
echo " "
echo "Tests with correct data:"
echo " "
echo "Test 1"
echo " "
./a.out <./Tests/test1.txt
echo " "
echo "Test 2"
echo " "
./a.out <./Tests/test2.txt
echo " "
echo "Test 3"
echo " "
./a.out <./Tests/test3.txt
echo " "
echo "Tests with incorrect data:"
echo " "
echo "Test 4"
echo " "
./a.out <./Tests/test4.txt
echo " "
echo "Test 5"
echo " "
./a.out <./Tests/test5.txt
echo " "
echo "Test 6"
echo " "
./a.out <./Tests/test6.txt
make -f Makefile clean
