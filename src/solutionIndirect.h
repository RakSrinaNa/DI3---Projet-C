#ifndef SOLUTIONINDIRECT
#define SOLUTIONINDIRECT

#include "solutionIndirect.h"
#include "bag.h"
#include "instance.h"

typedef struct _SolutionIndirect SolutionIndirect;

struct _SolutionIndirect
{
	int * itemsOrder;
	Bag * bag;
	Instance * instance;
};

/**
 * Create a SolutionIndirect on  the heap.
 * @param instance The instance associated to the solution.
 * @return A pointer to the newly created solution.
 */
SolutionIndirect * solutionIndirect_create(Instance * instance);

/**
 * Destroy an instance previously created with solutionIndirect_create.
 *
 * @param solution A pointer to the solution to destroy.
 */
void solutionIndirect_destroy(SolutionIndirect * solution);

/**
 * Decode the solution.
 *
 * @param solution A pointer to the solution to decode.
 */
void solutionIndirect_decode(SolutionIndirect * solution);

/**
 * Calculate the score for the solution.
 *
 * @param solution A pointer to the solution to evaluate.
 * @return The score of the solution.
 */
int solutionIndirect_evaluate(SolutionIndirect * solution);

/**
 * Tells if the solution is valid.
 *
 * @param solution A pointer to the solution to verify.
 * @return A boolean representing if the solution is valid.
 */
int solutionIndirect_doable(SolutionIndirect * solution);

/**
 * Print the solution in the console.
 *
 * @param solution A pointer to the solution to print.
 */
void solutionIndirect_print(SolutionIndirect * solution);

/**
 * Save the solution into a file.
 *
 * @param fileName The path to the file to write.
 * @param solution A pointer to the solution to write.
 */
void solutionIndirect_saveToFile(char * fileName, SolutionIndirect * solution);

/**
 * Get the 'index'th item index of ordered items.
 *
 * @param solution A pointer to the solution.
 * @param index The index of the ordered item.
 * @return The index of the item.
 */
int solutionIndirect_getItemIndex(SolutionIndirect * solution, int index);

//TODO
SolutionIndirect * solutionIndirect_duplicate(SolutionIndirect * solution);

#endif
