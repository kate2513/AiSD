
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "structure.h"
#include <clocale>

int main(){

	char name[20];
	std::ifstream file;
	int key=0, new_key=0;
	int forrand=time(0);
	std::string str_treap;
	int counter=1;

	setlocale(LC_ALL, "Russian");

	//receiving file .txt
	std::cout << "Здравствуйте!\nДанная программа создана для демонстрации "
		<< "работы с БДП типа\n\"Рандомизированная пирамида поиска\"(Treap).\n"
		<< "В ходе программы будет показан:\n1) каждый шаг формирования БДП,\n"
		<< "2) как происходит поиск, добавление и удаление элментов из пирамиды.\n"
		<< "Вывод БДП реализован в виде уступчатых списков.\n"
		<< "Для начала работы, пожалуйста, введите имя файла в формате <имя_файла>.txt\n"
		<< "(текстовый файл, где у вас хранится последовательность элементов для формирования БДП)"
		<< std::endl;
	std::cin.getline(name,20);
	file.open(name);
	if (!file.is_open()){
		std::cout << "\nНевозможно открыть файл.\nПрограмма завершена!" << std::endl;
		return 0;
	}

	//receiving key for the search
	std::cout << "Введите ключ (целое число), которое вы хотите найти: ";
	std::cin >> new_key;
	std::cout << std::endl;

	std::getline(file,str_treap);
	std::cout << "Входная последовательность: \n" << str_treap << std::endl;
	file.clear();
	file.seekg(0, file.beg);
	//making class object for future treap
	randTreap<int> my_treap;

	//receiving elements from file and adding them to the treap
	do{
		srand(forrand);
		file >> key;
		if (file.eof()) break;
		std::cout << "---------------------\n";
		std::cout << "Шаг № " << counter++ << "\n";
		std::cout << "\nПрограмма приняла " << key << "\n";
                std::cout << "Сейчас произойдет поиск места для вставки.\n";
		std::cout << "Текущая БДП:\n";
		my_treap.print(my_treap.top,my_treap.height(my_treap.top));
		my_treap.insert(key,&(my_treap.top));
		forrand++;
	}while (1);
	std::cout << "---------------------\n";

	if (!my_treap.height(my_treap.top)){
		std::cout << "БДП пусто! Программа завершена!\n";
		exit(1);
	}

	file.close();

	//searching for new_key if it is found print the treap,
	//if not add new_key to the treap and print the result.
	std::cout << "Поиск элемента "<< new_key << " в БДП (по ключу)...\n";
	if (my_treap.search(my_treap.top,new_key)){
		std::cout << "Элемент " << new_key << " найден!\n";
		std::cout << "Построенное БДП:\n";
		my_treap.print(my_treap.top,my_treap.height(my_treap.top));
	}
	else{ 
		std::cout << "Элемент "<< new_key <<" не найден. Сейчас произойдет его добавление.\n";
	//	std::cout << "Пирамида без нового элемента:\n";
	//	my_treap.print(my_treap.top,my_treap.height(my_treap.top));
		std::cout << "---------------------\n";
		my_treap.insert(new_key,&(my_treap.top));
		std::cout << "---------------------\n";
		std::cout << "Пирамида с новым элементом:\n";
		my_treap.print(my_treap.top,my_treap.height(my_treap.top));
	}
return 0;
}

