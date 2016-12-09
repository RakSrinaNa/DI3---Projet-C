#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "item.h"

void instanceInitialize(Instance * instance, int itemsCount, int dimensionsCount)
{
    instance->itemsCount = itemsCount;
    instance->dimensionsNumber = dimensionsCount;
    instance->items = NULL;
    instance->maxWeights = NULL;
    if(instance->dimensionsNumber == 0 || instance->itemsCount == 0)
        return;
    if((instance->items = (Item *) malloc(sizeof(Item) * instance->itemsCount)) == NULL)
    {
        perror("ERROR MALLOC instanceInitialize");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < instance->itemsCount; i++)
    {
        itemInitialize((instance->items) + i, instance->dimensionsNumber);
    }
}

Item * instanceGetItemAt (Instance *instance, int index)
{
    if(index < 0 || index >= instance->itemsCount)
        return NULL;
    return (instance->items) + index;
}

void instanceDestroy(Instance * instance)
{
    for(int i = 0; i < instance->itemsCount; i++) // Destroy each object of the instance
        itemDestroy(instanceGetItemAt(instance, i));

    free(instance->maxWeights);
    free(instance->items);
}
