#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "object.h"

Object * objectCreate()
{
    Object * object; // Create an object
    if((object = (Object *) malloc(sizeof(Object))) == NULL)
    {
        perror("ERROR MALLOC objectCreate object.c");
        exit(EXIT_FAILURE);
    }
    return object;
}

void objectInitialize(Object * object, int dimensionsNumber)
{
    if((object->weights = malloc(sizeof(int) * dimensionsNumber)) == NULL)
    {
        perror("ERROR MALLOC objectInitialize object.c");
        exit(EXIT_FAILURE);
    }
}

void objectSetWeight(Object * object, int weightPos, int weight)
{
    object->weights[weightPos] = weight;
}

void objectDestroy(Object * object)
{
    free(object->weights);
    free(object);
}
