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
    instance->objectsNumber = 0;
    instance->dimensionsNumber = 0;
    instance->objects = NULL;
    instance->maxWeights = NULL;
    return instance;
}

void instanceInitialize(Instance * instance)
{
    if(instance->dimensionsNumber == 0)
        return;
    if((instance->objects = (Object **) malloc(sizeof(Object *) * instance->objectsNumber)) == NULL)
    {
        perror("ERROR MALLOC instanceInitialize instance.c");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < instance->objectsNumber; i++)
    {
        instanceSetObject(instance, objectCreate(), i);
        objectInitialize(instance->objects[i], instance->dimensionsNumber);
    }
}

Object * instanceGetObjectAt(Instance * instance, int index)
{
    return instance->objects[index];
}

void instanceSetObject(Instance * instance, Object * object, int index)
{
    instance->objects[index] = object;
}

void instanceDestroy(Instance * instance)
{
    for(int i = 0; i < instance->objectsNumber; i++) // Destroy each object of the instance
        objectDestroy(instance->objects[i]);

    free(instance->maxWeights);
    free(instance->objects);
    free(instance);
}
