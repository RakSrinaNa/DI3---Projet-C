#include <stdio.h>
#include <stdlib.h>

#include "headers/instance.h"
#include "headers/utils.h"

void item_initialize(Item * item, int dimensionsNumber)
{
	item->value = 0;
	item->weights = NULL;
	if(dimensionsNumber <= 0)
		return;
	
	MMALLOC(item->weights, int, dimensionsNumber, "item_initialize");
	
	for(int i = 0; i < dimensionsNumber; i++)
		item->weights[i] = 0;
}

void item_setWeight(Item * item, int index, int weight)
{
	item->weights[index] = weight;
}

int item_getWeight(Item * item, int index)
{
	return item->weights[index];
}

void item_destroy(Item * item)
{
	free(item->weights);
}
