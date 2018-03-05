/*
DV2: Algoritmer och problemlösning.
File: rundfa.c
Name: Adam Lindgren & Jakob Lundin.
CS-user: dv17aln & c14jln
Date: 28 Februari 2018
Description: TODO
Required input: A file path with instructions for the DFA and a filepath with
				text to match against the DFA.
Output: It writes to terminal if it matches or not with the given DFA.
*/

#include "rundfa.h"
#include "table.h"


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


//Declaration of helpfunctions.
static FILE *openFile(char *file);
static void validateParams(int argc);
static void usageText(void);
static void freeCon(connections *con);
static void freeHeader(dfaHeader *h);
static void extractHeader(dfaType *dfa, char *headerStr, bool isAccepted);

int main(int argc, char **argv){
	validateParams(argc);
	FILE *fp = openFile("test");
	dfaType *dfa = buildDfaType(fp);

	//TODO
	//GLÖM INTE BORT FILINLÄSNING DUMFAN.

	char *str = "111111111111";
	int i = 0;
	char *activeNode = dfa_getStart(dfa);
	char *c = malloc(sizeof(char)*2);
	c[1] = '\0';
		printf("\nmain:\n");
	while(str[i]){
		c[0] = str[i];
		printf("%s", activeNode);
		activeNode = dfa_traverse(dfa, activeNode, c);
		printf(" -%s-> %s\n\n", c, activeNode);
		i++;
	}
	if (dfa_checkAccepted(dfa, activeNode)){
		printf("OJJ, det funkar (kanske)\n");
	}

	dfa_kill(dfa);
	free(c);
	fclose(fp);
	return 0;
}

dfaHeader *createHeader(FILE *fp){
	dfaHeader *h = headerInit();
	fgets(h->start, MAX_LINE_SIZE, fp);
	fgets(h->accepted, MAX_LINE_SIZE, fp);
	fgets(h->misc, MAX_LINE_SIZE, fp);
	return h;
}

bool inputConnection(connections *con, FILE *fp){
	char *line = calloc(sizeof(char),MAX_LINE_SIZE);
	if (fgets(line, MAX_LINE_SIZE, fp) == NULL){
		free(line);
		return false;
	}
	int i = 0;
	i = extractWord(line, con->orig, i);
	i = extractWord(line, con->input, i);
	extractWord(line, con->dest, i);
	free(line);
	return true;
}

dfaHeader *headerInit(void){
	dfaHeader *h = malloc(sizeof(dfaHeader));
	h->start = calloc(sizeof(char), MAX_LINE_SIZE);
	h->accepted = calloc(sizeof(char), MAX_LINE_SIZE);
	h->misc = calloc(sizeof(char), MAX_LINE_SIZE);
	return h;
}

connections *connectionsInit(void){
	connections *con = malloc(sizeof(connections));
	con->orig = calloc(sizeof(char), MAX_LABEL_LENGTH);
	con->dest = calloc(sizeof(char), MAX_LABEL_LENGTH);
	con->input = calloc(sizeof(char), MAX_LABEL_LENGTH);
	return con;
}

dfaType *buildDfaType(FILE *fp) {

	dfaHeader *h = createHeader(fp);

	extractWord(h->start, h->start, 0);
	dfaType *dfa = dfa_init(NODE_CAPACITY, h->start, INPUT_RANGE);

	//Extract the accepted end state/states.
	extractHeader(dfa, h->accepted, true);

	//Extract the rest of the states.
	extractHeader(dfa, h->misc, false);

	connections *con = connectionsInit();
	while (inputConnection(con, fp)){
		printf("%s -%s-> %s\n", con->orig, con->input, con->dest);
		dfa_addConnection(dfa, con->orig, con->input, con->dest);
		con->input = calloc(sizeof(char), MAX_LABEL_LENGTH);
	}

	freeHeader(h);
	freeCon(con);
	return dfa;
}

int extractWord(char *line, char *str, int i){
	int j = 0;
	while ((line[i] != ' ') && (line[i] != '\0')){
		if (line[i] == '\n' || line[i] == '\r'){
			i++;
			continue;
		}
		str[j] = line[i];
		i++;
		j++;
	}
	str[j] = '\0';
	i++;
	printf("%s\n", str);
	return i;
}


//Defining helpfunctions.


/* Function:	extractHeader
 * Description:	Extracts the words that indicates the accepted states and the
 				rest of the states of the given DFA.
 * Input:		A dfaType pointer, the string you want to extract words from and
 				a boolean if it's the accepted part of the header or not.
 * Output:		None.
 */
static void extractHeader(dfaType *dfa, char *headerStr, bool isAccepted) {
	char *headerTemp;
	int i = 0;

	while (headerStr[i]){
		headerTemp = calloc(sizeof(char), MAX_LABEL_LENGTH);
		i = extractWord(headerStr, headerTemp, i);
		dfa_addNode(dfa, headerTemp);
		if(isAccepted) {
			dfa_setAccepted(dfa, headerTemp);
		}
	}
}


/* Function:	openFile
 * Description:	Opens a file, if not possible it exits the program and gives
 				an error message.
 * Input:		A string with the filepath.
 * Output:		File pointer.
 */
static FILE *openFile(char *file){
	FILE *fp = fopen(file, "r");

	if(fp == NULL) {
		fprintf(stderr, "Couldn't open input file %s\n", file);
		exit(2);
	}
	return fp;
}


/* Function:	validateParams
 * Description: Validates the inparameters for the program. If no paramters or
 				too few are given, the program prints the usage text and exits
				the program.
 * Input:		An integer with the amount of parameters.
 * Output:		None.
 */
static void validateParams(int argc){
	if(argc != 2) {
		usageText();
	}
}


/* Function:	usageText
 * Description:	Prints the program argument syntax and exits the program.
 * Input:		None.
 * Output:		None.
 */
static void usageText(void){
    printf("\nUSAGE:\n");
    printf("rundfa [DFA FILE] [INPUT FILE]\n\n");
	exit(1);
}


/* Function:	freeCon
 * Description:	Frees the resources previously allocated
 				to the connections struct.
 * Input:		A connections pointer.
 * Output:		None.
 */
static void freeCon(connections *con){
	free(con->orig);
	free(con->input);
	free(con->dest);
	free(con);
}


/* Function:	freeHeader
 * Description:	Frees the resources previously allocated
 				to the dfaHeader struct.
 * Input:		A dfaHeader pointer.
 * Output:		None.
 */
static void freeHeader(dfaHeader *h){
	free(h->accepted);
	free(h->misc);
	free(h);
}
