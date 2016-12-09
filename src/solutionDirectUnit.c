#include <stdlib.h>

#include "solutionDirectUnit.h"
#include "solutionDirect.h"
#include "parser.h"

void solutionDirectTests(void)
{
	Instance * instance = parser_readFile("MKP-Instances/theBestBag.txt");
	SolutionDirect * solution = solutionDirect_create(instance);
	solution->itemsTaken[1] = 1;
	solution->itemsTaken[3] = 1;
	solution->itemsTaken[5] = 1;
	solution->itemsTaken[7] = 1;
	if(solutionDirect_evaluate(instance, solution->itemsTaken) != 333)
	{
		perror("ASSERT SOLUTIONDIRECT 1");
		exit(EXIT_FAILURE);
	}
	if(solutionDirect_doable(instance, solution->itemsTaken) != 0)
	{
		perror("ASSERT SOLUTIONDIRECT 2");
		exit(EXIT_FAILURE);
	}
	solution->itemsTaken[1] = 0;
	solution->itemsTaken[3] = 0;
	solution->itemsTaken[5] = 0;
	solution->itemsTaken[7] = 0;
	solution->itemsTaken[6] = 1;
	solution->itemsTaken[12] = 1;
	int score = solutionDirect_evaluate(instance, solution->itemsTaken);
	if(score != 167)
	{
		perror("ASSERT SOLUTIONDIRECT 1");
		exit(EXIT_FAILURE);
	}
	if(solutionDirect_doable(instance, solution->itemsTaken) != 1)
	{
		perror("ASSERT SOLUTIONDIRECT 2");
		exit(EXIT_FAILURE);
	}
	char * filename = "testSolutionDirect.txt";
	solutionDirect_saveToFile(filename, instance, solution->itemsTaken);
	FILE * file;
	if((file = fopen(filename, "r")) == NULL)
	{
		perror("ERROR MALLOC SOLUTIONDIRECT UNIT");
		exit(EXIT_FAILURE);
	}
	if(score != atoi(parser_readLine(file)))
	{
		perror("ASSERT SOLUTIONDIRECT 3");
		exit(EXIT_FAILURE);
	}
	int * itemsTaken = parser_lineToIntArray(parser_readLine(file), instance->itemsCount);
	fclose(file);
	for(int i = 0; i < instance->itemsCount; i++)
		if(itemsTaken[i] != solution->itemsTaken[i])
		{
			if(remove(filename) != 0)
				perror("ERROR REMOVE SOLUTIONDIRECT UNIT");
			perror("ASSERT SOLUTIONDIRECT 4");
			exit(EXIT_FAILURE);
		}
	free(itemsTaken);
	if(remove(filename) != 0)
	{
		perror("ERROR REMOVE SOLUTIONDIRECT UNIT");
		exit(EXIT_FAILURE);
	}
}
