#ifndef METAHEURISTIC
#define METAHEURISTIC

#include "instance.h"
#include "solutionDirect.h"
#include "scheduler.h"
#include "heuristic.h"
#include "metaheuristicLocal.h"

/**
 * Starts the local metaheuristic function depending on the solutionType and schedulerType.
 *
 * @param instance A pointer to the instance.
 * @param solutionType The solution type.
 * @param operatorSearch The search operator:
 *  - DIRECT:
 *   * 0 -> Use the add and invert operator.
 *  - INDIRECT:
 *   * 0 -> Use the swap item operator.
 * @param schedulerType The scheduler number to use to start the metaheuristic. See heuristic function (heuristic.h).
 * @return A pointer to the best solution the metaheuristic found.
 */
Solution * metaheuristicLocal_search(Instance * instance, SolutionType solutionType, int operatorSearch, int schedulerType);

/**
 * Get a list of candidates for being the best solution.
 *
 * @param currentSolution A pointer to the solution where the operator will be applied.
 * @param searchOperator The operator to use. See metaheuristicLocal_search function.
 * @param neighboursCount A pointer to an int that will contain the amount of candidates.
 * @return A list of pointer to solutions.
 */
Solution ** metaheuristicLocal_getNeighbours(Solution * currentSolution, int searchOperator, int * neighboursCount);

/**
 * Create a list of candidates by swapping one time items in pairs.
 *
 * @param currentSolution A pointer to the solution where the operator will be applied. The solution must be indirect.
 * @param neighboursCount A pointer to an int that will contain the amount of candidates.
 * @return A list of pointer to solutions.
 */
Solution ** metaheuristicLocal_swapItem(Solution * currentSolution, int * neighboursCount);

/**
 * Create a list of candidates by adding an item.
 *
 * @param currentSolution A pointer to the solution where the operator will be applied. The solution must be direct.
 * @param neighboursCount A pointer to an int that will contain the amount of candidates.
 * @return A list of pointer to solutions.
 */
Solution ** metaheuristicLocal_addItem(Solution * currentSolution, int * neighboursCount);

/**
 * Create a list of candidates by inverting two items.
 *
 * @param currentSolution A pointer to the solution where the operator will be applied. The solution must be direct.
 * @param neighboursCount A pointer to an int that will contain the amount of candidates.
 * @return A list of pointer to solutions.
 */
Solution ** metaheuristicLocal_invertItem(Solution * currentSolution, int * neighboursCount);

/**
 * Create a list of candidates by inverting two items and by adding an item.
 *
 * @param currentSolution A pointer to the solution where the operator will be applied. The solution must be direct.
 * @param neighboursCount A pointer to an int that will contain the amount of candidates.
 * @return A list of pointer to solutions.
 */
Solution ** metaheuristicLocal_addAndInvertItem(Solution * currentSolution, int * neighboursCount);

#endif
