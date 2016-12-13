#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "solutionIndirect.h"

SolutionIndirect * solutionIndirect_create(Instance * instance)
{
	SolutionIndirect * solution;
	if((solution = (SolutionIndirect *) malloc(sizeof(SolutionIndirect))) == NULL)
	{
		perror("ERROR MALLOC solutionIndirect_create");
		exit(EXIT_FAILURE);
	}
	
	if((solution->itemsOrder = (int *) malloc(sizeof(int) * instance->itemsCount)) == NULL)
	{
		perror("ERROR MALLOC solutionIndirect_create");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < instance->itemsCount; i++)
		solution->itemsOrder[i] = 0;
	
	solution->bag = NULL;
	
	solution->evaluate = solutionIndirect_evaluate;
	solution->doable = solutionIndirect_doable;
	solution->print = solutionIndirect_print;
	solution->saveToFile = solutionIndirect_saveToFile;
	
	return solution;
}

void solutionIndirect_destroy(SolutionIndirect * solution)
{
	free(solution->itemsOrder);
	bag_destroy(solution->bag);
	free(solution);
}

void solutionIndirect_decode(Instance * instance, SolutionIndirect * solution)
{
	Bag * bag = bag_create(instance);
	
	for(int i = 0; i < instance->itemsCount; i++)
		if(bag_canContain(instance, bag, solution->itemsOrder[i]))
			bag_appendItem(instance, bag, solution->itemsOrder[i]);
	
	solution->bag = bag;
}

int solutionIndirect_evaluate(Instance * instance, Bag * bag)
{
	int totalValue = 0;
	
	for(unsigned int i = 0; i < bag->itemsCount; i++)
		totalValue += instance_getItem(instance, bag_getItemID(bag, i))->value;
	
	return totalValue;
}

int solutionIndirect_doable(Instance * instance, Bag * bag)
{
	for(int i = 0; i < instance->dimensionsNumber; i++)
		if(bag->weights[i] > instance->maxWeights[i])
			return 0;
	
	return 1;
}

void solutionIndirect_print(Instance * instance, Bag * bag)
{
	printf("Total value in the bag : %d\n", solutionIndirect_evaluate(instance, bag));
	printf("Objects in the bag : ");
	for(unsigned int i = 0; i < bag->itemsCount; i++)
        printf("%d\t", bag_getItemID(bag, i));
	printf("\n");
}

void solutionIndirect_saveToFile(char * fileName, Instance * instance, SolutionIndirect * solution, Bag * bag)
{
	FILE * file;
	if((file = fopen(fileName, "w+")) == NULL)
	{
		perror("ERROR FOPEN solutionDirect_saveToFile");
		exit(EXIT_FAILURE);
	}
	
	fprintf(file, "%d\n", solutionIndirect_evaluate(instance, bag));
	
	for(int i = 0; i < instance->itemsCount; i++)
		fprintf(file, "%d\t\t", solution->itemsOrder[i]);
	
	fprintf(file, "\n");
  
  for(unsigned int i = 0; i < solutionIndirect_getBag(solution)->itemsCount; i++)
		fprintf(file, "%d\t\t", bag_getItemID(solutionIndirect_getBag(solution), i));

	fclose(file);
}

Bag * solutionIndirect_getBag(SolutionIndirect * solution)
{
    return solution->bag;
}
