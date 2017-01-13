#ifndef METAHEURISTICGENETIC
#define METAHEURISTICGENETIC

Solution * metaheuristicGenetic_search(Instance * instance, SolutionType solutionType, int populationSize, float mutationProbability, int maxIterations);

Solution ** metaheuristicGenetic_firstPopulation(Instance * instance, SolutionType SolutionType, int populationMaxSize);

Solution * metaheuristicGenetic_bestFromPopulation(Solution ** population, int populationMaxSize);

void metaheuristicGenetic_selectParents(Solution ** population, int populationMaxSize, Solution * parent1, Solution * parent2, int style);

void metaheuristicGenetic_selectParentsFight(Solution ** population, int populationMaxSize, Solution * parent1, Solution * parent2);

void metaheuristicGenetic_selectParentsRoulette(Solution ** population, int populationMaxSize, Solution * parent1, Solution * parent2);

#endif
