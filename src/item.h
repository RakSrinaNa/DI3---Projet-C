#ifndef ITEM
#define ITEM

typedef struct
{
	int value;
	int * weights;
} Item;

/**
 * Initialize an item.
 *
 * @param item A pointer to the item to initialize.
 * @param dimensionsNumber The number of dimensions this item have.
 */
void item_initialize(Item * item, int dimensionsNumber);

/**
 * Set a weight for this item.
 *
 * @param item A pointer to the item where the weight will be set.
 * @param index The index of the weight.
 * @param weight The value of the weight.
 */
void item_setWeight(Item * item, int index, int weight);

/**
 * Get a weight from an item.
 *
 * @param item A pointer to the item where to get the weight from.
 * @param index The index of the wanted weight.
 * @return The value of the weight.
 */
int item_getWeight(Item * item, int index);

/**
 * Destroy an item previously initialized with item_initialize.
 *
 * @param item A pointer to the item to destroy.
 */
void item_destroy(Item * item);

#endif
