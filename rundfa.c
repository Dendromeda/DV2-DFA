#include "rundfa.h"
#include "table.h"


struct dfaHeader{
	char *start;
	char *accepted;
	char *misc;
};

struct conns{
	char *orig;
	char *input;
	char *dest;
};

FILE *openFile(char *file);

int main(int argc, char **argv){
	FILE *fp = openFile("test");
	dfaType *dfa = buildDfaType(fp);

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

bool inputConnection(conns *con, FILE *fp){
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

dfaType *buildDfaType(FILE *fp) {

	dfaHeader *h = createHeader(fp);

	extractWord(h->start, h->start, 0);
	dfaType *dfa = dfa_init(NODE_CAPACITY, h->start, INPUT_RANGE);

	char *headerTemp;
	int i = 0;
	while (h->accepted[i]){
		headerTemp = calloc(sizeof(char), MAX_LABEL_LENGTH);
		i = extractWord(h->accepted, headerTemp, i);
		dfa_addNode(dfa, headerTemp);
		dfa_setAccepted(dfa, headerTemp);
	}
	i = 0;
	while (h->misc[i]){
		headerTemp = calloc(sizeof(char), MAX_LABEL_LENGTH);
		i = extractWord(h->misc, headerTemp, i);
		dfa_addNode(dfa, headerTemp);
	}


	conns *con = malloc(sizeof(conns));
		con->orig = calloc(sizeof(char), MAX_LABEL_LENGTH);
		con->dest = calloc(sizeof(char), MAX_LABEL_LENGTH);
		con->input = calloc(sizeof(char), MAX_LABEL_LENGTH);
	while (inputConnection(con, fp)){
		printf("%s -%s-> %s\n", con->orig, con->input, con->dest);
		dfa_addConnection(dfa, con->orig, con->input, con->dest);
		con->input = calloc(sizeof(char), MAX_LABEL_LENGTH);
	}

	free(h->accepted);
	free(h->misc);
	free(h);

	free(con->orig);
	free(con->input);
	free(con->dest);
	free(con);

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

FILE *openFile(char *file){
	FILE *fp = fopen(file, "r");
	if(fp == NULL) {
		fprintf(stderr, "Couldn't open input file %s\n", file);
		exit(2);
	}
	return fp;
}
