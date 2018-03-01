#include "dfaType.h"
#include <stdio.h>

typedef struct{
	char *label;
	table *connections;
}dfaNode;

struct dfaType{
  size_t range;
  char *start;
  table *nodes;
  table *accepted;
};

static void freeNode(void *n);

static char *nodeGetLabel(dfaNode *n);

static dfaNode *getNode(dfaType *dfa, char *str);

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

size_t hashFunc(void *key){
	int e = 0;
	char *str = key;
	for (int i = 0; str[i]; i++) {
			e += str[i];
	}
	return e;
}

/* Function:	nodeGetLabel
 * Description:	Returns label string of given dfaNode
 * Input:		dfaNode
 * Output:		string
 */
static char *nodeGetLabel(dfaNode *n){
	return n->label;
}

/* Function:	nodeFree
 * Description:	frees all allocated memory in dfaNode structure
 * Input:		dfaNode
 * Output:		-
 */
static void freeNode(void *v){
	dfaNode *n = v;
	table_kill(n->connections);
	//free(n->label);
	free(n);
}

/* Function:	getNode
 * Description:	Returns the node corresponding to the given string.
 * Input:		dfaNode, string
 * Output:		dfaNode
 */
static dfaNode *getNode(dfaType *dfa, char *str){
	return table_lookup(dfa->nodes, str);
}


dfaType *dfa_init(size_t cap, char *start, size_t range){
	dfaType *dfa = malloc(sizeof(dfaType));
	dfa->range = range;
	dfa->start = start;
	dfa->nodes = table_empty(cap, &stringcmp, &hashFunc, *free, &freeNode);
	dfa->accepted = table_empty(cap, &stringcmp, &hashFunc, NULL, NULL);
	return dfa;
}

char *dfa_getStart(dfaType *dfa){
	char *s = dfa->start;
	return s;
}

void dfa_addNode(dfaType *dfa, char *label){
	dfaNode *n = malloc(sizeof(dfaNode));
	n->label = label;
	n->connections = table_empty(dfa->range, stringcmp, hashFunc,
		                         *free, NULL);
	table_insert(dfa->nodes, (void*)label, n);
}


void dfa_addConnection(dfaType *dfa, char *orig, char *input, char *dest){
	dfaNode *origNode = getNode(dfa, orig);
	dfaNode *destNode = getNode(dfa, dest);
	table *t = origNode->connections;
	table_insert(t, input, destNode);
}


void dfa_setAccepted(dfaType *dfa, char *label){
	dfaNode *n = getNode(dfa, label);
	table_insert(dfa->accepted, nodeGetLabel(n), n);
}


void dfa_kill(dfaType *dfa){
	table_kill(dfa->nodes);
	table_kill(dfa->accepted);
	free(dfa->start);
	free(dfa);

}


char *dfa_traverse(dfaType *dfa, char *orig, char *input){
	dfaNode *origNode = getNode(dfa, orig);
	dfaNode *destNode = table_lookup(origNode->connections, input);
	if (destNode != NULL) {
		return nodeGetLabel(destNode);
	} else {
		fprintf(stderr, "\nINVALID INPUT FOR THIS DFA: '%s'\n", input);
		printf("Exiting....\n");
		exit(2);
	}
}


bool dfa_checkAccepted(dfaType *dfa, char *endNodeLabel){
	if (table_lookup(dfa->accepted, endNodeLabel)) {
		return true;
	} else {
		return false;
	}
}
