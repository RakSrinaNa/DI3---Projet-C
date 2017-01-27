#ifndef METAHEURISTICGENETIC
#define METAHEURISTICGENETIC

#include "solution.h"

typedef struct
{
	Solution ** people;
	int maxSize;
	int size;
} Population;

/**
 * Starts the genetic metaheuristic function depending on the solutionType.
 *
 * @param instance A pointer to the instance.
 * @param solutionType The solution type.
 * @param populationSize Number maximum of each population.
 * @param mutationProbability The probability between 0 and 1 of a child mutating.
 * @param maxIterations The maximum number of generation to create.
 * @param styleNaturalSelection The style of the natural selection.
 *  - 0: Replace all the parents by all the children
 *  - 1: Replace by the best of parents and children
 *  - 2: Replace by half best of parents and half best of children
 * @param styleParentSelection The style to select the parents:
 *  - 0: Selection by fighting
 *  - 1: Selection by quality of parents
 * @return A pointer to the best solution the metaheuristic found.
 */
Solution * metaheuristicGenetic_search(Instance * instance, SolutionType solutionType, int populationSize, float mutationProbability, int maxIterations, int styleNaturalSelection, int styleParentSelection);

/**
 * Creates a population structure.
 *
 * @param populationMaxSize The maximum size of the population.
 * @return A pointer to the Population.
 */
Population * population_create(int populationMaxSize);

/**
 * Add a solution to the population.
 *
 * @param population A pointer to the population to add into.
 * @param person A pointer to the solution to add.
 * @return 1 if the solution was added, 0 otherwise.
 */
int population_append(Population * population, Solution * person);

/**
 * Destroys a population.
 *
 * @param population A pointer to the population to destroy.
 */
void population_destroy(Population * population);

/**
 * Get the best solution in a population based on its score.
 *
 * @param population A pointer to the population in which to find the solution.
 * @return A pointer to a duplicate of the best solution. If several solutions have the same score, only the first one encountered will be kept.
 */
Solution * population_getBest(Population * population);

/**
 * Get the worst solution in a population based on its score.
 *
 * @param population A pointer to the population in which to find the solution.
 * @return A pointer to the worst solution. If several solutions have the same score, only the first one encountered will be kept.
 */
Solution * population_getWorst(Population * population);

/**
 * Duplicates a population.
 *
 * @param population A pointer to the population to duplicate.
 * @return A pointer to the duplicated population.
 */
Population * population_duplicate(Population * population);

/**
 * Replace a solution with another one in a Population.
 *
 * @param population A pointer to the population where to replace the solution.
 * @param toReplace A pointer to the solution to replace.
 * @param replaceWith A pointer to the solution to replace with.
 */
void population_replace(Population * population, Solution * toReplace, Solution * replaceWith);

/**
 * Remove a solution from a Population.
 *
 * @param population A pointer to the population in which we'll remove the solution.
 * @param solution A pointer to the solution to remove.
 */
void population_remove(Population * population, Solution * solution);

/**
 * Calculate the sum of the score of the people in the Population.
 *
 * @param population A pointer to the population to get the score from.
 * @return The score.
 */
long population_evaluate(Population * population);

/**
 * Choose two parents from a population depending of the style.
 *
 * @param population A pointer to the population.
 * @param parent1 An empty pointer to the first parent.
 * @param parent2 An empty pointer to the second parent.
 * @param style The style of the election.
 */
void metaheuristicGenetic_selectParents(Population * population, Solution ** parent1, Solution ** parent2, int style);

/**
 * Choose two parents with the Fighting method.
 *
 * @param population A pointer to the population.
 * @param parent1 An empty pointer to the first parent.
 * @param parent2 An empty pointer to the second parent.
 */
void metaheuristicGenetic_selectParentsFight(Population * population, Solution ** parent1, Solution ** parent2);

/**
 * Choose two parents with the random Roulette method.
 *
 * @param population A pointer to the population.
 * @param parent1 An empty pointer to the first parent.
 * @param parent2 An empty pointer to the second parent.
 */
void metaheuristicGenetic_selectParentsRoulette(Population * population, Solution ** parent1, Solution ** parent2);

/**
 * Create two children from the parents depending of the solution's type (direct or indirect).
 *
 * @param parent1 A pointer to the first parent.
 * @param parent2 A pointer to the second parent.
 * @param child1 An empty pointer to the first child.
 * @param child2 An empty pointer to the second child.
 */
void metaheuristicGenetic_breedChildren(Solution * parent1, Solution * parent2, Solution ** child1, Solution ** child2);

/**
 * Create two children from the parents with the PMX method.
 *
 * @param parent1 A pointer to the first parent.
 * @param parent2 A pointer to the second parent.
 * @param child1 An empty pointer to the first child.
 * @param child2 An empty pointer to the second child.
 */
void metaheuristicGenetic_breedChildrenPMX(Solution * parent1, Solution * parent2, Solution ** child1, Solution ** child2);

/**
 * Create two children from the parents with the 1-Point method.
 *
 * @param parent1 A pointer to the first parent.
 * @param parent2 A pointer to the second parent.
 * @param child1 An empty pointer to the first child.
 * @param child2 An empty pointer to the second child.
 */
void metaheuristicGenetic_breedChildren1Point(Solution * parent1, Solution * parent2, Solution ** child1, Solution ** child2);

/**
 * Create a random mutation in the given child.
 *
 * @param child The child susceptible to get a mutation.
 */
void metaheuristicGenetic_mutation(Solution * child);

/**
 * Choose a way to replace the old generation by the new one.
 *
 * @param population A pointer to the old population.
 * @param childPopulation A pointer to the new population.
 * @param style Style of the selection.
 */
void metaheuristicGenetic_naturalSelection(Population ** population, Population * childPopulation, int style);

/**
 * Just replace the old generation by all the new generation.
 *
 * @param childPopulation A pointer to the new population.
 * @return A pointer to a copy of the new population.
 */
Population * metaheuristicGenetic_naturalSelectionGeneration(Population * childPopulation);

/**
 * Select the best solutions from the old and the new population.
 *
 * @param population A pointer to the old population.
 * @param childPopulation A pointer to the new population.
 * @return A pointer to a generation containing the best solution of the old and the new population.
 */
Population * metaheuristicGenetic_naturalSelectionElitist(Population * population, Population * childPopulation);

/**
 * Select the best solutions from the best half of the old population and the best half of the new population.
 *
 * @param population A pointer to the old population.
 * @param childPopulation A pointer to the new population.
 * @return A pointer to a generation containing the best half of the old population and the best half of the new population.
 */
Population * metaheuristicGenetic_naturalSelectionBalanced(Population * population, Population * childPopulation);

#endif
