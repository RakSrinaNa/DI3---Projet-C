#include <stdlib.h>
#include <stdio.h>

#include "instanceUnit.h"
#include "instance.h"

void instanceTests()
{
    int * weights = (int *) malloc(3 * sizeof(int));
    if(weights == NULL)
        exit(10);
    weights[0] = 1;
    weights[1] = 2;
    weights[2] = 3;

    Instance * instance = instanceCreate();
    if(instance->objectsNumber != 0 || instance->dimensionsNumber != 0 || instance->objects != NULL || instance->maxWeights != NULL)
    {
        perror("ASSERT INSTANCE 1");
        exit(EXIT_FAILURE);
    }
    instanceInitialize(instance);
    if(instance->objects != NULL || instance->maxWeights != NULL)
    {
        perror("ASSERT INSTANCE 1");
        exit(EXIT_FAILURE);
    }
    instance->dimensionsNumber = 3;
    instance->objectsNumber = 3;
    instance->maxWeights = weights;
    instanceInitialize(instance);
    if(instance->objects == NULL || instanceGetObjectAt(instance, 2)->value != 0)
    {
        perror("ASSERT INSTANCE 2");
        exit(EXIT_FAILURE);
    }
    instanceDestroy(instance);
}
