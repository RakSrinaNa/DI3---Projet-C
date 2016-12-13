#include <stdlib.h>
#include "solutionIndirectUnit.h"
#include "solutionIndirect.h"
#include "parser.h"
#include "instance.h"
#include "bag.h"

void solutionIndirectTests(void)
{
	Instance * instance = parser_readFile("MKP-Instances/theBestBag.txt");
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
	{
		perror("ASSERT SOLUTIONINDIRECT 1");
		exit(EXIT_FAILURE);
	}
	if(solution->bag->itemsCount != 2 || bag_getItemIndex(solution->bag, 0) != 0 || bag_getItemIndex(solution->bag, 1) != 12)
	{
		perror("ASSERT SOLUTIONINDIRECT 2");
		exit(EXIT_FAILURE);
	}
	
	order[0] = 6;
	order[1] = 12;
	order[6] = 0;
	order[12] = 1;
	
	solutionIndirect_decode(solution);
	if(solutionIndirect_doable(solution) != 1)
	{
		perror("ASSERT SOLUTIONINDIRECT 3");
		exit(EXIT_FAILURE);
	}
	if(solution->bag->itemsCount != 2 || bag_getItemIndex(solution->bag, 0) != 6 || bag_getItemIndex(solution->bag, 1) != 12)
	{
		perror("ASSERT SOLUTIONINDIRECT 4");
		exit(EXIT_FAILURE);
	}
	
	solutionIndirect_destroy(solution);
	instance_destroy(instance);
	free(instance);
}
