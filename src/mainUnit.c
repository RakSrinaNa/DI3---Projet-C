#include <stdio.h>

#include "itemUnit.h"
#include "parserUnit.h"
#include "instanceUnit.h"

int mainUnit()
{
	printf("Executing item tests...");
	itemTests();
	printf("OK\n");
	printf("Executing instance tests...");
	instanceTests();
	printf("OK\n");
	printf("Executing parser tests...");
	parserTests();
	printf("OK\n");
	return 0;
}
