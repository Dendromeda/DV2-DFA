#include "dfaType.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 256
#define NODE_CAPACITY 2
#define MAX_LABEL_LENGTH 16
#define INPUT_RANGE 2

typedef struct conns conns;

typedef struct dfaHeader dfaHeader;


/* Function:	createHeader
 * Description:	Creates dfaNode with label,and adds it to table of nodes in
 				dfaType with label as key
 * Input:		A dfaType and a string with the label.
 * Output:		None.
 */
dfaHeader *createHeader(FILE *fp);


/* Function:	inputConnection
 * Description:	Creates dfaNode with label,and adds it to table of nodes in
 				dfaType with label as key
 * Input:		A dfaType and a string with the label.
 * Output:		None.
 */
bool inputConnection(conns *con, FILE *fp);


/* Function:	headerInit
 * Description:	Creates dfaNode with label,and adds it to table of nodes in
 				dfaType with label as key
 * Input:		A dfaType and a string with the label.
 * Output:		None.
 */
dfaHeader *headerInit(void);


/* Function:	readLine
 * Description:	Creates dfaNode with label,and adds it to table of nodes in
 				dfaType with label as key
 * Input:		A dfaType and a string with the label.
 * Output:		None.
 */
void readLine(char *str, FILE *fp);


/* Function:	buildDfaType
 * Description:	Creates dfaNode with label,and adds it to table of nodes in
 				dfaType with label as key
 * Input:		A dfaType and a string with the label.
 * Output:		None.
 */
dfaType *buildDfaType(FILE *fp);


/* Function:	extractWord
 * Description:	Creates dfaNode with label,and adds it to table of nodes in
 				dfaType with label as key
 * Input:		A dfaType and a string with the label.
 * Output:		None.
 */
int extractWord(char *line, char *str, int i);
