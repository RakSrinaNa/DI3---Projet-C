#ifndef UNIT
#define UNIT

#include <sys/param.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void unit_error(char * str);

int unit_arrayEquals(int * base, int * compare, int length);

#endif
