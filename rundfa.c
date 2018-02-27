#include "dfaType.h"
#define MAX_LINE_SIZE 256

typedef struct {
	char *start;
	char *accepted;
	char *misc;
} dfaHeader;

int main(int argc, char **argv);

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
	h->start = calloc(sizeof(char) * MAX_LINE_SIZE);
	h->accepted = calloc(sizeof(char) * MAX_LINE_SIZE);
	h->misc = calloc(sizeof(char) * MAX_LINE_SIZE);
	return h;
}

void readLine(char *str, FILE *fp){
	fgets(str, MAX_LINE_SIZE, fp);
}

dfaType *buildDfaType(dfaHeader *header, ) {

	//INTERN STRUCT?

	//GÅ IGENOM HEADER

	//SKAPA DFATYPE MED HJÄLP AV HEADERINFO

	//LÄSER CONNECTIONS WHILE LOOP
		//TA HAND OM VARJE RAD
			//FSCANF PÅ VARJE RAD
			//SPARA TILL STRUCT

		//SKAPA CONNECTIONS I DFATYPE MED HJÄLP AV INTERN STRUCT

	return d;

}
