#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "solutionDirect.h"
#include "utils.h"

SolutionDirect * solutionDirect_create(Instance * instance)
{
	SolutionDirect * solution;
	MMALLOC(solution, SolutionDirect, 1, "solutionDirect_create");

	solution->instance = instance;

	MMALLOC(solution->itemsTaken, int, instance->itemsCount, "solutionDirect_create");
	for(int i = 0; i < instance->itemsCount; i++)
		solution->itemsTaken[i] = 0;

	return solution;
}

void solutionDirect_destroy(SolutionDirect * solution)
{
	free(solution->itemsTaken);
	free(solution);
}

int solutionDirect_evaluate(SolutionDirect * solution)
{
	int totalValue = 0;

	for(int i = 0; i < solution->instance->itemsCount; i++)
		if(solutionDirect_isItemTaken(solution, i) == 1)
			totalValue += instance_item_getValue(solution->instance, i);

	return totalValue;
}

int solutionDirect_doable(SolutionDirect * solution)
{
	for(int dimension = 0; dimension < solution->instance->dimensionsNumber; dimension++)
	{
		int totalWeight = 0;
		for(int i = 0; i < solution->instance->itemsCount; i++)
			if(solutionDirect_isItemTaken(solution, i) == 1)
				totalWeight += instance_item_getWeight(solution->instance, i, dimension);
		if(totalWeight > instance_getMaxWeight(solution->instance, dimension))
			return 0;
	}
	return 1;
}

void solutionDirect_takeItem(SolutionDirect * solution, int index)
{
	if(index >= 0 && index < solution->instance->itemsCount)
		solution->itemsTaken[index] = 1;
}

void solutionDirect_print(SolutionDirect * solution)
{
	printf("Total value in the bag : %d\n", solutionDirect_evaluate(solution));
	printf("Objects in the bag : ");
	for(int i = 0; i < solution->instance->itemsCount; i++)
		if(solutionDirect_isItemTaken(solution, i) == 1)
			printf("%d\t", i);
	printf("\n");
}

void solutionDirect_saveToFile(char * fileName, SolutionDirect * solution)
{
	FILE * file;
	if((file = fopen(fileName, "w+")) == NULL)
	{
		perror("ERROR FOPEN solutionDirect_saveToFile");
		exit(EXIT_FAILURE);
	}

	fprintf(file, "%d\n", solutionDirect_evaluate(solution));
	for(int i = 0; i < solution->instance->itemsCount; i++)
		fprintf(file, "%d\t\t", solutionDirect_isItemTaken(solution, i));

	fclose(file);
}

SolutionDirect * solutionDirect_duplicate(SolutionDirect * solutionDirect)
{
	SolutionDirect * newSolution = solutionDirect_create(solutionDirect->instance);
	for(int i = 0; i < solutionDirect->instance->itemsCount; i++)
		if(solutionDirect_isItemTaken(solutionDirect, i) == 1)
			solutionDirect_takeItem(newSolution, i);

	return newSolution;
}

int solutionDirect_isItemTaken(SolutionDirect * solution, int index)
{
	if(index < 0 || index >= solution->instance->itemsCount)
		return 0;
	return solution->itemsTaken[index];
}
