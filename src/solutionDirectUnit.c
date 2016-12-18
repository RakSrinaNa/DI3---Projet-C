#include <stdlib.h>

#include "unit.h"
#include "solutionDirectUnit.h"
#include "solutionDirect.h"
#include "parser.h"
#include "instance.h"

void solutionDirectTests(void)
{
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag.txt");
	SolutionDirect * solution = solutionDirect_create(instance);
	solution->itemsTaken[1] = 1;
	solution->itemsTaken[3] = 1;
	solution->itemsTaken[5] = 1;
	solution->itemsTaken[7] = 1;
	if(solutionDirect_evaluate(instance, solution->itemsTaken) != 333)
		unit_error("ASSERT SOLUTIONDIRECT 1");
	if(solutionDirect_doable(instance, solution->itemsTaken) != 0)
		unit_error("ASSERT SOLUTIONDIRECT 2");
	solution->itemsTaken[1] = 0;
	solution->itemsTaken[3] = 0;
	solution->itemsTaken[5] = 0;
	solution->itemsTaken[7] = 0;
	solution->itemsTaken[6] = 1;
	solution->itemsTaken[12] = 1;
	int score = solutionDirect_evaluate(instance, solution->itemsTaken);
	if(score != 167)
		unit_error("ASSERT SOLUTIONDIRECT 1");
	if(solutionDirect_doable(instance, solution->itemsTaken) != 1)
		unit_error("ASSERT SOLUTIONDIRECT 2");
	char * filename = "testSolutionDirect.txt";
	solutionDirect_saveToFile(filename, instance, solution->itemsTaken);
	FILE * file;
	if((file = fopen(filename, "r")) == NULL)
	{
		perror("ERROR FOPEN SOLUTIONDIRECT UNIT");
		exit(EXIT_FAILURE);
	}
	if(score != atoi(parser_readLine(file)))
		unit_error("ASSERT SOLUTIONDIRECT 3");
	int * itemsTaken = parser_lineToIntArray(parser_readLine(file), instance->itemsCount);
	fclose(file);
	if(remove(filename) != 0)
		perror("ERROR REMOVE SOLUTIONDIRECT UNIT");
	if(!unit_arrayEquals(itemsTaken, solution->itemsTaken, instance->itemsCount))
		unit_error("ASSERT SOLUTIONDIRECT 4");
	free(itemsTaken);
}
