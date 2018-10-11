#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

#define N 500

int main(){
char * name;
int answer;
FILE * file;

fputs("Type 1 to proceed in terminal, and 2 to use file.\n(else you will be forced to use file)\n",stdout);
scanf("%d",&answer);
if (answer==1){
	scanf("\n");
	name=(char*)malloc(sizeof(char)*N);
	fgets(name,N,stdin);
	file=fopen("input.txt","w+");
	fputs(name,file);
	fclose(file);
	file=fopen("input.txt","r");
}
else{
	fputs("Please, type the name of the file in format <name>.txt\n",stdout);
	scanf("\n");
	name=(char*)malloc(sizeof(char)*N);
	fgets(name,N,stdin);
	name[strlen(name)-1]='\0';
	file = fopen(name,"r");
	if (file == NULL){
		printf("File not existed!\n");
		return 0;
	}
}

fpos_t txt_pointer;
fgetpos(file,&txt_pointer);
fgets(name,N,file);
printf("\nINPUT EXPRESSION:\n");
printf("%s\n",name);
fsetpos(file,&txt_pointer);

printf("\nSTEPS:\n");
char symbol;
int level=0;
Element * Head=NULL;
Element * El;
Element * Up=NULL;
int tag;
Head=makeList(&level,&Up,&file);
symbol=fgetc(file);
fclose(file);
/*
El=Head;
while(El!=NULL){
	printf("\npointer =%p\n",El);
	printf("atom =%s\n",El->atom);
	printf("tag =%i\n",El->tag);
	printf("next =%p\n",El->next);
	printf("down =%p\n",El->down);
	if (El->next != NULL){
		El=El->next;
		continue;
	}
	El=El->down;
	}
El=Head;
printf("_______________________________________");
while(El!=NULL){
	printf("\npointer =%p\n",El);
	printf("atom =%s\n",El->atom);
	printf("tag =%i\n",El->tag);
	printf("next =%p\n",El->next);
	printf("down =%p\n",El->down);
	if (El->down != NULL){
		El=El->down;
		continue;
	}
	El=El->next;
	}
*/
file=fopen("log.txt","a");
if (file == NULL)
	file=fopen("log.txt","w+");
//printf("level = %d\n",level);
if (level!=0)
	fprintf(file,"Brackets do not match!\n");
if (symbol!='\n')
	fprintf(file,"Arguments out of brackets!\n");
if (Head != NULL) El=Head;
else{
	printf("List is empty!\n");
	return 0;
}
fclose(file);

name[0]=0;
check_mistakes(Head);
file=fopen("log.txt","r");
if (file==NULL)
	printf("\nSyntactically correct!\n");
else{
	fgetpos(file,&txt_pointer);
	fgets(name,N,file);
	if (name[0] == 0)
		printf("\nSyntactically correct!\n");
	else{
		fsetpos(file,&txt_pointer);
		printf("\n\nSyntactically incorrect!\nAll errors:\n");
		while (1){
			fgets(name,500,file);
			if (feof(file)) break;
			printf("%s",name);
		}
	}
}
free(name);
fclose(file);
remove("log.txt");
remove("input.txt");
clearList(Head);
return 0;
}
