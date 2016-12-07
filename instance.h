#include <stdio.h>
#include <stdlib.h>

typedef struct {

    int value;
    int * weights;

} Object;

typedef struct {

    int objectNumber;
    int dimensionNumber;

    Object ** objects;

} Instance;
