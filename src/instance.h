#ifndef INSTANCE
    #define INSTANCE

    #include "object.h"

    typedef struct{
        int objectsNumber;
        int dimensionsNumber;
        Object * objects;
        int * maxWeights;
    } Instance;

    /**
     * Initialize an instance depending on its values objectsNumber and dimensionsNumber.
     *
     * This method should be called only once.
     *
     * @param instance A pointer to the instance to initialize.
     */
    void instanceInitialize(Instance * instance, int objectsCount, int dimensionsCount);

    /**
     * Return the object at the given position in an instance.
     *
     * @param instance The instance to retrieve the object from.
     * @param index The index of the object.
     *
     * @return A pointer to the wanted object, NULL if not present.
     */
    Object * instanceGetObjectAt(Instance * instance, int index);

    /**
     * Destroy an instance previously initialized.
     *
     * @param instance A pointer to the instance to destroy.
     */
    void instanceDestroy(Instance * instance);

#endif
