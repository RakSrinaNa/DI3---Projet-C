#ifndef INSTANCE
#define INSTANCE

#include "object.h"

typedef struct _instance{

    int objectNumber;
    int dimensionNumber;

    Object ** objects;

    int * maxWeights;

} Instance;

void instanceInitialize(Instance * instance);
void instanceSetObject(Instance * instance, Object * object, int i);
void instanceFinalize(Instance * instance);

#endif
