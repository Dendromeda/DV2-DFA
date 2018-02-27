#include "dfaType.h"

struct {
	char *label;
	table *connections;
} dfaNode;

typedef struct {
  size_t range;
  char *start;
  table *accepted;
  table *nodes;
} dfaType;

bool stringcmp(void *p1, void *p2){
	int i = 0;
	char *str1 = p1;
	char *str2 = p2;

	while(str1[i] != 0) {
		if (str1[i] != str2[i]) {
			return 0;
		}
		i++;
	}

	if (str2[i] != 0) {
		return 0;
	} else {
		return 1;
	}
}

int hashFunc(char *str){
	int e = 0;
	for (int i = 0; str[i]; i++){
			e += str[i];
	}
	return e;
}

static void nodeFree(dfaNode *n){
	table_kill(n->connections, free, free);
	free(t->label);
	free(n);
}

static char *nodeGetLabel(dfaNode *n){
	return n->label;
}

static dfaNode *dfa_getNode(dfaType *dfa, char *str){
	return table_lookup(dfa->nodes, str);
}

dfaType *dfaInit(size_t cap, char *start, size_t range){
	dfaType *dfa = malloc(sizeof(dfaType));
	dfa->range = range;
	dfa->start = start;
	dfa->accepted = table_empty(cap, stringcmp, hashFunc);
	dfa->nodes = table_empty(cap, stringcmp, hashFunc);
}

void addNode(dfaType *dfa, char *label){
	dfaNode *n = malloc(sizeof(dfaNode));
	n->label = label;
	n->connections = table_empty(dfa->range, stringcmp, hashFunc);
	table_insert(dfa->nodes, label, n);
}

void addConnection(dfaType *dfa, char *orig, char *input, char *dest){
	dfaNode *origNode = dfa_getNode(dfa, orig);
	dfaNode *destNode = dfa_getNode(dfa, dest);
	table_insert(origNode->connections, input, destNode);
}

void setAccepted(dfaType *dfa, char *label){
	dfaNode *n = dfa_getNode(dfa, label);
	table_insert(dfa->accepted, getLabel(n), n);
}



void dfaKill(dfaType *dfa){
	table_kill(dfa->nodes, free, freeNode);
	table_kill(dfa->accepted, free, NULL);

}

char *dfaTraverse(dfaType *dfa, char *orig, char *input){
	dfaNode *origNode = dfa_getNode(dfa, origNode);
	dfaNode *destNode = table_lookup(origNode->connections, input);
	if (destNode != NULL){
		return getLabel(destNode);
	} else {
		printf("Va.\n");
		return orig;
	}
}

bool checkAccepted(dfaType *dfa, char *endNodeLabel){
	if (table_lookup(dfa->accepted, endNodeLabel)){
		return true;
	} else {
		return false;
	}
}
