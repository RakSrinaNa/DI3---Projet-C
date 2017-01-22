#include <stdio.h>

#include "headers/itemUnit.h"
#include "headers/instanceUnit.h"
#include "headers/parserUnit.h"
#include "headers/solutionDirectUnit.h"
#include "headers/bagUnit.h"
#include "headers/solutionIndirectUnit.h"
#include "headers/schedulerUnit.h"
#include "headers/heuristicUnit.h"
#include "headers/metaheuristicLocalUnit.h"
#include "headers/solutionUnit.h"
#include "headers/metaheuristicTabouUnit.h"
#include "headers/metaheuristicGeneticUnit.h"

int mainUnit()
{
	setbuf(stdout, NULL);
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
	printf("Executing solution tests...");
	solutionTests();
	printf("OK\n");
	printf("Executing scheduler tests...");
	schedulerTests();
	printf("OK\n");
	printf("Executing heuristic tests...");
	heuristicTests();
	printf("OK\n");
	printf("Executing metaheuristicLocal tests...");
	metaheuristicLocalTests();
	printf("OK\n");
	printf("Executing metaheuristicTabou tests...");
	metaheuristicTabouTests();
	printf("OK\n");
	printf("Executing metaheuristicGenetic tests...");
	metaheuristicGeneticTests();
	printf("OK\n");
	return 0;
}
