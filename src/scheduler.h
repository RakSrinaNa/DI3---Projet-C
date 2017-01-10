#ifndef SCHEDULER
#define SCHEDULER

#include "instance.h"
#include "bag.h"

/**
 * Creates a list of items indexes of an instance. This list is randomly ordered.
 *
 * @param instance A pointer to the instance containing the items.
 * @return The list of items.
 */
int * scheduler_random(Instance * instance);

/**
 * Remove an item from the list.
 *
 * @param listPtr A pointer to the list to remove from.
 * @param listCount A pointer to the size of the list.
 * @param index The index of the item to remove.
 * @return The popped element.
 */
int scheduler_removeFromList(int ** listPtr, int * listCount, int index);

/**
 * Append an item to the end of the list.
 *
 * @param list A pointer to the list to insert the item into.
 * @param listCount A pointer to the list length.
 * @param element The element to insert.
 */
void scheduler_appendToList(int ** list, int * listCount, int element);

/**
 * Creates a list of items indexes of an instance. This list is ordered by the item value (decreasing).
 *
 * @param instance A pointer to the instance containing the items.
 * @return The list of items.
 */
int * scheduler_itemValue(Instance * instance);

/**
 * Creates a list of items indexes of an instance. This list is ordered by the ratio of the value and the sum of its weights (decreasing).
 *
 * @param instance A pointer to the instance containing the items.
 * @return The list of items.
 */
int * scheduler_allDimensions(Instance * instance);

/**
 * Get the ratio of an item over all the dimensions.
 *
 * @param instance The instance where the item is in.
 * @param index The index of the item.
 * @return Its ratio (value/(sum of weights)).
 */
double scheduler_allDimensions_score(Instance * instance, int index);

/**
 * Creates a list of items indexes of an instance. This list is ordered by the ratio of the value and the specified weight (decreasing).
 *
 * @param instance A pointer to the instance containing the items.
 * @param dimension The dimension we are considering for the ratio.
 * @param itemsInList The items that we are allowed to use.
 * @param sizeList The size of itemsInList.
 * @return The list of items.
 */
int * scheduler_forDimension(Instance * instance, int dimension, int * itemsInList, int sizeList);

/**
 * Get the ratio of an item over the specified dimension.
 *
 * @param instance The instance where the item is in.
 * @param index The index of the item.
 * @param dim The index of the dimension.
 * @return Its ratio.
 */
double scheduler_forDimension_score(Instance * instance, int index, int dim);

/**
 * Creates a list of items indexes of an instance. This list is ordered by the ratio of the value and the sum of its weighted weights (decreasing).
 *
 * @param instance A pointer to the instance containing the items.
 * @return The list of items.
 */
int * scheduler_allDimensionsWeighted(Instance * instance);

/**
 * Get the ratio of an item over all the weighted dimensions.
 *
 * @param instance The instance where the item is in.
 * @param index The index of the item.
 * @return Its ratio (value/(sum of (maxWeight - weight))).
 */
double scheduler_allDimensionsWeighted_score(Instance * instance, int index);

/**
 * Creates a list of items indexes of an instance. This list is ordered by the ratio with the weight ties the exponential of 20 times the ratio of the completion of the bag.
 *
 * @param instance A pointer to the instance containing the items.
 * @param bag A pointer to the bag associated to the items.
 * @param itemsInList A list of items that are considered.
 * @param sizeList The size of itemsInList.
 * @return
 */
int * scheduler_exponential(Instance * instance, Bag * bag, int * itemsInList, int sizeList); //TODO UNIT

/**
 * Get the ratio with the weight ties the exponential of 20 times the ratio of the completion of the bag.
 *
 * @param instance A pointer to the instance associated to the items.
 * @param bag A pointer to the bag associated to the items.
 * @param index The index of the item.
 * @return The score of this item.
 */
double scheduler_exponential_score(Instance * instance, Bag * bag, int index); //TODO UNIT

/**
 * Sort an array depending on the scores.
 *
 * @param indexes An array of the indexes.
 * @param scores An array of the scores.
 * @param sizeList The size of the lists.
 */
void scheduler_sortArray(int * indexes, double * scores, int sizeList); //TODO UNIT

#endif
