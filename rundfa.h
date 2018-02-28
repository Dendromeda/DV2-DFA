#include "dfaType.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 256
#define NODE_CAPACITY 64
#define MAX_LABEL_LENGTH 16
#define INPUT_RANGE 2

typedef struct connections connections;

typedef struct dfaHeader dfaHeader;

dfaHeader *createHeader(FILE *fp);

void inputConnection(dfaType *dfa, FILE *fp);

dfaHeader *headerInit(void);

void readLine(char *str, FILE *fp);

dfaType *buildDfaType(dfaHeader *header);
