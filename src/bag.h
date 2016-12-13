#ifndef BAG
#define BAG

#include <stdio.h>
#include "instance.h"

typedef struct
{
	int * items;
	int itemsCount;
	int * weights;
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

/**
 * Get the index in the instance of the 'index'th item in the bag.
 *
 * @param bag The bag to get the index from.
 * @param index The index of the item.
 * @return The index of the item, -1 if not in range.
 */
int bag_getItemIndex(Bag * bag, int index);

/**
 * Get the current weight of the bag for the 'index'th dimension.
 *
 * @param bag A pointer to the bag where to get the weight from.
 * @param index The index of the dimension.
 * @return The current weight for that dimension.
*/
int bag_getWeight(Bag * bag, int index);

/**
 * Add amount to the weight of the bag for the 'index'th dimension.
 *
 * @param bag A pointer to the bag where to get the weight from.
 * @param index The index of the dimension.
 * @param amount The amount to add.
*/
void bag_addWeight(Bag * bag, int index, int amount);

/**
 * Write the items contained in the bag into the file.
 *
 * @param bag A pointer to the bag.
 * @param file The file to write to.
 */
void bag_saveItems(Bag * bag, FILE * file);

/**
 * Prints into the console the items present in the bag.
 *
 * @param bag A pointer to the bag to print.
 */
void bag_print(Bag * bag);

#endif
