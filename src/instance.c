#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "object.h"

void instanceInitialize(Instance * instance)
{
    if((instance->objects = (Object **) malloc(sizeof(Object *) * instance->objectsNumber)) == NULL)
    {
        printf("ERROR MALLOC instanceInitialize instance.c");
        exit(1);
    }
    for(int i = 0; i < instance->objectsNumber; i++)
    {
        instanceSetObject(instance, objectCreate(), i);
        objectInitialize(instance->objects[i], instance->dimensionsNumber);
    }
}

void instanceSetObject(Instance * instance, Object * object, int index)
{
    instance->objects[index] = object;
}

Object * instanceGetObjectAt(Instance * instance, int index)
{
    return instance->objects[index];
}

void instanceDestroy(Instance * instance)
{
    for(int i = 0; i < instance->objectsNumber; i++) // Destroy each object of the instance
        objectDestroy(instance->objects[i]);

    free(instance->maxWeights);
    free(instance->objects);
    free(instance);
}
