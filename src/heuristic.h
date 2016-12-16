#ifndef HEURISTIC
#define HEURISTIC

#include "instance.h"
#include "bag.h"
#include "solutionIndirect.h"

typedef enum
{
	DIRECT, INDIRECT
} SolutionType;

typedef union
{
	SolutionDirect * direct;
	SolutionIndirect * indirect;
} Solutions;

typedef struct
{
	SolutionType type;
	Solutions solutions;
	long solveTime;
} Solution;

/**
 * Starts the heuristic function depending on the solutionType and schedulerType.
 *
 * @param instance A pointer to the instance to run the heuristic on.
 * @param solutionType The solution type:
 *  - 0 -> Indirect
 *  - Any other value -> Direct
 * @param schedulerType The scheduler type:
 *  - 0 -> Sort in random order
 *  - 1 -> Sort by item value.
 *  - 2 -> Sort by ratio with all dimensions.
 *  - 3 -> Sort by ratio with the most critic dimension.
 * @return A pointer to a solution.
 */
Solution * heuristic(Instance * instance, int solutionType, int schedulerType);

/**
 * Get the initial list for a scheduler type.
 *
 * @param instance A pointer to the instance where the items are from.
 * @param bag A pointer to the bag associated to the solution.
 * @param schedulerType The type of the scheduler.
 * @return The list to use in the heuristic for this scheduler.
 */
int * heuristic_getList(Instance * instance, Bag * bag, int schedulerType);

#endif
