#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "structure.h"


int main(){

	char name[20];
	std::ifstream file;
	int key=0, new_key=0;
	int forrand=time(0);

	//receiving file .txt
	std::cout << "Please, type the name of the file in format <name>.txt" << std::endl;
	std::cin.getline(name,20);
	file.open(name);
	if (!file.is_open()){
		std::cout << "\nFile couldn't be open.\nProgram terminated!" << std::endl;
		return 0;
	}

	//receiving key for the search
	std::cout << "Enter key(int) that you want to find: ";
	std::cin >> new_key;
	std::cout << std::endl;

	//making class object for future treap
	randTreap<int> my_treap;

	//receiving elements from file and adding them to the treap
	do{
		srand(forrand);
		file >> key;
		if (file.eof()) break;
		my_treap.insert(key,&(my_treap.top));
		forrand++;
	}while (1);
	
	if (!my_treap.height(my_treap.top)){
		std::cout << "Tree is empty! Program terminated!\n";
		exit(1);
	}
	//printing content of the file
	file.clear();
	file.seekg(0, file.beg);
	std::cout << "INPUT = ";
	do{
		file>>key;
		if (file.eof()) break;
		std::cout << key << " ";
	}while(1);
	std::cout << std::endl << std::endl;
	file.close();

	//searching for new_key if it is found print the treap,
	//if not add new_key to the treap and print the result.
	if (my_treap.search(my_treap.top,new_key)){
		std::cout << "Element " << new_key << " is found!\n\n";
		std::cout << "Builded treap:\n";
		my_treap.print(my_treap.top,my_treap.height(my_treap.top));
	}
	else{ 
		std::cout << "Element isn't here. So that we need to add it.\n\n";
		std::cout << "Treap without new element:\n";
		my_treap.print(my_treap.top,my_treap.height(my_treap.top));
		my_treap.insert(new_key,&(my_treap.top));
		std::cout << "Treap with new element:\n";
		my_treap.print(my_treap.top,my_treap.height(my_treap.top));
	}
return 0;
}

