#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "item.h"

void itemInitialize (Item *item, int dimensionsNumber)
{
    item->value = 0;
    item->weights = NULL;
    if((item->weights = malloc(sizeof(int) * dimensionsNumber)) == NULL)
    {
        perror("ERROR MALLOC itemInitialize");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < dimensionsNumber; i++)
        item->weights[i] = 0;
}

void itemSetWeight (Item *item, int weightPos, int weight)
{
    item->weights[weightPos] = weight;
}

void itemDestroy (Item *item)
{
    free(item->weights);
}
