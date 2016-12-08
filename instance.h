#ifndef INSTANCE
#define INSTANCE

#include "object.h"

typedef struct _instance{

    int objectNumber;
    int dimensionNumber;

    Object ** objects;

    int * maxWeights;

} Instance;

#endif
