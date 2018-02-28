#ifndef DFATYPE_H
#define DFATYPE_H

#include "table-hash.h"
#include <stdlib.h>

typedef struct dfaType dfaType;

/* Function:	stringcmp
 * Description:	Compares two strings, returns true if identical.
 * Input:		Two strings.
 * Output:		Boolean.
 */
bool stringcmp(void *p1, void *p2);

/* Function:	hashFunc
 * Description:	adds ASCII values of each character in string
 * Input: 		string to be hashed
 * Output:		int with hash value
 */
size_t hashFunc(void *key);

/* Function:	dfaInit
 * Description:	Creates new dfaType structure, initiated with start node.
 * Input:		int for dfa capacity, name string of start node, and int range
 				of alphabet.
 * Output:		dfaType
 */
dfaType *dfa_init(size_t cap, char *start, size_t range);

char *dfa_getStart(dfaType *dfa);

/* Function:	addNode
 * Description:	Creates dfaNode with label,and adds it to table of nodes in
 				dfaType with label as key
 * Input:		dfaType, string label
 * Output:		-
 */
void dfa_addNode(dfaType *dfa, char *label);

/* Function:	addConnection
 * Description:	Finds the origin dfaNode and adds dest to connection tabLe
 				with str as key
 * Input:		dfaType, key string, origin node name, destination node name
 * Output:		-
 */
void dfa_addConnection(dfaType *dfa, char *orig, char *input, char *dest);

/* Function:	setAccepted
 * Description:	adds node label to accepted table in dfaType,
 * Input:
 * Output:
 */
void dfa_setAccepted(dfaType *dfa, char *label);

/* Function:
 * Description:
 * Input:
 * Output:
 */
void dfa_kill(dfaType *dfa);

/* Function:
 * Description:
 * Input:
 * Output:
 */
char *dfa_traverse(dfaType *dfa, char *orig, char *input);

/* Function:
 * Description:
 * Input:
 * Output:
 */
bool dfa_checkAccepted(dfaType *dfa, char *endNodeLabel);

//DEBUGKOD
table *getNodeTable(dfaType *dfa);


typedef struct{
	char *label;
	table *connections;
}dfaNode;

#endif
