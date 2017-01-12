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
	if(solutionDirect_evaluate(solution) != 333)
		unit_error("ASSERT SOLUTIONDIRECT 1");
	if(solutionDirect_doable(solution) != 0)
		unit_error("ASSERT SOLUTIONDIRECT 2");
	solution->itemsTaken[1] = 0;
	solutionDirect_takeItem(solution, 1);
	if(solution->itemsTaken[1] != 1)
		unit_error("ASSERT SOLUTIONDIRECT 3");
	solution->itemsTaken[1] = 0;
	solution->itemsTaken[3] = 0;
	solution->itemsTaken[5] = 0;
	solution->itemsTaken[7] = 0;
	solution->itemsTaken[6] = 1;
	solution->itemsTaken[12] = 1;
	int score = solutionDirect_evaluate(solution);
	if(score != 167)
		unit_error("ASSERT SOLUTIONDIRECT 4");
	if(solutionDirect_doable(solution) != 1)
		unit_error("ASSERT SOLUTIONDIRECT 5");
	char * filename = "testSolutionDirect.txt";
	solutionDirect_saveToFile(filename, solution);
	FILE * file;
	if((file = fopen(filename, "r")) == NULL)
	{
		perror("ERROR FOPEN SOLUTIONDIRECT UNIT");
		exit(EXIT_FAILURE);
	}
	if(score != atoi(parser_readLine(file)))
		unit_error("ASSERT SOLUTIONDIRECT 6");
	char * line = parser_readLine(file);
	int * itemsTaken = parser_lineToIntArray(line, instance->itemsCount);
	free(line);
	fclose(file);
	if(remove(filename) != 0)
		perror("ERROR REMOVE SOLUTIONDIRECT UNIT");
	if(!unit_arrayEquals(itemsTaken, solution->itemsTaken, instance->itemsCount))
		unit_error("ASSERT SOLUTIONDIRECT 7");
	free(itemsTaken);
	SolutionDirect * dup = solutionDirect_duplicate(solution);
	if(dup == NULL || dup->instance != solution->instance || !unit_arrayEquals(solution->itemsTaken, dup->itemsTaken, instance->itemsCount))
		unit_error("ASSERT SOLUTIONDIRECT 8");
	solutionDirect_destroy(solution);
	solutionDirect_destroy(dup);
	instance_destroy(instance);
}
