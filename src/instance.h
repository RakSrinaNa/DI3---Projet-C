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
 * Get the maximum weight for a dimension.
 *
 * @param instance The instance concerned.
 * @param index The index of the weight.
 * @return The value of the weight. 0 if not present.
 */
int instance_getMaxWeight(Instance * instance, int index);

/**
 * Destroy an instance previously initialized.
 *
 * @param instance A pointer to the instance to destroy.
 */
void instance_destroy(Instance * instance);

/**
 * Get the 'dimension'th weight of the 'index'th item in the instance
 *
 * @param instance A pointer to the instance.
 * @param index The index of the item.
 * @param dimension The index of the dimension.
 * @return The wanted weight, -1 if item or dimension not in range.
 */
int instance_item_getWeight(Instance * instance, int index, int dimension);

/**
 * Get the value of the 'index'th item.
 *
 * @param instance A pointer to the instance.
 * @param index The index of the item.
 * @return The value of this item, -1 if not in range.
 */
int instance_item_getValue(Instance * instance, int index);

#endif
