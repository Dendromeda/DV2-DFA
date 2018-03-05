/*
DV2: Algoritmer och problemlösning.
File: rundfa.h
Name: Adam Lindgren & Jakob Lundin.
CS-user: dv17aln & c14jln
Date: 28 Februari 2018
Description: Creates a DFA through a given file with the start state, accepted
			 states and other states and their transitions. It also matches a
			 given file against this DFA.
Required input: A file path with instructions for the DFA and a filepath with
				text to match against the DFA.
Output: It writes to terminal if the given file matches with the given DFA.
*/

#include "dfaType.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_LINE_SIZE 256
#define NODE_CAPACITY 2
#define MAX_LABEL_LENGTH 16
#define INPUT_RANGE 2
#define MAX_STRING_SIZE 128

typedef struct connections connections;

typedef struct dfaHeader dfaHeader;


/* Function:	createHeader
 * Description:	Reads the first three lines in the given file and creates
 				a dfaHeader struct.
 * Input:		A file pointer.
 * Output:		A dfaHeader pointer.
 */
dfaHeader *createHeader(FILE *fp);


/* Function:	inputConnection
 * Description:	Extracts the transistions from the given file line and puts them
 				in the connections struct.
 * Input:		A connections pointer and a file pointer.
 * Output:		Boolean.
 */
bool inputConnection(connections *con, FILE *fp);


/* Function:	headerInit
 * Description:	Initiates a dfaHeader struct.
 * Input:		None.
 * Output:		A dfaHeader pointer.
 */
dfaHeader *headerInit(void);


/* Function:	connectionsInit
 * Description:	Initiates a connections struct.
 * Input:		None.
 * Output:		A connections pointer.
 */
connections *connectionsInit(void);


/* Function:	buildDfaType
 * Description:	Builds the DFA from the given file.
 * Input:		A file pointer.
 * Output:		A dfaType pointer.
 */
dfaType *buildDfaType(FILE *fp);


/* Function:	extractWord
 * Description:	Extracts the first word it encounters from the given string
 				pointer
 * Input:		A string with the input line and a string for the extracted
 				word and an integer with the index where the word will be read
				in the input line.
 * Output:		An integer.
 */
int extractWord(char *line, char *str, int i);
