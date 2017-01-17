#ifndef METAHEURISTICGENETIC
#define METAHEURISTICGENETIC

#include "solution.h"

typedef struct
{
	Solution ** persons;
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
 * @return A pointer to the best solution the metaheuristic found.
 */
Solution * metaheuristicGenetic_search(Instance * instance, SolutionType solutionType, int populationSize, float mutationProbability, int maxIterations); //TODO Unit

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
 * @param people A pointer to the solution to add.
 * @return 1 if the solution was added, 0 otherwise.
 */
int population_append(Population * population, Solution * people);

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
 * @return A pointer to the best solution. If several solutions have the same score, only the first one encountered will be kept.
 */
Solution * population_getBest(Population * population);

//TODO Doc
Solution * population_getWorst(Population * population); //TODO Unit

//TODO Doc
Population * population_duplicate(Population * population); //TODO Unit

//TODO Doc
void population_replace(Population * population, Solution * toReplace, Solution * replaceWith); //TODO Unit

//TODO Doc
void population_remove(Population * population, Solution * solution); //TODO Unit

//TODO Doc
void metaheuristicGenetic_selectParents(Population * population, Solution * parent1, Solution * parent2, int style); //TODO Unit

//TODO Doc
void metaheuristicGenetic_selectParentsFight(Population * population, Solution * parent1, Solution * parent2); //TODO Unit

//TODO Doc
void metaheuristicGenetic_selectParentsRoulette(Population * population, Solution * parent1, Solution * parent2); //TODO Unit

//TODO Doc
void metaheuristicGenetic_mutation(Solution * child); //TODO Unit

//TODO Doc
void metaheuristicGenetic_naturalSelection(Population ** population, Population * childPopulation, int style); //TODO Unit

//TODO Doc
Population * metaheuristicGenetic_naturalSelectionGeneration(Population * population); //TODO Unit

//TODO Doc
Population * metaheuristicGenetic_naturalSelectionElitist(Population * population, Population * childPopulation); //TODO Unit

//TODO Doc
Population * metaheuristicGenetic_naturalSelectionBalanced(Population * population, Population * childPopulation); //TODO Unit

#endif
