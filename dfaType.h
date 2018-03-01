/*
DV2: Algoritmer och problemlösning.
File: dfaType.h
Name: Adam Lindgren & Jakob Lundin.
CS-user: dv17aln & c14jln
Date: 28 Februari 2018
Description: Creates a definite finite automaton.
*/

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
 * Description:	Adds ASCII values of each character in string
 * Input: 		A string to be hashed
 * Output:		An integer with the hash value
 */
size_t hashFunc(void *key);


/* Function:	dfa_init
 * Description:	Creates new dfaType structure, initiated with start node.
 * Input:		An integer for dfa capacity, a string for the start state and
 				an integer for the range of the input alphabet.
 * Output:		A dfaType pointer.
 */
dfaType *dfa_init(size_t cap, char *start, size_t range);


/* Function:	dfa_getStart
 * Description:	Returns the start state.
 * Input:		A dfaType pointer.
 * Output:		A string.
 */
char *dfa_getStart(dfaType *dfa);


/* Function:	addNode
 * Description:	Creates dfaNode with label,and adds it to table of nodes in
 				dfaType with label as key
 * Input:		A dfaType and a string with the label.
 * Output:		None.
 */
void dfa_addNode(dfaType *dfa, char *label);


/* Function:	dfa_addConnection
 * Description:	Finds the origin dfaNode and adds dest to connection tabLe
 				with str as key
 * Input:		dfaType, key string, origin node name, destination node name
 * Output:		-
 */
void dfa_addConnection(dfaType *dfa, char *orig, char *input, char *dest);


/* Function:	dfa_setAccepted
 * Description:	Adds a node label to the accepted table in dfaType.
 * Input:		A dfaType pointer and a string with the label.
 * Output:		None.
 */
void dfa_setAccepted(dfaType *dfa, char *label);


/* Function:	dfa_kill
 * Description: Frees memory allocated to the given dfaType.
 * Input:		A dfaType pointer.
 * Output:		None.
 */
void dfa_kill(dfaType *dfa);


/* Function:	dfa_traverse
 * Description:	Traverses the dfaType to the next state if the given input
 				exists within the current states connections.
 * Input:		A dfaType pointer, a string with the current states label
 				and a string with the input.
 * Output:		A string.
 */
char *dfa_traverse(dfaType *dfa, char *orig, char *input);


/* Function:	dfa_checkAccepted
 * Description: Sees if the ending state is one of the accepted end states.
 * Input:		a dfaType pointer and a string with the ending states label.
 * Output:		Boolean.
 */
bool dfa_checkAccepted(dfaType *dfa, char *endNodeLabel);

#endif
