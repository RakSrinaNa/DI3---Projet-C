#ifndef PARSER
#define PARSER

#include "stdio.h"
#include "instance.h"

char * readLine(FILE * file);
Instance * readFile(char * fileName);
Instance * readInstance(FILE * file, Instance * instance);
int * getValuesFromLine(char * line, int valuesNumber);

#endif
