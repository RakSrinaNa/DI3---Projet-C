#include <stdlib.h>
#include <time.h>

#include "headers/metaheuristicGenetic.h"
#include "headers/solution.h"
#include "headers/utils.h"
#include "headers/heuristic.h"

Solution * metaheuristicGenetic_search(Instance * instance, SolutionType solutionType, int populationMaxSize, float mutationProbability, int maxIterations)
{
	//Random
	srand(time(NULL));

	Solution ** population = metaheuristicGenetic_firstPopulation(instance, solutionType, populationMaxSize);
	int populationSize = 0;

	Solution * bestSolution = metaheuristicGenetic_bestFromPopulation(population, populationMaxSize);
	int scoreBest = solution_evaluate(bestSolution);

	
	int i = 0;
	while(i < maxIterations)
	{
		Solution ** childPopulation = NULL;
		for(int j = 0; j < populationMaxSize/2; j++)
		{
			Solution * parent1 = NULL; Solution * parent2 = NULL;
			metaheuristicGenetic_selectParents(population, populationMaxSize, parent1, parent2, 0);

			Solution * child1 = NULL; Solution * child2 = NULL;
			metaheuristicGenetic_breedChildren(parent1, parent2, child1, child2);

			metaheuristicGenetic_addToPopulation(childPopulation, &populationSize, child1, child2);
		}

		for(int j = 0; j < populationSize; j++)
		{
			if(solution_evaluate(childPopulation[j]) > scoreBest)
			{
                scoreBest = solution_evaluate(childPopulation[j]);
                solution_destroy(bestSolution);
                bestSolution = solution_duplicate(childPopulation[j]);
			}
			if(mutationProbability > (float)(rand() % RAND_MAX))
			{
				childPopulation[j] = metaheuristicGenetic_mutation(childPopulation[j]);
				if(solution_evaluate(childPopulation[j]) > scoreBest)
				{
					scoreBest = solution_evaluate(childPopulation[j]);
					solution_destroy(bestSolution);
					bestSolution = solution_duplicate(childPopulation[j]);
				}
			}

		}
        metaheuristicGenetic_naturalSelection(population, childPopulation);
		i++;
	}

	metaheuristicGenetic_killPopulation(population, populationMaxSize);
	return bestSolution;
}

Solution ** metaheuristicGenetic_firstPopulation(Instance * instance, SolutionType solutionType, int populationMaxSize)
{
    Solution ** population;
    MMALLOC(population, Solution *, populationMaxSize, "metaheuristicGenetic_firstPopulation");
    for(int i = 0; i < populationMaxSize; i++)
		population[i] = heuristic(instance, solutionType, 0);

	return population;
}

Solution * metaheuristicGenetic_bestFromPopulation(Solution ** population, int populationMaxSize)
{
	Solution * bestSolution = NULL;
	int bestScore = 0;
	for(int i = 0; i < populationMaxSize; i++)
        if(solution_evaluate(population[i]) > bestScore)
		{
			bestScore = solution_evaluate(population[i]);
			bestSolution = population[i];
		}

	return bestSolution;
}

void metaheuristicGenetic_selectParents(Solution ** population, int populationMaxSize, Solution * parent1, Solution * parent2, int style)
{
	switch(style)
	{
		case 0:
			metaheuristicGenetic_selectParentsFight(population, populationMaxSize, parent1, parent2);
			break;
	
		case 1:
			metaheuristicGenetic_selectParentsRoulette(population, populationMaxSize, parent1, parent2);
			break;
			
		default:
			break;
	}
}

void metaheuristicGenetic_selectParentsFight(Solution ** population, int populationMaxSize, Solution * parent1, Solution * parent2)
{
	int fighter1 = -1; int fighter2 = -1; int fighter3 = -1; int fighter4 = -1;
	while(fighter4 == -1)
	{
        int fighter = rand()%populationMaxSize;
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

void metaheuristicGenetic_selectParentsRoulette(Solution ** population, int populationMaxSize, Solution * parent1, Solution * parent2)
{
    int i = 0;
    long populationScore = population_evaluate(population, populationMaxSize);

    while(parent1 == NULL)
	{
		long score = solution_evaluate(population[i]);
		if((float)rand()/RAND_MAX < (float)score/populationScore)
				parent1 = population[i];
		populationScore -= score;
		i++;
	}

	while(parent2 == NULL || parent1 == parent2)
	{
		long score = solution_evaluate(population[i]);
		if((float)rand()/RAND_MAX < (float)score/populationScore)
				parent2 = population[i];
		populationScore -= score;
		i++;
	}
}
