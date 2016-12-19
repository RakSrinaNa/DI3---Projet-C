#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "solutionDirect.h"

SolutionDirect * solutionDirect_create(Instance * instance)
{
	SolutionDirect * solution;
	if((solution = (SolutionDirect *) malloc(sizeof(SolutionDirect))) == NULL)
	{
		perror("ERROR MALLOC solutionDirect_create");
		exit(EXIT_FAILURE);
	}
	
	if((solution->itemsTaken = (int *) malloc(sizeof(int) * instance->itemsCount)) == NULL)
	{
		perror("ERROR MALLOC solutionDirect_create");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < instance->itemsCount; i++)
		solution->itemsTaken[i] = 0;
	
	solution->evaluate = solutionDirect_evaluate;
	solution->doable = solutionDirect_doable;
	solution->print = solutionDirect_print;
	solution->saveToFile = solutionDirect_saveToFile;
	
	return solution;
}

void solutionDirect_destroy(SolutionDirect * solution)
{
	free(solution->itemsTaken);
	free(solution);
}

int solutionDirect_evaluate(Instance * instance, int * items)
{
	int totalValue = 0;
	
	for(int i = 0; i < instance->itemsCount; i++)
		if(items[i] == 1)
			totalValue += instance_item_getValue(instance, i);
	
	return totalValue;
}

int solutionDirect_doable(Instance * instance, int * items)
{
	for(int dimension = 0; dimension < instance->dimensionsNumber; dimension++)
	{
		int totalWeight = 0;
		for(int i = 0; i < instance->itemsCount; i++)
			if(items[i] == 1)
				totalWeight += instance_item_getWeight(instance, i, dimension);
		if(totalWeight > instance_getMaxWeight(instance, dimension))
			return 0;
	}
	return 1;
}

void solutionDirect_takeItem(SolutionDirect * solution, int index)
{
	solution->itemsTaken[index] = 1;
}

void solutionDirect_print(Instance * instance, int * items)
{
	printf("Total value in the bag : %d\n", solutionDirect_evaluate(instance, items));
	printf("Objects in the bag : ");
	for(int i = 0; i < instance->itemsCount; i++)
		if(items[i] == 1)
			printf("%d\t", i);
	printf("\n");
}

void solutionDirect_saveToFile(char * fileName, Instance * instance, int * items)
{
	FILE * file;
	if((file = fopen(fileName, "w+")) == NULL)
	{
		perror("ERROR FOPEN solutionDirect_saveToFile");
		exit(EXIT_FAILURE);
	}
	
	fprintf(file, "%d\n", solutionDirect_evaluate(instance, items));
	for(int i = 0; i < instance->itemsCount; i++)
		fprintf(file, "%d\t\t", items[i]);
	
	fclose(file);
}
