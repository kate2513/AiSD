all:	hierarchical_list

hierarchical_list: lab2.o functions.o
	gcc lab2.o functions.o

lab2.o: ./Source/lab2.c
	gcc -c ./Source/lab2.c

functions.o: ./Source/functions.c
	gcc -c ./Source/functions.c

clean:
	rm -rf *.o a.out
