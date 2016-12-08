#ifndef INSTANCE
    #define INSTANCE

    #include "object.h"

    typedef struct{
        int objectsNumber;
        int dimensionsNumber;
        Object ** objects;
        int * maxWeights;
    } Instance;

    void instanceInitialize(Instance * instance);
    void instanceSetObject(Instance * instance, Object * object, int index);
    Object * instanceGetObjectAt(Instance * instance, int index);
    void instanceDestroy(Instance * instance);

#endif
