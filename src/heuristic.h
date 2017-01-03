#ifndef HEURISTIC
#define HEURISTIC

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
 * @return The list to use in the heuristic for this scheduler.
 */
int * heuristic_getList(Instance * instance, Bag * bag, int schedulerType);

/**
 * Save a Solution to a file.
 *
 * @param fileName The file where to write.
 * @param instance A pointer to the instance linked to the solution.
 * @param solution A pointer to the solution.
 */
void heuristic_saveSolutionToFile(char * fileName, Instance * instance, Solution * solution);

/**
 * Destroy a solution.
 *
 * @param solution A pointer to the solution to destroy.
 */
void heuristic_solutionDestroy(Solution * solution);

/**
 * Convert the time from microseconds to seconds.
 *
 * @param timeInUS The tie in microseconds.
 * @return The time in seconds.
 */
double convertToSecond(long timeInUS);

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
