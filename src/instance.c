#include <stdio.h>
#include <stdlib.h>

#include "instance.h"

void instance_initialize(Instance * instance, int itemsCount, int dimensionsCount)
{
	instance->itemsCount = itemsCount;
	instance->dimensionsNumber = dimensionsCount;
	instance->items = NULL;
	instance->maxWeights = NULL;
	if(instance->dimensionsNumber <= 0 || instance->itemsCount <= 0)
		return;
	if((instance->items = (Item *) malloc(sizeof(Item) * instance->itemsCount)) == NULL)
	{
		perror("ERROR MALLOC instance_initialize");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < instance->itemsCount; i++)
		item_initialize((instance->items) + i, instance->dimensionsNumber);
}

Item * instance_getItem(Instance * instance, int index)
{
	if(index < 0 || index >= instance->itemsCount || instance->items == NULL) // If not in range or items not initialized
		return NULL;
	return (instance->items) + index;
}

int instance_getMaxWeight(Instance * instance, int index)
{
	if(index < 0 || index >= instance->dimensionsNumber || instance->maxWeights == NULL) // If not in range or maxWeights not initialized
		return 0;
	return instance->maxWeights[index];
}

void instance_setMaxWeights(Instance * instance, int * weights)
{
	instance->maxWeights = weights;
}

void instance_destroy(Instance * instance)
{
	for(int i = 0; i < instance->itemsCount; i++) // Destroy each object of the instance
		item_destroy(instance_getItem(instance, i));
	
	free(instance->maxWeights);
	free(instance->items);
}
