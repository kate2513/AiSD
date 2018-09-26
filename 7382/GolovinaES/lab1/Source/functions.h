//constants for color output in function printf
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Function, which takes file sequence.txt and use it to show the depth of recursion
void recursion_depth(int k);

// Function, which check 2 symbols in string, are they digits or not. Yes = 1, No = 0
int numbers(char * str, int index);

// Function, which check 3 symbols in string, are they letters or not. Yes = 1, No = 0
int name(char * str, int index);

// Function, which check if string is parametr
int parametr(char* str, int * index, FILE ** f);

// Function, which check if string is list_of_parametr
int list_of_parametrs(char*,int*,FILE**);
