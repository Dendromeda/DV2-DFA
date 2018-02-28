#include "rundfa.h"

struct dfaHeader{
	char *start;
	char *accepted;
	char *misc;
};

struct connections{
	char *orig;
	char *input;
	char *dest;
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

void inputConnection(connections *con, FILE *fp){
	char *line = calloc(sizeof(char),MAX_LINE_SIZE);
	fgets(line, MAX_LINE_SIZE, fp);
	int i = 0;
	int j = 0;
	while (line[i] != ' ' && line[i] != '\0'){
		con->orig[j] = line[i];
		i++;
		j++;
	}
	j = 0;
	while (line[i] != ' ' && line[i] != '\0'){
		con->input[j] = line[i];
		i++;
		j++;
	}
	j = 0;
	while (line[i] != '\0'){
		con->dest[j] = line[i];
		i++;
		j++;
	}
}

dfaHeader *headerInit(void){
	dfaHeader *h = malloc(sizeof(dfaHeader));
	h->start = calloc(sizeof(char), MAX_LINE_SIZE);
	h->accepted = calloc(sizeof(char), MAX_LINE_SIZE);
	h->misc = calloc(sizeof(char), MAX_LINE_SIZE);
	return h;
}

dfaType *buildDfaType(FILE *fp) { // range = argv[2]?

	dfaHeader *h = createHeader(fp);

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

void extractWord(char *line, char *str, int i){

}
