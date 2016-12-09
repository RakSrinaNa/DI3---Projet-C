#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "object.h"

Instance * instanceCreate()
{
    Instance * instance;
    if((instance = (Instance *) malloc(sizeof(Instance))) == NULL)
    {
        perror("ERROR MALLOC instanceCreate instance.c");
        exit(EXIT_FAILURE);
    }
    return instance;
}

void instanceInitialize(Instance * instance, int objectsCount, int dimensionsCount)
{
    instance->objectsNumber = objectsCount;
    instance->dimensionsNumber = dimensionsCount;
    instance->objects = NULL;
    instance->maxWeights = NULL;
    if(instance->dimensionsNumber == 0 || instance->objectsNumber == 0)
        return;
    if((instance->objects = (Object *) malloc(sizeof(Object) * instance->objectsNumber)) == NULL)
    {
        perror("ERROR MALLOC instanceInitialize instance.c");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < instance->objectsNumber; i++)
    {
        objectInitialize((instance->objects) + i, instance->dimensionsNumber);
    }
}

Object * instanceGetObjectAt(Instance * instance, int index)
{
    if(index < 0 || index >= instance->objectsNumber)
        return NULL;
    return (instance->objects) + index;
}

void instanceDestroy(Instance * instance)
{
    for(int i = 0; i < instance->objectsNumber; i++) // Destroy each object of the instance
        objectDestroy(instanceGetObjectAt(instance, i));

    free(instance->maxWeights);
    free(instance->objects);
    free(instance);
}
