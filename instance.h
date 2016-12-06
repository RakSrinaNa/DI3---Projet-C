#include <stdio.h>
#include <stdlib.h>

typedef struct _object{

    int value;
    int * weights;

} Object;

typedef struct _instance{

    int objectNumber;
    int dimensionNumber;

    Object ** objects;

} Instance;
