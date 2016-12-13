#ifndef BAG
#define BAG

#include "instance.h"

typedef struct
{
	int * items;
	size_t itemsCount;
	int * weights;
	int * maxWeights;
} Bag;

/**
 * Create a bag on the heap.
 *
 * @param instance A pointer to the instance associated with the bag
 * @return A pointer to the bag.
 */
Bag * bag_create(Instance * instance);

/**
 * Destroy a bag previously created bag_create.
 *
 * @param bag The bag to destroy.
 */
void bag_destroy(Bag * bag);

/**
 * Add an item to the bag.
 *
 * @param instance A pointer to the instance.
 * @param bag A pointer to the bag.
 * @param itemIndex The index of the item to add to the bag.
 */
void bag_appendItem(Instance * instance, Bag * bag, int itemIndex);

/**
 * Tells if an item can fit in a bag.
 *
 * @param instance A pointer to the instance.
 * @param bag A pointer to the bag.
 * @param itemIndex The index of the item.
 * @return A boolean indicating if this item can fit in the bag.
 */
int bag_canContain(Instance * instance, Bag * bag, int itemIndex);

int bag_getItemID(Bag * bag, int index);

#endif
