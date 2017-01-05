#ifndef SOLUTION
#define SOLUTION

#include <sys/timeb.h>

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
	Instance * instance;
	SolutionType type;
	Solutions solutions;
	long double solveTime;
} Solution;

/**
 * Save a Solution to a file.
 *
 * @param fileName The file where to write.
 * @param solution A pointer to the solution.
 */
void solution_saveToFile(char * fileName, Solution * solution);

/**
 * Get the difference between two times in seconds.
 *
 * @param start The starting time.
 * @param end The ending time.
 * @return The elapsed time in seconds.
 */
long double solution_getTimeDiff(struct timeb start, struct timeb end);

/**
 * Evaluate a solution.
 *
 * @param solution A pointer to the solution.
 * @return The score for the solution.
 */
int solution_evaluate(Solution * solution);

/**
 * Tells if a solution is doable.
 *
 * @param solution A pointer to the solution.
 * @return 1 if doable, 0 else.
 */
int solution_doable(Solution * solution);

/**
 * Duplicate a Solution on the heap.
 *
 * @param solution A pointer to the solution to duplicate.
 * @return A pointer to the duplicated solution.
 */
Solution * solution_duplicate(Solution * solution);

/**
 * Destroy a solution.
 *
 * @param solution A pointer to the solution to destroy.
 */
void solution_destroy(Solution * solution);

#endif
