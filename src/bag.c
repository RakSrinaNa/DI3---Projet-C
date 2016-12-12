#include <stdio.h>
#include <stdlib.h>

#include "bag.h"

Bag * bag_create(Instance * instance)
{
	
	Bag * bag = (Bag *) malloc(sizeof(Bag));
	bag->items = (int *) malloc(sizeof(int));
	bag->itemsCount = 0;
	
	bag->weights = (int *) malloc(sizeof(int) * instance->dimensionsNumber);
	for(int i = 0; i < instance->dimensionsNumber; i++)
		bag->weights[i] = 0;
	
	bag->maxWeights = (int *) malloc(sizeof(int) * instance->dimensionsNumber);
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
	
	bag->items = (int *) realloc(bag, (size_t) (bag->itemsCount + 1));
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

int bag_getItemID(Bag * bag, int index)
{

    return bag->items[index];

}
