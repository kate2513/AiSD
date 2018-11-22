#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include "structures.h"

int main(){

int level=0,bt_depth=0;
int length=0,elMax=0;
std::ifstream file;

char name[20];

//string which contains bt
std::string str_bt;

//choice of terminal or file mode
std::cout << "Type 1 to proceed in terminal, and 2 to use file.\n(else you will be forced to use file)" << std::endl;
	std::getline(std::cin,str_bt);
	if (str_bt[0]=='1'){
		std::cout << "Enter a binary tree, which you want to convert in forest:" << std::endl;
		std::getline(std::cin,str_bt);
	}
	else{
		std::cout << "Please, type the name of the file in format <name>.txt" << std::endl;
		std::cin.getline(name,20);
		file.open(name);
		if (!file.is_open()){
			std::cout << "\nFile couldn't be open\nProgram terminated!" << std::endl;
			return 0;
		}
		std::getline(file,str_bt);
		file.close();
	}

std::cout << "\nYour output is " << str_bt << std::endl;

//length of the string
length=str_bt.length();

//level - уровень, где находимся, bt_depth считает глубину дерева
for (int i=0;i<length;i++){
	if (str_bt[i]=='(')
		 level++;
	if (str_bt[i]==')')
		 level--;
	if (bt_depth<level) bt_depth=level;
}

if (level){
	std::cout <<"\nError! Brackets aren't closed!\nProgram terminated!" << std::endl;
	return 0;
}

if (!bt_depth){
	std::cout << "\nError! It is not a tree!\nProgram terminated!" << std::endl;
	return 0;
}

//counting maximum numbers of elements in tree (2^bt_depth - 1)
elMax=(int)pow(2.0,(double)bt_depth)-1;

std::cout << "\nAdditional steps:" << std::endl;

//creation of bin tree class
binTree<char> user_bt(bt_depth);
int curr_pos=0;
if (str_bt[curr_pos]=='('){
	curr_pos++;
	fill_from_str(&user_bt,str_bt,&curr_pos,-1);
}
else{
	std::cout << "\nError! No open bracket!\nProgram terminated!" << std::endl;
	return 0;
}

std::cout << "\n"<< "Binary tree:" << std::endl;

//printing binary tree
user_bt.print_tree(0,bt_depth);

// creation of forest
Forest<char> user_forest(elMax+1,bt_depth,bt_depth);

//for position in forest
int posf=1;

//filling forest from binary tree with convertation 
convert_bt_to_forest(&user_bt,&user_forest,0,0,&posf,0);

std::cout << "\n"<< "Forest:" << std::endl;

//printing forest
user_forest.print_forest(0,bt_depth);

//for output forest in horizontal order
std::string * levels= new std::string[bt_depth];

//filling strings with levels
user_forest.print_horizontal(levels,0,0);
int index=0;

std::cout << "\n"<< "Forest in horizontal order: ";
//output in horizontal order
	while(index<bt_depth){
		std::cout << levels[index];
		index++;
	}
	std::cout << std::endl;

delete [] levels;
return 0;
}

