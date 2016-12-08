#ifndef PARSER
#define PARSER

#include "instance.h"

char * readLine(FILE * file);
Instance * readFile(char * fileName);
Instance * readInstance(FILE * file, Instance * instance);

#endif
