#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

Element * createNewEl(char* atom, int tag, Element* prev, Element* up){

	Element * temp=(Element*)malloc(sizeof(Element));
	if (prev != NULL)
		prev->next = temp;
	if (up != NULL)
		up->down = temp;
	if (tag){
		temp->atom=(char*)malloc(sizeof(char)*5);
		strcpy(temp->atom,atom);
		temp->tag=1;
	}
	else{
		temp->tag=0;
		temp->atom=NULL;
	}
	temp->next=NULL;
	temp->down=NULL;

return temp;
}


Element* makeList(int * level, Element ** up, FILE ** text){
	FILE * log;
	Element * Head;
	Element * El;
	Element * prev=NULL;
	Element * currUp=*up;
	fpos_t txt_pointer;
	int tag;
	int position=0;
	char symbol;
	char * str_symbol=(char*)malloc(sizeof(char)*5);
	printf("\n");
	for (int i=0;i<(*level);i++)
		printf("  ");
	printf("makeList level %d: start\n",(*level)+1);
	for (int i=0;i<(*level);i++)
		printf("  ");
	printf("Atoms: ");
	while (1){
		tag=1;
		str_symbol[0]=0;
		if (position) currUp=NULL;
		fgetpos(*text,&txt_pointer);
		symbol=fgetc(*text);
			if (*level==0 && position==0 && symbol=='(')
				symbol=fgetc(*text);
		if (symbol=='\n'){
			fsetpos(*text,&txt_pointer);
			return Head;
		}
		//recording of atom (+,-,*,nil,log,sqrt,4536)
		if (isdigit(symbol)){
			for (int i=0;i<5;i++){
				if (!isdigit(symbol)) break;
				strncat(str_symbol,&symbol,1);
				fgetpos(*text,&txt_pointer);
				symbol=fgetc(*text);
			}
			fsetpos(*text,&txt_pointer);
			symbol=' ';
		}
		if (isalpha(symbol)){
			if (position){
				fsetpos(*text,&txt_pointer);
				symbol='(';
				position++;
			}
			else{
				for (int i=0;i<5;i++){
					if (!isalpha(symbol)) break;
					strncat(str_symbol,&symbol,1);
					fgetpos(*text,&txt_pointer);
					symbol=fgetc(*text);
				}
				if (symbol != '(' || (strncmp(str_symbol,"log",3) && strncmp(str_symbol,"sqrt",4))){
					log=fopen("log.txt","w+");
					if (symbol != '(')
						fprintf(log,"'(' required after function!\n");
					if (strncmp(str_symbol,"log",3) && strncmp(str_symbol,"sqrt",4))
						fprintf(log,"%s is not supported function!\n",str_symbol);
					fclose(log);
				}
				if (symbol!='('){
					fsetpos(*text,&txt_pointer);
				}
				else symbol=' ';
			}
		}
		switch (symbol){
			case '(':
				tag=0;
				strncat(str_symbol,&symbol,1);
				break;
			case '+':
			case '-':
			case '*':
			case ',':
				strncat(str_symbol,&symbol,1);
				break;
			default:
				break;
		}
	//addition of new element
	if (str_symbol[0] != 0){
		if (!position){
			Head=createNewEl(str_symbol,tag,prev,currUp);
			prev=Head;
			position++;
			(*level)++;
		}
		else{
			El=createNewEl(str_symbol,tag,prev,currUp);
			prev=El;
			position++;
		}
		if (tag)
			printf("%s -> ",str_symbol);
	}
	if (symbol=='('){
		printf("nil -> ");
		if (position==1)
			makeList(level,&Head,text);
		else
			makeList(level,&El,text);
	}
	if (symbol==')'){
		printf("\n");
		for (int i=0;i<(*level)-1;i++)
			printf("  ");
		printf("makeList level %d: end\n",(*level));
		(*level)--;
		return Head;
	}
}

return Head;
}

void check_mistakes(Element * El){
	int position=0;
	FILE * log;
	while(El!=NULL){
		log=fopen("log.txt","a");
		if (log == NULL){
			log=fopen("log2.txt","w+");
		}
		if (position==0 && El->tag){
			if (El->atom[0]=='+' || El->atom[0]=='*'){
				if (El->next->next == NULL || El->next == NULL)
					fprintf(log,"Mistake! Operation %c requires >1 arguments!\n",El->atom[0]);
			}
			if (El->atom[0]=='-'){
				if (El->next == NULL){
					fprintf(log,"Mistake! Operation %c requires minimum 1 argument!\n",El->atom[0]);
				}
			}
			if (!strncmp(El->atom,"log",3)){
					if (El->next != NULL){
						if (!isdigit(El->next->atom[0]))
							fprintf(log,"Function log(,) requires numbers as arguments!\n");
						if (atoi(El->next->atom) == 1){
							fprintf(log,"Function log(a,b) requires a != 1!\n");
						}
						if (atoi(El->next->atom) < 0)
							fprintf(log,"Function log(a,b) requires a > 0!\n");
						if (El->next->next != NULL){
							if (El->next->next->atom[0] != ',')
								fprintf(log,"No ',' in function log(,)!\n");
							if (El->next->next->next != NULL){
								if (!isdigit(El->next->next->next->atom[0]))
									fprintf(log,"Function log(,) requires numbers as arguments!\n");
								if (atoi(El->next->next->next->atom) < 0)
									fprintf(log,"Function log(a,b) requires b > 0!\n");
								if (El->next->next->next->next != NULL)
									fprintf(log,"Too many arguments in function log(,)!\n");
							}
							else fprintf(log,"Function log(,) requires 2 arguments, separated with ','!\n");
						}
						else fprintf(log,"Function log(,) requires >1 arguments!\n");
					}
					else fprintf(log,"Function log(,) requires arguments!\n");
			}
 			if (!strncmp(El->atom,"sqrt",4)){
				if (El->next != NULL){
					if (!isdigit(El->next->atom[0]))
						fprintf(log,"Function sqrt() requires number as argument!\n");
					if (El->next->next != NULL)
						fprintf(log,"Function sqrt() requires 1 argument!\n");
				}
				else fprintf(log,"Function sqrt() requires 1 argument!\n");
			}
			if (El->atom[0]!='+' && El->atom[0]!='-' && El->atom[0]!='*' && El->atom[0]!='s' && El->atom[0]!='l'){
				if(!isalpha(El->atom[0]))
					fprintf(log,"Prefix form of expression required!\n");
			}
		}
		if (position && El->tag){
			if (!isdigit(El->atom[0]) && El->atom[0] != ',')
				fprintf(log,"Argument (%s) is not number!\n",El->atom);
			if (El->atom[0]=='+' || El->atom[0]=='-' || El->atom[0] == '*')
				fprintf(log,"Prefix form of expression required!\n");
		}
		position++;
		fclose(log);
		if (El->down != NULL){
			check_mistakes(El->down);
		}
		El=El->next;
	}
}

void clearList(Element * El){
	Element * temp;
	temp=El;
	while (temp != NULL){
		
		if (temp->down != NULL){
			clearList(temp->down);
		}
		temp=temp->next;
	}
	free(temp);
}

