#ifndef HEURISTIC
#define HEURISTIC

#include <time.h>

#include "instance.h"
#include "bag.h"
#include "solutionIndirect.h"
#include "solutionDirect.h"

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
	Instance * instance;
	SolutionType type;
	Solutions solutions;
	long double solveTime;
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
 *  - 4 -> Sort by ratio with the sum of each dimension weighting by its remaining space.
 *  - 5 -> //TODO desc
 * @return A pointer to a solution.
 */
Solution * heuristic(Instance * instance, int solutionType, int schedulerType);

/**
 * Get the initial list for a scheduler type.
 *
 * @param instance A pointer to the instance where the items are from.
 * @param bag A pointer to the bag associated to the solution.
 * @param schedulerType The type of the scheduler.
 * @param oldList The old list to replace, use NULL if creating a new one (should be useful for schedulerType 3 & 4).
 * @param listCount The size of the list to create.
 * @return The list to use in the heuristic for this scheduler.
 */
int * heuristic_getList(Instance * instance, Bag * bag, int schedulerType, int * oldList, int listCount);

/**
 * Save a Solution to a file.
 *
 * @param fileName The file where to write.
 * @param solution A pointer to the solution.
 */
void heuristic_saveSolutionToFile(char * fileName, Solution * solution);

/**
 * Destroy a solution.
 *
 * @param solution A pointer to the solution to destroy.
 */
void heuristic_solutionDestroy(Solution * solution);

/**
 * Get the difference between two times in seconds.
 *
 * @param start The starting time.
 * @param end The ending time.
 * @return The elapsed time in seconds.
 */
long double heuristic_getTimeDiff(clock_t start, clock_t end);

/**
 * Evaluate a solution.
 *
 * @param solution A pointer to the solution.
 * @return The score for the solution.
 */
int heuristic_evaluate(Solution * solution);

/**
 * Tells if a solution is doable.
 *
 * @param solution A pointer to the solution.
 * @return 1 if doable, 0 else.
 */
int heuristic_doable(Solution * solution);

#endif
