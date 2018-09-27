all:	recursion

recursion: lab1.o functions.o
	gcc lab1.o functions.o

lab1.o: ./Source/lab1.c
	gcc -c ./Source/lab1.c

functions.o: ./Source/functions.c
	gcc -c ./Source/functions.c

clean:
	rm -rf *.o a.out
