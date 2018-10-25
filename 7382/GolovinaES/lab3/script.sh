#!/bin/bash
g++ Source/lab3.cpp
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
echo "Test 4"
echo " "
./a.out <./Tests/test4.txt
echo " "
echo "Test 5"
echo " "
./a.out <./Tests/test5.txt
echo " "
echo "Tests with incorrect data:"
echo " "
echo " "
echo "Test 6"
echo " "
./a.out <./Tests/test6.txt
echo " "
echo "Test 7"
echo " "
./a.out <./Tests/test7.txt
echo " "
echo "Test 8"
echo " "
./a.out <./Tests/test8.txt
echo " "
echo "Test 9"
echo " "
./a.out <./Tests/test9.txt
echo " "
echo "Test 10"
echo " "
./a.out <./Tests/test10.txt
rm -f a.out
