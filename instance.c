#include <stdio.h>
#include <stdlib.h>

#include "instance.h"


void instanceInitialize(Instance * instance){

    instance->objects = malloc(sizeof(Object *) * instance->objectNumber);

}

void instanceSetObject(Instance * instance, Object * object, int i){

    instance->objects[i] = object;

}

void objectInitialize(Instance * instance, Object * object){

    object->weights = malloc(sizeof(int) * instance->dimensionNumber);

}

