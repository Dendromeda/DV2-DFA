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

dfaHeader *createHeader(FILE *fp);

bool inputConnection(conns *con, FILE *fp);

dfaHeader *headerInit(void);

void readLine(char *str, FILE *fp);

dfaType *buildDfaType(FILE *fp);

int extractWord(char *line, char *str, int i);
