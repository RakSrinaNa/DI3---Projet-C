#include <stdlib.h>
#include <time.h>

#include "headers/metaheuristicGenetic.h"
#include "headers/utils.h"
#include "headers/heuristic.h"

Solution * metaheuristicGenetic_search(Instance * instance, SolutionType solutionType, int populationMaxSize, float mutationProbability, int maxIterations)
{
	//Random
	srand(time(NULL));

	Population * population = population_create(populationMaxSize);
	for(int i = 0; i < population->maxSize; i++)
		population_append(population, heuristic(instance, solutionType, 0));

	Solution * bestSolution = metaheuristicGenetic_bestFromPopulation(population);
	int scoreBest = solution_evaluate(bestSolution);

	int i = 0;
	while(i < maxIterations)
	{
		Population * childPopulation = population_create(populationMaxSize);
		for(int j = 0; j < populationMaxSize / 2; j++)
		{
			Solution * parent1 = NULL;
			Solution * parent2 = NULL;
			metaheuristicGenetic_selectParents(population, parent1, parent2, 0);

			Solution * child1 = NULL;
			Solution * child2 = NULL;
			metaheuristicGenetic_breedChildren(parent1, parent2, child1, child2);

			population_append(childPopulation, child1);
			population_append(childPopulation, child2);
		}

		for(int j = 0; j < childPopulation->size; j++)
		{
			int tempScore = solution_evaluate(childPopulation->persons[j]);
			if(tempScore > scoreBest)
			{
				scoreBest = tempScore;
				solution_destroy(bestSolution);
				bestSolution = solution_duplicate(childPopulation->persons[j]);
			}
			if(mutationProbability > (float) (rand() % RAND_MAX))
			{
				childPopulation->persons[j] = metaheuristicGenetic_mutation(childPopulation->persons[j]);
				tempScore = solution_evaluate(childPopulation->persons[j]);
				if(tempScore > scoreBest)
				{
					scoreBest = tempScore;
					solution_destroy(bestSolution);
					bestSolution = solution_duplicate(childPopulation->persons[j]);
				}
			}
		}
		metaheuristicGenetic_naturalSelection(population, childPopulation);
		i++;
	}

	population_destroy(population);
	return bestSolution;
}

void population_destroy(Population * population)
{
	for(int i = 0; i < population->size; i++)
		solution_destroy(population->persons[i]);
	free(population->persons);
	free(population);
}

void population_append(Population * population, Solution * people)
{
	if(population->size >= population->maxSize)
	{
		perror("Overpopulation population_append");
		exit(EXIT_FAILURE);
	}
	population->size++;
	RREALLOC(population->persons, Solution *, population->size, "population_destroy");
	population->persons[population->size - 1] = people;
}

Population * population_create(int populationMaxSize)
{
	Population * population;
	MMALLOC(population, Population, 1, "population_create");
	population->maxSize = populationMaxSize;
	population->size = 0;
	population->persons = NULL;
	return population;
}

Solution * metaheuristicGenetic_bestFromPopulation(Population * population)
{
	Solution * bestSolution = NULL;
	int bestScore = 0;
	for(int i = 0; i < population->size; i++)
	{
		int tempScore = solution_evaluate(population->persons[i]);
		if(tempScore > bestScore)
		{
			bestScore = tempScore;
			bestSolution = population->persons[i];
		}
	}

	return bestSolution;
}

void metaheuristicGenetic_selectParents(Population * population, Solution * parent1, Solution * parent2, int style)
{
	switch(style)
	{
		case 0:
			metaheuristicGenetic_selectParentsFight(population, parent1, parent2);
			break;

		case 1:
			metaheuristicGenetic_selectParentsRoulette(population, parent1, parent2);
			break;

		default:
			break;
	}
}

void metaheuristicGenetic_selectParentsFight(Population * population, Solution * parent1, Solution * parent2)
{
	int fighter1 = -1;
	int fighter2 = -1;
	int fighter3 = -1;
	int fighter4 = -1;
	while(fighter4 == -1)
	{
		int fighter = rand() % population->maxSize;
		if(fighter == fighter1 || fighter == fighter2 || fighter == fighter3 || fighter == fighter4)
			continue;
		else if(fighter1 == -1)
			fighter1 = fighter;
		else if(fighter2 == -1)
			fighter2 = fighter;
		else if(fighter3 == -1)
			fighter3 = fighter;
		else
			fighter4 = fighter;
	}
}

void metaheuristicGenetic_selectParentsRoulette(Population * population, Solution * parent1, Solution * parent2)
{
	int i = 0;
	long populationScore = population_evaluate(population);

	while(parent1 == NULL)
	{
		long score = solution_evaluate(population->persons[i]);
		if((float) rand() / RAND_MAX < (float) score / populationScore)
			parent1 = &(population->persons[i]);
		populationScore -= score;
		i++;
	}

	i = 0;
	while(parent2 == NULL || parent1 == parent2)
	{
		long score = solution_evaluate(population->persons[i]);
		if((float) rand() / RAND_MAX < (float) score / populationScore)
			parent2 = &(population->persons[i]);
		populationScore -= score;
		i++;
	}
}
