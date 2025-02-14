#include <stdio.h>
#include <stdlib.h>

#include "headers/instance.h"
#include "headers/utils.h"

void instance_initialize(Instance * instance, int itemsCount, int dimensionsCount)
{
	instance->itemsCount = itemsCount;
	instance->dimensionsNumber = dimensionsCount;
	instance->items = NULL;
	instance->maxWeights = NULL;
	if(instance->dimensionsNumber <= 0 || instance->itemsCount <= 0)
	{
		perror("Instance with no dimensions or items");
		exit(EXIT_FAILURE);
	}
	MMALLOC(instance->items, Item, instance->itemsCount, "instance_initialize");
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
	free(instance);
}

int instance_item_getWeight(Instance * instance, int index, int dimension)
{
	if(index < 0 || index >= instance->itemsCount || dimension < 0 || dimension >= instance->dimensionsNumber)
		return -1;
	return item_getWeight(instance_getItem(instance, index), dimension);
}

int instance_item_getValue(Instance * instance, int index)
{
	if(index < 0 || index >= instance->itemsCount)
		return -1;
	return instance_getItem(instance, index)->value;
}
