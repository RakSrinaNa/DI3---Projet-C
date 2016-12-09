#ifndef INSTANCE
#define INSTANCE

#include "item.h"

typedef struct
{
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
void instance_initialize(Instance * instance, int itemsCount, int dimensionsCount);

/**
 * Return the item at the given position in an instance.
 *
 * @param instance A pointer to the instance to retrieve the object from.
 * @param index The index of the item.
 *
 * @return A pointer to the wanted object, NULL if not present.
 */
Item * instance_getItem(Instance * instance, int index);

/**
 * Set the max weights for this instance.
 *
 * @param instance A pointer to the instance to set the max values to.
 * @param weights A pointer to and int array on the heap representing the maximum weights.
 */
void instance_setMaxWeights(Instance * instance, int * weights);

/**
 * Destroy an instance previously initialized.
 *
 * @param instance A pointer to the instance to destroy.
 */
void instance_destroy(Instance * instance);

#endif
