#include <stdio.h>
#include <stdlib.h>

#include "objectUnit.h"
#include "stringUtilsUnit.h"
#include "instanceUnit.h"

int mainUnit()
{
    printf("Executing stringUtils tests...");
    stringUtilsTests();
    printf("OK\n");
    printf("Executing object tests...");
    objectTests();
    printf("OK\n");
    printf("Executing instance tests...");
    instanceTests();
    printf("OK\n");
	return 0;
}
