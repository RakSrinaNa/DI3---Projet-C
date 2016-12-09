#include <stdio.h>
#include <stdlib.h>

#include "objectUnit.h"
#include "parserUnit.h"
#include "instanceUnit.h"

int mainUnit()
{
    printf("Executing object tests...");
    objectTests();
    printf("OK\n");
    printf("Executing instance tests...");
    instanceTests();
    printf("OK\n");
    printf("Executing parser tests...");
    parserTests();
    printf("OK\n");
	return 0;
}
