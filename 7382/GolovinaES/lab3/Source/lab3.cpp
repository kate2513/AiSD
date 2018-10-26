#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#define N 500

template <class Type>
struct Stack {
	//constructor
	Stack():topElem(0)
	{}
	//destructor
	~Stack()
	{
		StackElem * temp=topElem;
		while(temp != NULL){
			topElem=topElem->next;
			delete temp;
			temp=topElem;
		}
	}
	//add element
	void push(Type val){
		StackElem* temp;
		temp = new StackElem;
		temp->value=val;
		temp->next=topElem;
		topElem=temp;
	}
	//remove element
	Type pop(){
		StackElem * temp=topElem;
		if (topElem){
			Type val = topElem->value;
			topElem = topElem->next;
			delete temp;
			return val;
		}
		else{
			std::cout << "Stack is empty!" << std::endl;
			return 0;
		}
	}
	//check emptiness
	bool isEmpty(){
		if (topElem==NULL) return true;
		else return false;
	}
	//take top element
	Type top(){
		return topElem->value;
	}
	//count quantity of elements in stack
	int count(){
		StackElem * temp=topElem;
		int counter=0;
		while (temp!=NULL){
			counter++;
			temp=temp->next;
		}
	return counter;
	}
	//print elements
	void print(){
		StackElem * temp=topElem;
		while(temp!=NULL){
			std::cout << "\t" << temp->value << std::endl;
			temp=temp->next;
		}
	}
	struct StackElem{
		Type value;
		StackElem * next;
	};
	StackElem * topElem;
};


int main(){
	char symbol;
	int * num = new int[3];
	num[0]=-1;num[1]=-1;num[2]=-1;
	char* str = new char[N];
	int index=0,counter=0;
	FILE * txt_file;

	//choice of terminal or file mode
	std::cout << "Type 1 to proceed in terminal, and 2 to use file.\n(else you will be forced to use file)" << std::endl;
	std::cin.getline(str,2);
	symbol=str[0];
	if (symbol=='1'){
		std::cin.getline(str,N);
		txt_file = fopen("../in.txt","w+");
		fputs(str,txt_file);
		fclose(txt_file);
		txt_file = fopen("../in.txt","r");
	}
	else{
		std::cout << "Please, type the name of the file in format <name>.txt" << std::endl;
		std::cin.getline(str,N);
		str[strlen(str)]='\0';
		txt_file = fopen(str,"r");
		if (txt_file == NULL){
			printf("File not existed!\n");
			return 0;
		}
	}

	//output of the string
	fpos_t txt_pointer;
	fgetpos(txt_file,&txt_pointer);
	std::cout << "RECIEVED FORMULA:" << std::endl;
	fgets(str,N,txt_file);
	std::cout << str << std::endl;
	fsetpos(txt_file,&txt_pointer);

	//creating stack with values of type char
	Stack<char> new_stack; 

	//filling stack with digits and operations(m,M)
	while(1){
		if (feof(txt_file)) break;
		symbol=fgetc(txt_file);
		if (isdigit(symbol) || isalpha(symbol)){
			new_stack.push(symbol);
		}
	}
	fclose(txt_file);

	//output of stack
	std::cout << "Stack:" <<std::endl;
	new_stack.print();

	std::cout << "Steps:" <<std::endl;
	counter=new_stack.count();
	//counting of the result
	while(counter){
		switch (new_stack.top()){
			case 'm':
				if (index-2<0){
					std::cout << "Incorrect data!(m)" << std::endl;
					return 0;
				}
				std::cout<<"Min("<<num[index-1]<<","<<num[index-2]<<") = ";
				new_stack.pop();
				num[index-2]=std::min(num[index-1],num[index-2]);
				std::cout << num[index-2] << std::endl;
				index--;
				break;
			case 'M':
				if (index-2<0){
					std::cout << "Incorrect data!(M)" << std::endl;
					return 0;
				}
				std::cout<<"Max("<<num[index-1]<<","<<num[index-2]<<") = ";
				new_stack.pop();
				num[index-2]=std::max(num[index-1],num[index-2]);
				std::cout << num[index-2] << std::endl;
				index--;
				break;
			default:
				if (isdigit(new_stack.top())){
					num[index]=new_stack.pop() - '0';
					index++;
				}
				else{
					std::cout << "Incorrect data!(digit)" << std::endl;
					return 0;
				}
				break;
		}
		counter--;

	}
	std::cout << "Result = " << num[0] << std::endl;
	remove("in.txt");
	delete [] str;
	delete [] num;

return 0;
}
