#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"


// Function, which takes file sequence.txt and use it to show the depth of recursion
void recursion_depth(int k){
	printf("\nRECURSION DEPTH:\n");
	char tab[100]="";
	char str[20];
	FILE *file = fopen("./sequence.txt","r");
	while (1){
		fgets(str,20,file);
		if (feof(file)) break;
		printf("%s%s",tab,str);
		strcat(tab,"  ");
	}
	str[strlen(str)-1]='\0';
	if (!k)
		printf("\nMistake in \"%s\". Incorrect data.\nString isn't list of parametrs.\n",str);
	else
		printf("\nCorrect data.\nString is list of parametrs.\n");
	fclose(file);
}


// Function, which check 2 symbols in string, are they digits or not. Yes = 1, No = 0
int numbers(char * str, int index){
	for (int i=index+1;i>index-1;i--){
		if (!isdigit(str[i]))
			return 0;
	}
printf("%c %c = digit digit\n",str[index],str[index+1]);
return 1;
}


// Function, which check 3 symbols in string, are they letters or not. Yes = 1, No = 0
int name(char * str, int index){
	for (int i=index+2;i>index-1;i--){
		if (!isalpha(str[i]))
			return 0;
	}
printf("%c %c %c = letter letter letter\n",str[index],str[index+1],str[index+2]);
return 1;
}


// Function, which check if string is parametr
int parametr(char* str, int * index, FILE ** f){
	int start_index=*index;
	fprintf(*f,"parametr\n");
	if (name(str,*index)){
		(*index)+=3;
		if (str[(*index)]=='='){
			(*index)++;
			if (numbers(str,*index)){
				(*index)+=2;
				for (int i=start_index;i<*index;i++){
					printf("%c",str[i]);
				}
				printf(" = parametr\n");
				return 1;
			}
			else{
				if (str[*index]=='('){
					(*index)++;
					if (list_of_parametrs(str,index,f))
						if (str[*index]==')'){
							(*index)++;
							return 1;
						}
				}
			}
		}
	}
return 0;
}


// Function, which check if string is list_of_parametr
int list_of_parametrs(char * str, int * index, FILE ** f){
	fprintf(*f,"list_of_parametrs\n");
	if (parametr(str,index,f)){
		if (str[*index]=='\0' || str[*index]==')'){
			return 1;
		}
		else{
			if (str[*index]==','){
				(*index)++;
				return list_of_parametrs(str,index,f);
			}
		}
	}
return 0;
}
