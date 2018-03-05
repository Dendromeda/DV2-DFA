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
 * Description:	TODO
 * Input:		A file pointer.
 * Output:		A dfaHeader pointer.
 */
dfaHeader *createHeader(FILE *fp);


/* Function:	inputConnection
 * Description:	TODO
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


/* Function:	readLine
 * Description:	TODO
 * Input:		A string and a file pointer.
 * Output:		None.
 */
void readLine(char *str, FILE *fp);


/* Function:	buildDfaType
 * Description:	TODO
 * Input:		A file pointer.
 * Output:		A dfaType pointer.
 */
dfaType *buildDfaType(FILE *fp);


/* Function:	extractWord
 * Description:	TODO
 * Input:		A string with the input line and a string for the extracted
 				word and an integer with the index where the word will be read
				in the input line.
 * Output:		An integer.
 */
int extractWord(char *line, char *str, int i);
