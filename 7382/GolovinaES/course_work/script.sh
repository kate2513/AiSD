#!/bin/bash
g++ ./Source/lab5-2.cpp
echo " "
echo "Test 1"
echo " "
./a.out <./Tests/for_test1.txt
echo " "
echo "Test 2"
echo " "
./a.out <./Tests/for_test2.txt
echo " "
echo "Test 3"
echo " "
./a.out <./Tests/for_test3.txt
echo " "
echo "Test 4"
echo " "
./a.out <./Tests/for_test4.txt
echo " "
echo "Test 5"
echo " "
./a.out <./Tests/for_test5.txt
echo " "
echo "Test 6"
echo " "
./a.out <./Tests/for_test6.txt
echo " "
echo "Test 7"
echo " "
./a.out <./Tests/for_test7.txt
echo " "
echo "Test 8"
echo " "
./a.out <./Tests/for_test8.txt
echo " "
echo "Test 9"
echo " "
./a.out <./Tests/for_test9.txt
rm -rf a.out
