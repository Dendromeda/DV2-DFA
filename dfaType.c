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

void nodeFree(dfaNode *n){
	table_kill(n->connections, free, free);
	free(t->label);
	free(n);
}

char *nodeGetLabel(dfaNode *n){
	return n->label;
}

dfaType *dfaInit(size_t cap, char *start, size_t range){
	dfaType *dfa = malloc(sizeof(dfaType));
	dfa->range = range;
	dfa->start = start;
	dfa->accepted = table_empty(cap, stringcmp, hashFunc);
	dfa->nodes = table_empty(cap, stringcmp, hashFunc);
}

dfaNode *addNode(dfaType *dfa, char *label){
	dfaNode *n = malloc(sizeof(dfaNode));
	n->label = label;
	n->connections = table_empty(dfa->range, stringcmp, hashFunc);
	table_insert(dfa->nodes, label, n);
	return n;
}

void addConnection(dfaType *dfa, char *orig, char *input, char *dest){
	dfaNode *origNode = table_lookup(dfa->nodes, orig);
	dfaNode *destNode = table_lookup(dfa->nodes, dest);
	table_insert(origNode->connections, input, destNode);
}

void setAccepted(dfaType *dfa, dfaNode *n){
	table_insert(dfa->accepted, getLabel(n), n);
}

void dfaKill(dfaType *dfa){
	table_kill(dfa->nodes, free, freeNode);
	table_kill(dfa->accepted, free, NULL);

}

dfaNode *dfaTraverse(dfaType *dfa, dfaNode *origNode, char *str){
	dfaNode *destNode = table_lookup(n->connections, str);
	if (destNode != NULL){
		return destNode;
	} else {
		printf("Va.\n");
		return origNode;
	}
}

bool checkAccepted(dfaType *dfa, char *str){
	if (table_lookup(dfa->accepted, str)){
		return true;
	} else {
		return false;
	}
}
