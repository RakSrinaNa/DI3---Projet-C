#include <stdio.h>
#include <stdlib.h>

#include "headers/instance.h"
#include "headers/solutionIndirect.h"
#include "headers/utils.h"

SolutionIndirect * solutionIndirect_create(Instance * instance)
{
	SolutionIndirect * solution;
	MMALLOC(solution, SolutionIndirect, 1, "solutionIndirect_create");
	MMALLOC(solution->itemsOrder, int, instance->itemsCount, "solutionIndirect_create");
	for(int i = 0; i < instance->itemsCount; i++)
		solution->itemsOrder[i] = 0;

	solution->bag = NULL;
	solution->instance = instance;

	return solution;
}

void solutionIndirect_destroy(SolutionIndirect * solution)
{
	free(solution->itemsOrder);
	bag_destroy(solution->bag);
	free(solution);
}

void solutionIndirect_decode(SolutionIndirect * solution)
{
	if(solution->bag != NULL)
		bag_destroy(solution->bag);

	Bag * bag = bag_create(solution->instance);

	for(int i = 0; i < solution->instance->itemsCount; i++)
		if(bag_canContain(solution->instance, bag, solutionIndirect_getItemIndex(solution, i)))
			bag_appendItem(solution->instance, bag, solutionIndirect_getItemIndex(solution, i));

	solution->bag = bag;
}

int solutionIndirect_evaluate(SolutionIndirect * solution)
{
	int totalValue = 0;

	for(int i = 0; i < solution->bag->itemsCount; i++)
		totalValue += instance_item_getValue(solution->instance, bag_getItemIndex(solution->bag, i));

	return totalValue;
}

int solutionIndirect_doable(SolutionIndirect * solution)
{
	for(int i = 0; i < solution->instance->dimensionsNumber; i++)
		if(bag_getWeight(solution->bag, i) > instance_getMaxWeight(solution->instance, i))
			return 0;

	return 1;
}

int solutionIndirect_getItemIndex(SolutionIndirect * solution, int index)
{
	return solution->itemsOrder[index];
}

void solutionIndirect_print(SolutionIndirect * solution)
{
	printf("Total value in the bag : %d\n", solutionIndirect_evaluate(solution));
	printf("Objects in the bag : ");
	bag_print(solution->bag);
	printf("\n");
}

void solutionIndirect_saveToFile(char * fileName, SolutionIndirect * solution)
{
	FILE * file;
	if((file = fopen(fileName, "w+")) == NULL)
	{
		perror("ERROR FOPEN solutionDirect_saveToFile");
		exit(EXIT_FAILURE);
	}

	fprintf(file, "%d\n", solutionIndirect_evaluate(solution));

	for(int i = 0; i < solution->instance->itemsCount; i++)
		fprintf(file, "%d\t\t", solutionIndirect_getItemIndex(solution, i));

	fprintf(file, "\n");

	bag_saveItems(solution->bag, file);

	fclose(file);
}

SolutionIndirect * solutionIndirect_duplicate(SolutionIndirect * solution)
{
	SolutionIndirect * newSolution = solutionIndirect_create(solution->instance);
	for(int i = 0; i < solution->instance->itemsCount; i++)
		newSolution->itemsOrder[i] = solution->itemsOrder[i];
	newSolution->bag = bag_duplicate(solution->instance, solution->bag);
	return newSolution;
}
