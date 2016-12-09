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
    instanceInitialize(instance, 0, 0);
    if(instance->objects != NULL || instance->maxWeights != NULL)
    {
        perror("ASSERT INSTANCE 2");
        exit(EXIT_FAILURE);
    }
    instanceInitialize(instance, 3, 3);
    instance->maxWeights = weights;
    if(instance->objects == NULL || instanceGetObjectAt(instance, 2)->value != 0)
    {
        perror("ASSERT INSTANCE 3");
        exit(EXIT_FAILURE);
    }
    if(instanceGetObjectAt(instance, 3) != NULL)
    {
        perror("ASSERT INSTANCE 4");
        exit(EXIT_FAILURE);
    }
    instanceDestroy(instance);
}
