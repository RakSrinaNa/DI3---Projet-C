#include <stdlib.h>

#include "unit.h"
#include "solutionIndirectUnit.h"
#include "solutionIndirect.h"
#include "parser.h"

void solutionIndirectTests(void)
{
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag.txt");
	SolutionIndirect * solution = solutionIndirect_create(instance);
	
	int * order;
	if((order = (int *) malloc(sizeof(int) * instance->itemsCount)) == NULL)
	{
		perror("TEST MALLOC ERROR");
		exit(EXIT_FAILURE);
	}
	order[0] = 0;
	order[1] = 1;
	order[2] = 2;
	order[3] = 3;
	order[4] = 4;
	order[5] = 5;
	order[6] = 6;
	order[7] = 7;
	order[8] = 8;
	order[9] = 9;
	order[10] = 10;
	order[11] = 11;
	order[12] = 12;
	order[13] = 13;
	order[14] = 14;
	solution->itemsOrder = order;
	
	solutionIndirect_decode(solution);
	if(solutionIndirect_doable(solution) != 1)
		unit_error("ASSERT SOLUTIONINDIRECT 1");
	if(solution->bag->itemsCount != 2 || bag_getItemIndex(solution->bag, 0) != 0 || bag_getItemIndex(solution->bag, 1) != 12)
		unit_error("ASSERT SOLUTIONINDIRECT 2");
	
	order[0] = 6;
	order[1] = 12;
	order[6] = 0;
	order[12] = 1;
	
	solutionIndirect_decode(solution);
	if(solutionIndirect_doable(solution) != 1)
		unit_error("ASSERT SOLUTIONINDIRECT 3");
	if(solution->bag->itemsCount != 2 || bag_getItemIndex(solution->bag, 0) != 6 || bag_getItemIndex(solution->bag, 1) != 12)
		unit_error("ASSERT SOLUTIONINDIRECT 4");
	
	char * filename = "testSolutionIndirect.txt";
	solutionIndirect_saveToFile(filename, solution);
	FILE * file;
	if((file = fopen(filename, "r")) == NULL)
	{
		perror("ERROR FOPEN SOLUTIONINDIRECT UNIT");
		exit(EXIT_FAILURE);
	}
	if(solutionIndirect_evaluate(solution) != atoi(parser_readLine(file)))
		unit_error("ASSERT SOLUTIONDIRECT 3");
	int * itemOrder = parser_lineToIntArray(parser_readLine(file), solution->instance->itemsCount);
	for(int i = 0; i < instance->itemsCount; i++)
		if(solutionIndirect_getItemIndex(solution, i) != itemOrder[i])
		{
			if(remove(filename) != 0)
				perror("ERROR REMOVE SOLUTIONINDIRECT UNIT");
			unit_error("ASSERT SOLUTIONINDIRECT 4");
		}
	free(itemOrder); // Bag content (next line) should have already been verified in bagUnit
	fclose(file);
	if(remove(filename) != 0)
		perror("ERROR REMOVE SOLUTIONINDIRECT UNIT");
	
	solutionIndirect_destroy(solution);
	instance_destroy(instance);
	free(instance);
}
