#include "dfaType.h"

struct {
	char *label;
	table *connections;
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

void nodeFree(dfaNode *n){
	table_kill(n->connections, free, free);
	free(t->label);
	free(n);
}

char *nodeGetLabel(dfaNode *n){
	return n->label;
}

dfaType *dfaInit(size_t cap, char *start, int range){
	dfaType *dfa = malloc(sizeof(dfaType));
	dfa->range = range;
	dfa->start = NULL;
	dfa->accepted = table_empty(cap, stringcmp, hashFunc);
	dfa->nodes = table_empty(cap, stringcmp, hashFunc);
}

void addNode(dfaType *dfa, char *label){
	dfaNode *n = malloc(sizeof(dfaNode));
	n->label = label;
	n->connections = table_empty(dfa->range, stringcmp, hashFunc);
	table_insert(dfa->nodes, label, n);
}

void addConnection(dfaType *dfa, char *str, char *orig, char *dest){
	dfaNode *n = table_lookup(dfa->nodes, orig);
	table_insert(n->connections, str, dest);
}

void setAccepted(dfaType *dfa, char *label){
	table_insert(dfa->accepted, label, NULL);
}

void dfaKill(dfaType *dfa){
	table_kill(dfa->accepted, free, free);
	table_kill(dfa->nodes, free, freeNode);

}

dfaNode *dfaTraverse(dfaType *dfa, dfaNode *n, char *str){
	char *key = table_lookup(n->connections, key);
	if (key){
		return table_lookup(dfa, key);
	}
}

bool checkAccepted(dfaType *dfa, char *str){
	if (table_lookup(dfa->accepted, str)){
		return true;
	} else {
		return false;
	}
}
