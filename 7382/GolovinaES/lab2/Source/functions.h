
typedef struct Element{
	char* atom;
	int tag;
	struct Element* next;
	struct Element* down;
} Element;

Element * createNewEl(char* atom, int tag, Element* prev, Element* up);

Element* makeList(int * level, Element ** up, FILE ** text);

void clearList(Element * El);

void check_mistakes(Element * El);
