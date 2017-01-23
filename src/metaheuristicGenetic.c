#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "headers/solutionIndirect.h"
#include "headers/solutionDirect.h"
#include "headers/solution.h"
#include "headers/metaheuristicGenetic.h"
#include "headers/utils.h"
#include "headers/heuristic.h"
#include "headers/instance.h"

Solution * metaheuristicGenetic_search(Instance * instance, SolutionType solutionType, int populationMaxSize, float mutationProbability, int maxIterations, int styleNaturalSelection)
{
	//Random
	srand(time(NULL));

	Population * population = population_create(populationMaxSize);
	for(int i = 0; i < population->maxSize; i++)
		population_append(population, heuristic_search(instance, solutionType, 0));

	Solution * bestSolution = population_getBest(population);
	int scoreBest = solution_evaluate(bestSolution);

	int i = 0;
	while(i < maxIterations)
	{
		Population * childPopulation = population_create(populationMaxSize);
		for(int j = 0; j < populationMaxSize / 2; j++)
		{
			Solution * parent1 = NULL;
			Solution * parent2 = NULL;
			metaheuristicGenetic_selectParents(population, &parent1, &parent2, 1);

			Solution * child1 = NULL;
			Solution * child2 = NULL;
			metaheuristicGenetic_breedChildren(parent1, parent2, &child1, &child2);
			
			if(!population_append(childPopulation, child1))
				solution_destroy(child1);
			if(!population_append(childPopulation, child2))
				solution_destroy(child2);
		}

		for(int j = 0; j < childPopulation->size; j++)
		{
			int tempScore = solution_evaluate(childPopulation->people[j]);
			if(tempScore > scoreBest && solution_doable(childPopulation->people[j]))
			{
				scoreBest = tempScore;
				solution_destroy(bestSolution);
				bestSolution = solution_duplicate(childPopulation->people[j]);
			}
			if(mutationProbability > (float) (rand()) / RAND_MAX)
			{
				metaheuristicGenetic_mutation(childPopulation->people[j]);
				tempScore = solution_evaluate(childPopulation->people[j]);
				if(tempScore > scoreBest && solution_doable(childPopulation->people[j]))
				{
					scoreBest = tempScore;
					solution_destroy(bestSolution);
					bestSolution = solution_duplicate(childPopulation->people[j]);
				}
			}
		}
		metaheuristicGenetic_naturalSelection(&population, childPopulation, styleNaturalSelection);
		i++;
	}

	population_destroy(population);
	return bestSolution;
}

Population * population_create(int populationMaxSize)
{
	Population * population;
	MMALLOC(population, Population, 1, "population_create");
	population->maxSize = populationMaxSize;
	population->size = 0;
	population->people = NULL;
	return population;
}

void population_destroy(Population * population)
{
	for(int i = 0; i < population->size; i++)
		solution_destroy(population->people[i]);
	free(population->people);
	free(population);
}

Population * population_duplicate(Population * population)
{
	Population * newPopulation = population_create(population->maxSize);

	for(int i = 0; i < population->size; i++)
        population_append(newPopulation, solution_duplicate(population->people[i]));

	return newPopulation;
}

int population_append(Population * population, Solution * person)
{
	if(population->size >= population->maxSize)
		return 0;
	population->size++;
	RREALLOC(population->people, Solution *, population->size, "population_destroy");
	population->people[population->size - 1] = person;
	return 1;
}

void population_remove(Population * population, Solution * solution)
{
	int i = 0;
	while(population->size > i && population->people[i] != solution)
		i++;
	if(i < population->size)
	{
		solution_destroy(population->people[i]);
		for(int j = i; j < population->size - 1; j++)
			population->people[j] = population->people[j + 1];
	}
	population->size--;
}

Solution * population_getBest(Population * population)
{
	Solution * bestSolution = NULL;
	int bestScore = -1;
	for(int i = 0; i < population->size; i++)
	{
		int tempScore = solution_evaluate(population->people[i]);
		if(tempScore > bestScore)
		{
			bestScore = tempScore;
			solution_destroy(bestSolution);
			bestSolution = solution_duplicate(population->people[i]);
		}
	}

	return bestSolution;
}

Solution * population_getWorst(Population * population)
{
	Solution * worstSolution = NULL;
	int worstScore = INT_MAX;
	for(int i = 0; i < population->size; i++)
	{
		int tempScore = solution_evaluate(population->people[i]);
		if(tempScore < worstScore)
		{
			worstScore = tempScore;
			worstSolution = population->people[i];
		}
	}

	return worstSolution;
}

void population_replace(Population * population, Solution * toReplace, Solution * replaceWith)
{
	population_remove(population, toReplace);
	population_append(population, replaceWith);
}

long population_evaluate(Population * population)
{
    long score = 0;
    for(int i = 0; i < population->size; i++)
		score += solution_evaluate(population->people[i]);
	return score;
}

void metaheuristicGenetic_selectParents(Population * population, Solution ** parent1, Solution ** parent2, int style)
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

void metaheuristicGenetic_selectParentsFight(Population * population, Solution ** parent1, Solution ** parent2)
{
	int fighter1 = -1;
	int fighter2 = -1;
	int fighter3 = -1;
	int fighter4 = -1;
	while(fighter4 == -1)
	{
		int fighter = rand() % population->size;
		if(fighter == fighter1 || fighter == fighter2 || fighter == fighter3 || fighter == fighter4) //Si le nouveau fighter est deja selectionne alors on ne le prend pas
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

	if(solution_evaluate(population->people[fighter1]) > solution_evaluate(population->people[fighter2]))
		*parent1 = population->people[fighter1];
	else
		*parent1 = population->people[fighter2];

	if(solution_evaluate(population->people[fighter3]) > solution_evaluate(population->people[fighter4]))
		*parent2 = population->people[fighter3];
	else
		*parent2 = population->people[fighter4];

}

void metaheuristicGenetic_selectParentsRoulette(Population * population, Solution ** parent1, Solution ** parent2)
{
	int i = 0;
	long populationScore = population_evaluate(population);

	while(*parent1 == NULL)
	{
		int score = solution_evaluate(population->people[i]);
		if((float) rand() / RAND_MAX <= (float) score / populationScore) //Compare avec le ratio de la solution courrante sur le score de la population restante
		{
			*parent1 = population->people[i];
			break;
        }
		populationScore -= score; //populationScore est egal au score de la population restante
		i++;
	}

	i = 0;
	while(*parent2 == NULL || *parent1 == *parent2)
	{
		int score = solution_evaluate(population->people[i]);
		if((float) rand() / RAND_MAX <= (float) score / populationScore)
		{
			*parent2 = population->people[i];
			break;
        }
		populationScore -= score;
		i++;
	}
}

void metaheuristicGenetic_breedChildren(Solution * parent1, Solution * parent2, Solution ** child1, Solution ** child2)
{
    if(parent1->type != parent2->type)
    {
		perror("metaheuristicGenetic_breedChildren");
		exit(EXIT_FAILURE);
    }

    switch(parent1->type)
    {
	case DIRECT:
		metaheuristicGenetic_breedChildren1Point(parent1, parent2, child1, child2);
		break;

	case INDIRECT:
		metaheuristicGenetic_breedChildrenPMX(parent1, parent2, child1, child2);
		    solutionIndirect_decode((*child1)->solutions.indirect);
		    solutionIndirect_decode((*child2)->solutions.indirect);
		break;
    }
}

void metaheuristicGenetic_breedChildrenPMX(Solution * parent1, Solution * parent2, Solution ** child1, Solution ** child2)
{
	int cut1 = (rand() % (parent1->solutions.indirect->instance->itemsCount-2))+1;
	int cut2 = rand() % parent2->solutions.indirect->instance->itemsCount;
	while (cut2 <= cut1)
		cut2 = rand() % parent2->solutions.indirect->instance->itemsCount;

    *child1 = solution_fromIndirect(solutionIndirect_create(parent1->solutions.indirect->instance));
    *child2 = solution_fromIndirect(solutionIndirect_create(parent2->solutions.indirect->instance));

	for(int i = 0; i < parent1->instance->itemsCount; i++)
		if(i < cut1 || i >= cut2)
		{
			(*child1)->solutions.indirect->itemsOrder[i] = solutionIndirect_getItemIndex(parent1->solutions.indirect, i);
			(*child2)->solutions.indirect->itemsOrder[i] = solutionIndirect_getItemIndex(parent2->solutions.indirect, i);
		}

	for(int i = cut1; i < cut2; i++)
	{
		int item = solutionIndirect_getItemIndex(parent2->solutions.indirect, i);
		while(solutionIndirect_getIndexItem((*child1)->solutions.indirect, item) != -1)
			item = solutionIndirect_getItemIndex(parent1->solutions.indirect, solutionIndirect_getIndexItem(parent2->solutions.indirect, item));
		(*child1)->solutions.indirect->itemsOrder[i] = item;

		item = solutionIndirect_getItemIndex(parent1->solutions.indirect, i);
		while(solutionIndirect_getIndexItem((*child2)->solutions.indirect, item) != -1)
			item = solutionIndirect_getItemIndex(parent2->solutions.indirect, solutionIndirect_getIndexItem(parent1->solutions.indirect, item));
		(*child2)->solutions.indirect->itemsOrder[i] = item;
	}
}

void metaheuristicGenetic_breedChildren1Point(Solution * parent1, Solution * parent2, Solution ** child1, Solution ** child2)
{
	int cut = (rand() % (parent1->instance->itemsCount-2))+1;

    *child1 = solution_fromDirect(solutionDirect_create(parent1->instance));
    *child2 = solution_fromDirect(solutionDirect_create(parent2->instance));

    for(int i = 0; i < cut; i++)
	{
        (*child1)->solutions.direct->itemsTaken[i] = solutionDirect_isItemTaken(parent2->solutions.direct, i);
        (*child2)->solutions.direct->itemsTaken[i] = solutionDirect_isItemTaken(parent1->solutions.direct, i);
	}

	for(int i = cut; i < parent1->instance->itemsCount; i++)
	{
        (*child1)->solutions.direct->itemsTaken[i] = solutionDirect_isItemTaken(parent1->solutions.direct, i);
        (*child2)->solutions.direct->itemsTaken[i] = solutionDirect_isItemTaken(parent2->solutions.direct, i);

        if(!solution_doable(*child1))
			(*child1)->solutions.direct->itemsTaken[i] = 0;
        if(!solution_doable(*child2))
			(*child2)->solutions.direct->itemsTaken[i] = 0;
	}

	for(int i = parent1->instance->itemsCount-1; i >= 0; i--)
	{
        if(!solutionDirect_isItemTaken((*child1)->solutions.direct, i))
        {
			solutionDirect_takeItem((*child1)->solutions.direct, i);
			if(!solution_doable(*child1))
				(*child1)->solutions.direct->itemsTaken[i] = 0;
        }

        if(!solutionDirect_isItemTaken((*child2)->solutions.direct, i))
        {
			solutionDirect_takeItem((*child2)->solutions.direct, i);
			if(!solution_doable(*child2))
				(*child2)->solutions.direct->itemsTaken[i] = 0;
        }
	}

}

void metaheuristicGenetic_mutation(Solution * child)
{
	int index = 0;
    switch(child->type)
    {
	case DIRECT:
		index = rand() % child->instance->itemsCount;
		child->solutions.direct->itemsTaken[index] = abs(child->solutions.direct->itemsTaken[index] - 1);
		break;

	case INDIRECT:
		index = rand() % child->instance->itemsCount;
		int indexEnd = index + rand() % (child->instance->itemsCount - index);

		int object = -1;
		for(int i = 0; i < child->instance->itemsCount; i++)
		{
			if(i == index)
				object = solutionIndirect_getItemIndex(child->solutions.indirect, i);
			if(i > index && i <= indexEnd)
				child->solutions.indirect->itemsOrder[i-1] = solutionIndirect_getItemIndex(child->solutions.indirect, i);
			if(i == indexEnd)
				child->solutions.indirect->itemsOrder[i] = object;

		}
		break;
    }
}

void metaheuristicGenetic_naturalSelection(Population ** population, Population * childPopulation, int style)
{
	Population * newPopulation;
	switch(style)
	{
	case 0:
		newPopulation = metaheuristicGenetic_naturalSelectionGeneration(childPopulation);
		break;
	case 1:
		newPopulation = metaheuristicGenetic_naturalSelectionElitist(*population, childPopulation);
		break;
	case 2:
		newPopulation = metaheuristicGenetic_naturalSelectionBalanced(*population, childPopulation);
		break;
	default:
		perror("NATURAL SELECTION STYLE OVERSWAG");
		exit(EXIT_FAILURE);
	}
	population_destroy(childPopulation);
	population_destroy(*population);
	*population = newPopulation;

}

Population * metaheuristicGenetic_naturalSelectionGeneration(Population * childPopulation)
{
    Population * newPopulation = population_duplicate(childPopulation);
    return newPopulation;
}

Population * metaheuristicGenetic_naturalSelectionElitist(Population * population, Population * childPopulation)
{
    Population * newPopulation = population_duplicate(population);

	Solution * worst = population_getWorst(newPopulation);

	int i = 0;
	while(i < childPopulation->size)
	{
		if(solution_evaluate(childPopulation->people[i]) > solution_evaluate(worst))
		{
			population_replace(newPopulation, worst, solution_duplicate(childPopulation->people[i]));
			worst = population_getWorst(newPopulation);
		}
		i++;
	}

	return newPopulation;
}

Population * metaheuristicGenetic_naturalSelectionBalanced(Population * population, Population * childPopulation)
{
	Population * newPopulation = population_duplicate(population);
	Population * newPopulationChild = population_duplicate(childPopulation);

	while(newPopulation->size > newPopulation->maxSize/2)
		population_remove(newPopulation, population_getWorst(newPopulation));

	while(newPopulationChild->size > newPopulationChild->maxSize/2)
		population_remove(newPopulationChild, population_getWorst(newPopulationChild));

	Population * finalPopulation = population_create(population->maxSize);

	for(int i = 0; i < newPopulation->size; i++)
		population_append(finalPopulation, solution_duplicate(newPopulation->people[i]));

	for(int i = 0; i < newPopulationChild->size; i++)
		population_append(finalPopulation, solution_duplicate(newPopulationChild->people[i]));

	population_destroy(newPopulation);
	population_destroy(newPopulationChild);

	return finalPopulation;
}
