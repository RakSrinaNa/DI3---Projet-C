#ifndef INSTANCE
    #define INSTANCE

    #include "item.h"

    typedef struct{
        int itemsCount;
        int dimensionsNumber;
        Item * items;
        int * maxWeights;
    } Instance;

    /**
     * Initialize an instance depending on its values objectsNumber and dimensionsNumber.
     *
     * This method should be called only once.
     *
     * @param instance A pointer to the instance to initialize.
     * @param itemsCount The numbers of items in the instance. Should be greater than 0.
     * @param dimensionsCount The number of dimension. Should be greater than 0.
     */
    void instanceInitialize(Instance * instance, int itemsCount, int dimensionsCount);

    /**
     * Return the item at the given position in an instance.
     *
     * @param instance The instance to retrieve the object from.
     * @param index The index of the item.
     *
     * @return A pointer to the wanted object, NULL if not present.
     */
    Item * instanceGetItemAt (Instance *instance, int index);

    /**
     * Destroy an instance previously initialized.
     *
     * @param instance A pointer to the instance to destroy.
     */
    void instanceDestroy(Instance * instance);

#endif
