#ifndef METAHEURISTICGENETIC
#define METAHEURISTICGENETIC

#include "solution.h"

typedef struct
{
	Solution ** persons;
	int maxSize;
	int size;
} Population;

Solution * metaheuristicGenetic_search(Instance * instance, SolutionType solutionType, int populationSize, float mutationProbability, int maxIterations);

Population * population_create(int populationMaxSize);

void population_append(Population * population, Solution * people);

void population_destroy(Population * population);

Solution * metaheuristicGenetic_bestFromPopulation(Population * population);

void metaheuristicGenetic_selectParents(Population * population, Solution * parent1, Solution * parent2, int style);

void metaheuristicGenetic_selectParentsFight(Population * population, Solution * parent1, Solution * parent2);

void metaheuristicGenetic_selectParentsRoulette(Population * population, Solution * parent1, Solution * parent2);

void metaheuristicGenetic_mutation(Solution * child);

void metaheuristicGenetic_naturalSelection(Population * population, Population * childPopulation);

void metaheuristicGenetic_naturalSelectionGeneretion(Population * childPopulation, Population * newPopulation);

#endif
