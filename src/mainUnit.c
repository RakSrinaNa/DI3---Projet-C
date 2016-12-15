#include <stdio.h>

#include "itemUnit.h"
#include "instanceUnit.h"
#include "parserUnit.h"
#include "solutionDirectUnit.h"
#include "bagUnit.h"
#include "solutionIndirectUnit.h"
#include "schedulerUnit.h"

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
	printf("Executing bag tests...");
	bagTests();
	printf("OK\n");
	printf("Executing solutionIndirect tests...");
	solutionIndirectTests();
	printf("OK\n");
	printf("Executing scheduler tests...");
	schedulerTests();
	printf("OK\n");
	return 0;
}
