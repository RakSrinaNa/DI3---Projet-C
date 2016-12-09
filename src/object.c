#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "object.h"

void objectInitialize(Object * object, int dimensionsNumber)
{
    object->value = 0;
    object->weights = NULL;
    if((object->weights = malloc(sizeof(int) * dimensionsNumber)) == NULL)
    {
        perror("ERROR MALLOC objectInitialize object.c");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < dimensionsNumber; i++)
        object->weights[i] = 0;
}

void objectSetWeight(Object * object, int weightPos, int weight)
{
    object->weights[weightPos] = weight;
}

void objectDestroy(Object * object)
{
    free(object->weights);
}
