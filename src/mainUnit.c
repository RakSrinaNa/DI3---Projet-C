#include <stdio.h>

#include "itemUnit.h"
#include "parserUnit.h"
#include "instanceUnit.h"
#include "solutionDirectUnit.h"
#include "solutionIndirectUnit.h"

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
	printf("Executing solutionDirect tests...");
	solutionDirectTests();
	printf("OK\n");
	printf("Executing solutionIndirect tests...");
	solutionIndirectTests();
	printf("OK\n");
	return 0;
}
