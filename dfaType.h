#ifndef DFATYPE_H
#define DFATYPE_H

#include "table.h"

typedef struct dfaNode dfaNode;
typedef *nodeFunc(void*);
struct {
	char *label;
	table *connections;
	nodeFunc func;
};

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
	}
	return 1;
}

int hashFunc(char *str){
	int e = 0;
	for (int i = 0; str[i]; i++){
			e += str[i];
	}
	return e;
}

char *nodeGetLabel(dfaNode *n){
	return n->label;
}

dfaType *dfaInit(size_t cap){
	dfaType *dfa = malloc(sizeof(dfaType));
	dfa->start = NULL;
	dfa->accepted = table_empty(cap, stringcmp, hashFunc);
	dfa->nodes = table_empty(cap, stringcmp, hashFunc);
}

dfaNode dfaMakeNode(char *label, int range, *nodeFunc func){
	dfaNode *n = malloc(sizeof(dfaNode));
	n->label = label;
	n->connections = table_empty(range, stringcmp, hashFunc);
	n->nodeFunc = func;
}

void addConnection(dfaNode *n, char *key, char *label){
	table_insert(n->connections, key, label);
}

void addNode(dfaType *dfa, dfaNode *n){
	table_insert(dfa->nodes, nodeGetLabel(n), n);
}

void setAccepted(dfaType *dfa, dfaNode *n){
	table_insert(dfa->accepted, nodeGetLabel(n), n);
}




#endif
