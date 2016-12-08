#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "object.h"


void instanceInitialize(Instance * instance){

    instance->objects = (Object *) malloc(sizeof(Object *) * instance->objectNumber);

}

void instanceSetObject(Instance * instance, Object * object, int i){

    instance->objects[i] = object;

}

void instanceFinalize(Instance * instance){

    for(int i = 0; i < instance->objectNumber; i++)
        objectFinalize(instance->objects[i]);

    free(instance->maxWeights);
    free(instance->objects);
    free(instance);

}


