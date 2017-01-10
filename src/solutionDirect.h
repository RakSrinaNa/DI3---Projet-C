#ifndef SOLUTIONDIRECT
#define SOLUTIONDIRECT

#include "instance.h"

typedef struct _SolutionDirect SolutionDirect;

struct _SolutionDirect
{
	Instance * instance;
	int * itemsTaken;
};

/**
 * Create a direct solution on the heap.
 *
 * @param instance A pointer to the instance associated with this solution.
 * @return A pointer to the solution on the heap.
 */
SolutionDirect * solutionDirect_create(Instance * instance);

/**
 * Destroy a solution previously created with solutionDirect_create.
 *
 * @param solution A pointer to the solution to destroy.
 */
void solutionDirect_destroy(SolutionDirect * solution);

/**
 * Give the score for a solution.
 *
 * @param solution A pointer to the solution.
 * @return The score.
 */
int solutionDirect_evaluate(SolutionDirect * solution);

/**
 * Tells if the solution is possible or not.
 *
 * @param solution A pointer to the solution.
 * @return Boolean representing if the solution is possible.
 */
int solutionDirect_doable(SolutionDirect * solution);

/**
 * Prints the solution to the screen.
 *
 * @param solution A pointer to the solution.
 */
void solutionDirect_print(SolutionDirect * solution);

/**
 * Save the solution to a file
 *
 * @param fileName The path to the file to write to.
 * @param solution A pointer to the solution.
 */
void solutionDirect_saveToFile(char * fileName, SolutionDirect * solution);

/**
 * Mark an item as being taken.
 *
 * @param solution A pointer to the SolutionDirect.
 * @param index The index of the item to take.
 */
void solutionDirect_takeItem(SolutionDirect * solution, int index);

//TODO
SolutionDirect * solutionDirect_duplicate(SolutionDirect * solutionDirect);

//TODO
int solutionDirect_isItemTaken(SolutionDirect * solution, int index);

#endif
