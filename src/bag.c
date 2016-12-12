#include <stdio.h>
#include <stdlib.h>

#include "bag.h"

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
	if((bag->maxWeights = (int *) malloc(sizeof(int) * instance->dimensionsNumber)) == NULL)
	{
		perror("MALLOC ERROR bag_create");
		exit(EXIT_FAILURE);
	}
	bag->itemsCount = 0;
	
	for(int i = 0; i < instance->dimensionsNumber; i++)
		bag->weights[i] = 0;
	
	for(int i = 0; i < instance->dimensionsNumber; i++)
		bag->maxWeights[i] = instance_getMaxWeight(instance, i);
	
	return bag;
}

void bag_destroy(Bag * bag)
{
	free(bag->items);
	free(bag->weights);
	free(bag->maxWeights);
	free(bag);
}

void bag_appendItem(Instance * instance, Bag * bag, int itemIndex)
{
	int * newItems;
	if((newItems = (int *) realloc(bag, bag->itemsCount + 1)) == NULL)
	{
		perror("MALLOC ERROR bag_appendItem");
		exit(EXIT_FAILURE);
	}
	bag->items = newItems;
	bag->items[bag->itemsCount] = itemIndex;
	(bag->itemsCount)++;
	
	for(int i = 0; i < instance->dimensionsNumber; i++)
		bag->weights[i] += instance_getItem(instance, itemIndex)->weights[i];
}

int bag_canContain(Instance * instance, Bag * bag, int itemIndex)
{
	for(int i = 0; i < instance->dimensionsNumber; i++)
		if(bag->weights[i] + instance_getItem(instance, itemIndex)->weights[i] > bag->maxWeights[i])
			return 0;
	
	return 1;
}
