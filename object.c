#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "object.h"

void objectInitialize(Object * object, int dimensionsNumber){

    object->weights = malloc(sizeof(int) * dimensionsNumber);

}

void objectFinalize(Object * object){

    free(object->weights);
    free(object);

}
