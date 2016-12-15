#include <stdio.h>
#include <stdlib.h>

#include "bag.h"
#include "instance.h"
#include "solutionDirect.h"

Bag * bag_create(Instance * instance)
{
	Bag * bag;
	if((bag = (Bag *) malloc(sizeof(Bag))) == NULL)
	{
		perror("MALLOC ERROR bag_create");
		exit(EXIT_FAILURE);
	}
	if((bag->items = (int *) malloc(sizeof(int))) == NULL)
	{
		perror("MALLOC ERROR bag_create");
		exit(EXIT_FAILURE);
	}
	if((bag->weights = (int *) malloc(sizeof(int) * instance->dimensionsNumber)) == NULL)
	{
		perror("MALLOC ERROR bag_create");
		exit(EXIT_FAILURE);
	}
	bag->itemsCount = 0;
	
	for(int i = 0; i < instance->dimensionsNumber; i++)
		bag->weights[i] = 0;
	
	return bag;
}

void bag_destroy(Bag * bag)
{
	free(bag->items);
	free(bag->weights);
	free(bag);
}

void bag_appendItem(Instance * instance, Bag * bag, int itemIndex)
{
	int * newItems;
	(bag->itemsCount)++;
	if((newItems = (int *) realloc(bag->items, (unsigned int) bag->itemsCount)) == NULL)
	{
		perror("REALLOC ERROR bag_appendItem");
		exit(EXIT_FAILURE);
	}
	bag->items = newItems;
	bag->items[bag->itemsCount - 1] = itemIndex;
	
	for(int i = 0; i < instance->dimensionsNumber; i++)
		bag_addWeight(bag, i, instance_item_getWeight(instance, itemIndex, i));
}

int bag_canContain(Instance * instance, Bag * bag, int itemIndex)
{
	for(int i = 0; i < instance->dimensionsNumber; i++)
		if(bag_getWeight(bag, i) + instance_item_getWeight(instance, itemIndex, i) > instance_getMaxWeight(instance, i))
			return 0;
	
	return 1;
}

int bag_getItemIndex(Bag * bag, int index)
{
	if(index < 0 || index >= bag->itemsCount)
		return -1;
	return bag->items[index];
}

int bag_getWeight(Bag * bag, int index)
{
	return bag->weights[index];
}

void bag_addWeight(Bag * bag, int index, int amount)
{
	bag->weights[index] += amount;
}

void bag_saveItems(Bag * bag, FILE * file)
{
	for(int i = 0; i < bag->itemsCount; i++)
		fprintf(file, "%d\t\t", bag_getItemIndex(bag, i));
}

void bag_print(Bag * bag)
{
	for(int i = 0; i < bag->itemsCount; i++)
		printf("%d\t", bag_getItemIndex(bag, i));
}

int bag_getCriticDimension(Instance * instance, Bag * bag)
{
	int worstLeft = 9999999;
	int worst = -1;
	for(int i = 0; i < instance->dimensionsNumber; i++)
	{
		int left = instance_getMaxWeight(instance, i) - bag_getWeight(bag, i);
		if(left < worstLeft)
		{
			worstLeft = left;
			worst = i;
		}
	}
	return worst;
}

SolutionDirect * bag_toSolutionDirect(Instance * instance, Bag * bag)
{
	SolutionDirect * solution = solutionDirect_create(instance);
	for(int i = 0; i < bag->itemsCount; i++)
		solutionDirect_takeItem(solution, bag_getItemIndex(bag, i));
	return solution;
}
