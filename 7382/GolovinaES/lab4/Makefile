all:	binary_tree

binary_tree: lab4.o functions.o
	g++ lab4.o functions.o

lab4.o: ./Source/lab4.cpp
	g++ -c ./Source/lab4.cpp

functions.o: ./Source/functions.cpp
	g++ -c ./Source/functions.cpp

clean:
	rm -rf *.o a.out
