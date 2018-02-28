#include "rundfa.h"

struct dfaHeader{
	char *start;
	char *accepted;
	char *misc;
};

int main(int argc, char **argv){
	return 0;
}

dfaHeader *createHeader(FILE *fp){
	dfaHeader *h = headerInit();
	readLine(h->start, fp);
	readLine(h->accepted, fp);
	readLine(h->misc, fp);
	return h;
}

void inputConnection(dfaType *dfa, FILE *fp){

}

dfaHeader *headerInit(void){
	dfaHeader *h = malloc(sizeof(dfaHeader));
	h->start = calloc(sizeof(char), MAX_LINE_SIZE);
	h->accepted = calloc(sizeof(char), MAX_LINE_SIZE);
	h->misc = calloc(sizeof(char), MAX_LINE_SIZE);
	return h;
}

void readLine(char *str, FILE *fp){
	fgets(str, MAX_LINE_SIZE, fp);
}

dfaType *buildDfaType(dfaHeader *header) { // range = argv[2]?

	struct connections{
		char *orig;
		char *input;
		char *dest;
	};

	dfaHeader *h = headerInit();
	/*int c = 0;
	for (int i = 0; h->accepted[i]; i++){  //GILLAR EJ DETTA
		if (h->accepted[i] == ' '){
			c++;
		}
	}
	for (int i = 0; h->accepted[i]; i++){
		if (h->misc[i] == ' '){
			c++;
		}
	}*/
	//SKAPA DFATYPE MED HJÄLP AV HEADERINFO
	dfaType *dfa = dfa_init(NODE_CAPACITY, h->start, INPUT_RANGE);

	char *headerTemp = calloc(sizeof(char), MAX_LABEL_LENGTH);
	int i = 0;
	while (headerTemp!= NULL){
		int j = 0;
		while (h->accepted[i] != ' '){
			headerTemp[j] = h->accepted[i];
			i++;
			j++;
		}
		headerTemp[j] = '\0';
		dfa_addNode(dfa, headerTemp);
		dfa_setAccepted(dfa, headerTemp);
		headerTemp = calloc(sizeof(char), MAX_LABEL_LENGTH);

	}
	while (headerTemp!= NULL){
		int j = 0;
		while (h->misc[i] != ' '){
			headerTemp[j] = h->misc[i];
			i++;
			j++;
		}
		headerTemp[j] = '\0';
		dfa_addNode(dfa, headerTemp);
		headerTemp = calloc(sizeof(char), MAX_LABEL_LENGTH);

	}

	//LÄSER CONNECTIONS WHILE LOOP

		//TA HAND OM VARJE RAD
			//FSCANF PÅ VARJE RAD
			//SPARA TILL STRUCT

		//SKAPA CONNECTIONS I DFATYPE MED HJÄLP AV INTERN STRUCT

	return dfa;

}
