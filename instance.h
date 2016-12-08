#ifndef INSTANCE
#define INSTANCE

typedef struct _object{

    int value;
    int * weights;

} Object;

typedef struct _instance{

    int objectNumber;
    int dimensionNumber;

    Object ** objects;

    int * maxWeights;

} Instance;

#endif
