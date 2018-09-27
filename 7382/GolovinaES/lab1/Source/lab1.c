#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "functions.h"


int main(){

	//declaration of variables
	char name[22]="./";		//for the name of text file
	int input_format=0;		//0 - Terminal input, 1 - Input from file
	int index=0;		//current index of symbol in string, which is checking/going to check
	int result;			// result of program, is string "list of parametrs" or not
	long int length=100;		//length of the string
	char * s;			//pointer to the string
	char l[20];			//using to read length as string
	FILE *f=NULL;			//pointer to the text file

	//check if person want to type text in terminal or use <file>.txt
	fputs("If you want to type input in terminal  - type 0.\nIf you want to use input from file - type 1.\n",stdout);
	scanf("%d",&input_format);
	
	//asking for name of <file>.txt - 2 times. If still wrong - terminal mode is on
	if (input_format==1){
		fputs("Input from file is on.\n",stdout);
		fputs("Please, type the name of the file in format <name>.txt\n",stdout);
		scanf("\n");
		fgets(l,20,stdin);
		l[strlen(l)-1]='\0';
		strcat(name,l);
		f = fopen(name,"r");
		
		//check if pointer to the file isn't NULL
		if (!f){
			fputs("Error in opening file. There is no such file in directory or name of it was written incorrectly.\nPlease, try again.\n",stdout);	
		//	scanf("\n");
			fgets(l,20,stdin);
			l[strlen(l)-1]='\0';
			strcpy(name,"./\0");
			strcat(name,l);
			f = fopen(name,"r");
		}

		//check if pointer to the file isn't NULL - 2 time
		if (!f){
			fputs("Error in opening file.\n",stdout);
			input_format=0;
		}

		//if everything correct - read maximum length and string from <file>.txt
		if (input_format==1){
			fgets(l,20,f);
			length=strtol(l,&s,10);

			//if data is written incorrectly in file - termination of the program
			if (length<0 || length>SHRT_MAX || !length){
			fputs("Incorrect data. Program is terminated.",stdout);
			return 0;
			}

			//if data is correct - allocation memory and reading string from file
			s=(char*)malloc(sizeof(char)*length);
			fgets(s,length,f);
		}
		fclose(f);
	}

	// Terminal mode, reading length of the string (and checking if it correct) and string
	if (input_format!=1){
		fputs("Terminal input is on.\n",stdout);
		fputs("Please, type the maximum length of the string: \n\0",stdout);
		scanf("\n");

		//Check if maximum length is number and it's value in between 0 and 32767
		while (1){
			fgets(l,20,stdin);	//read length as string
			length=strtol(l,&s,10); //transformation string to integer; length=0, if it fail to transformate
			if (!length)
				fputs("Incorrect data. Please, type number: \n\0",stdout);
			else{
				if (length<INT_MAX && length>0)
					break;
				else
					fputs("Incorrect data. Please, type number < 32767  and > 0: \n\0",stdout);
			}
			scanf("\n");
		}
	
		//allocates memory for string accordiing to the maximum length of it
		s=(char*)malloc(sizeof(char)*length);
		fputs("Please, type the string:\n\0",stdout);
		scanf("\n");
		fgets(s,length,stdin);
	}

	//creating of file sequence.txt, where will be the information about what function (recursive) was on
	f= fopen("./sequence.txt","w+");

	//deleting sign of next line
	if (s[strlen(s)-1]=='\n') //maybe unnecessarily check
			s[strlen(s)-1]='\0';

	//start of recursive functions
	result=list_of_parametrs(s,&index,&f);
	fclose(f);

	//output of the string, green - correct part, red - incorrect
	printf("\nINPUT STRING:\n");
	for (int i=0;i<index;i++)
		printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET,s[i]);
	for (int i=index;i<strlen(s);i++)
		printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, s[i]);
	printf("\n");

	//output the depth of recursion
	recursion_depth(result);
	remove("sequence.txt");
free(s);

return 0;
}
