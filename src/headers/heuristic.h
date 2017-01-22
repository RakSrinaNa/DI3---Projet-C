#ifndef HEURISTIC
#define HEURISTIC

#include "instance.h"
#include "bag.h"
#include "solution.h"

/**
 * Starts the heuristic function depending on the solutionType and schedulerType.
 *
 * @param instance A pointer to the instance to run the heuristic on.
 * @param solutionType The solution type.
 * @param schedulerType The scheduler type:
 *  - 0 -> Sort in random order
 *  - 1 -> Sort by item value.
 *  - 2 -> Sort by ratio with all dimensions.
 *  - 3 -> Sort by ratio with the most critic dimension.
 *  - 4 -> Sort by ratio with the sum of each dimension weighting by its remaining space.
 *  - 5 -> Sort by ratio with the weight ties the exponential of 20 times the ratio of the completion of the bag.
 * @return A pointer to a solution.
 */
Solution * heuristic_search(Instance * instance, SolutionType solutionType, int schedulerType);

/**
 * Get the initial list for a scheduler type.
 *
 * @param instance A pointer to the instance where the items are from.
 * @param bag A pointer to the bag associated to the solution.
 * @param schedulerType The type of the scheduler. See heuristic function.
 * @param oldList The old list to replace, use NULL if creating a new one (should be useful for schedulerType 3 & 4).
 * @param listCount The size of the list to create.
 * @return The list to use in the heuristic for this scheduler.
 */
int * heuristic_getList(Instance * instance, Bag * bag, int schedulerType, int * oldList, int listCount);

#endif
