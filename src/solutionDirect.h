#ifndef SOLUTIONDIRECT
#define SOLUTIONDIRECT

#include "instance.h"

typedef struct
{
	int * itemsTaken;

	// Functions
	int (* evaluate)(Instance * instance, int * items);

	int (* doable)(Instance * instance, int * items);

	void (* print)(Instance * instance, int * items);

	void (* saveToFile)(char * fileName, Instance * instance, int * items);
} SolutionDirect;

/**
 * Create a direct solution on the heap.
 *
 * @param instance A pointer to the instance associated with this solution.
 * @return A pointer to the solution on the heap.
 */
SolutionDirect * solutionDirect_create(Instance * instance);

/**
 * Destroy a solution previously created with solutionDirect_create.
 * @param solution A pointer to the solution to destroy.
 */
void solutionDirect_destroy(SolutionDirect * solution);

/**
 * Give the score for a solution.
 *
 * @param instance A pointer to the instance associated with the solution.
 * @param items The items taken in the bag (array of booleans).
 * @return The score.
 */
int solutionDirect_evaluate(Instance * instance, int * items);

/**
 * Tells if the solution is possible or not.
 *
 * @param instance A pointer to the instance associated with the solution.
 * @param items The items taken in the bag (array of booleans).
 * @return Boolean representing if the solution is possible.
 */
int solutionDirect_doable(Instance * instance, int * items);

/**
 * Prints the solution to the screen.
 *
 * @param instance A pointer to the instance associated with the solution.
 * @param items The items taken in the bag (array of booleans).
 */
void solutionDirect_print(Instance * instance, int * items);

/**
 * Save the solution to a file
 *
 * @param fileName The path to the file to write to.
 * @param instance A pointer to the instance associated with the solution.
 * @param items The items taken in the bag (array of booleans).
 */
void solutionDirect_saveToFile(char * fileName, Instance * instance, int * items);

/**
 * Mark an item as being taken.
 *
 * @param solution A pointer to the SolutionDirect.
 * @param index The index of the item to take.
 */
void solutionDirect_takeItem(SolutionDirect * solution, int index);

#endif
