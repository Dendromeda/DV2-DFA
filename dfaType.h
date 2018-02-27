#ifndef DFATYPE_H
#define DFATYPE_H

#include "table.h"

typedef struct dfaNode dfaNode;


bool stringcmp(void *p1, void *p2);

/* Function:	hashFunc
 * Description:	adds ASCII values of each character in string
 * Input: 		string to be hashed
 * Output:		int with hash value
 */
int hashFunc(void *str);

/* Function:	nodeFree
 * Description:	frees all allocated memory in dfaNode structure
 * Input:		dfaNode
 * Output:		-
 */
void nodeFree(dfaNode *n);

/* Function:	nodeGetLabel
 * Description:	Returns label string of given dfaNode
 * Input:		dfaNode
 * Output:		string
 */
char *nodeGetLabel(dfaNode *n);

/* Function:	dfaInit
 * Description:	Creates new dfaType structure, initiated with start node.
 * Input:		int for dfa capacity, name string of start node, and int range
 				of alphabet.
 * Output:		dfaType
 */
dfaType *dfaInit(size_t cap, char *start, int range);

/* Function:	addNode
 * Description:	Creates dfaNode with label,and adds it to table of nodes in
 				dfaType with label as key
 * Input:		dfaType, string label
 * Output:		-
 */
void addNode(dfaType *dfa, char *label);

/* Function:	addConnection
 * Description:	Finds the origin dfaNode and adds dest to connection tabLe
 				with str as key
 * Input:		dfaType, key string, origin node name, destination node name
 * Output:		-
 */
void addConnection(dfaType *dfa, char *str, char *orig, char *dest);

/* Function:	setAccepted
 * Description:	adds node label to accepted table in dfaType,
 * Input:
 * Output:
 */
void setAccepted(dfaType *dfa, char *label);

/* Function:
 * Description:
 * Input:
 * Output:
 */
void dfaKill(dfaType *dfa);

/* Function:
 * Description:
 * Input:
 * Output:
 */
dfaNode *dfaTraverse(dfaType *dfa, dfaNode *n, char *str);

/* Function:
 * Description:
 * Input:
 * Output:
 */
bool checkAccepted(dfaType *dfa, char *str);


#endif
