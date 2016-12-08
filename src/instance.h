#ifndef INSTANCE
    #define INSTANCE

    #include "object.h"

    typedef struct{
        int objectsNumber;
        int dimensionsNumber;
        Object ** objects;
        int * maxWeights;
    } Instance;

    Instance * instanceCreate(void);
    void instanceInitialize(Instance * instance);
    Object * instanceGetObjectAt(Instance * instance, int index);
    void instanceSetObject(Instance * instance, Object * object, int index);
    void instanceDestroy(Instance * instance);

#endif
