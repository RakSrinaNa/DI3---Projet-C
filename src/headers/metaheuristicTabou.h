#ifndef METHAHEURISTICTABOU
#define METHAHEURISTICTABOU

#include "instance.h"
#include "heuristic.h"

typedef struct
{
	int a;
	int b;
} Movement;

typedef struct
{
	Movement ** movements;
	int size;
	int changes;
	int max;
} Tabou;

/**
 * Verify if two movements are the same.
 *
 * @param m1 A pointer to the first movement.
 * @param m2 A pointer to the second movement.
 * @return 1 if equals, 0 else.
 */
int movement_equals(Movement * m1, Movement * m2);

/**
 * Create a tabou structure on the heap.
 *
 * @param tabouMax The maximum size of the list.
 * @return A pointer to the created Tabou.
 */
Tabou * tabou_create(int tabouMax);

/**
 * Starts the tabou metaheuristic function depending on the solutionType.
 *
 * @param instance A pointer to the instance.
 * @param solutionType The solution type.
 * @param iterationMax Number maximum of iterations on the same best value before we stop.
 * @param tabouMax Maximum size of the tabou array.
 * @param aspiration 1 if using the aspiration, 0 else.
 * @return A pointer to the best solution the metaheuristic found.
 */
Solution * metaheuristicTabou_search(Instance * instance, SolutionType solutionType, int iterationMax, int tabouMax, int aspiration);

/**
 * Appends a movement into a Tabou.
 *
 * @param tabou A pointer to the tabou to append into.
 * @param movement A pointer to the movement to add.
 */
void tabou_appendMovement(Tabou * tabou, Movement * movement);

/**
 * Used to know if a movement is present in a tabou.
 *
 * @param tabou A pointer to the Tabou to search in.
 * @param movement A pointer to the movement to search for.
 * @return 1 if found, 0 else.
 */
int tabou_isMovementTabou(Tabou * tabou, Movement * movement);

/**
 * Creates a new solution with a movement applied.
 *
 * @param solution A pointer to the solution to perform the movement on.
 * @param movement A pointer to the movement to apply.
 * @return A new solution on the heap with the movement applied.
 */
Solution * metaheuristicTabou_getNeighbourFromMovement(Solution * solution, Movement * movement);

/**
 * Return all the possible permutations of a solution.
 *
 * @param solution A pointer to the solution where to get the permutations.
 * @param movementCount A pointer to an int that will contain the number of movements found.
 * @return A list of pointer to movements.
 */
Movement ** metaheuristicTabou_getMovements(Solution * solution, int * movementCount);

/**
 * Apply a movement on a solution.
 *
 * @param solution A pointer to the solution to modify.
 * @param movement A pointer to the movement to apply.
 */
void movement_applyMovement(Solution * solution, Movement * movement);

/**
 * Destroys a Tabou structure.
 *
 * @param tabou A pointer to the Tabou to destroy.
 */
void tabou_destroy(Tabou * tabou);

/**
 * Duplicates a movement on the heap.
 *
 * @param movement A pointer to the movement to duplicate.
 * @return A pointer to the duplicated movement.
 */
Movement * movement_duplicate(Movement * movement);

#endif
