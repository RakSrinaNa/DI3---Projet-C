#include <stdio.h>
#include <stdlib.h>

#include "headers/instance.h"
#include "headers/solutionDirect.h"
#include "headers/heuristic.h"
#include "headers/metaheuristicLocal.h"
#include "headers/utils.h"

Solution * metaheuristicLocal_search(Instance * instance, SolutionType solutionType, int searchOperator, int schedulerType)
{
	Solution * currentSolution = heuristic_search(instance, solutionType, schedulerType);
	Solution * bestSolution = solution_duplicate(currentSolution);

	int scoreBest = solution_evaluate(bestSolution);
	int scoreCurrent = solution_evaluate(currentSolution);

	int stop = 0;

	int scorePrevious = scoreCurrent;

	while(!stop)
	{
		Solution * bestNeighbourSolution = NULL;
		int scoreBestNeighbour = 0;

		int neighboursCount = 0;
		Solution ** allNeighbours = metaheuristicLocal_getNeighbours(currentSolution, searchOperator, &neighboursCount);

		for(int i = 0; i < neighboursCount; i++)
		{
			int tempScore = solution_evaluate(allNeighbours[i]);
			if(tempScore > scoreBestNeighbour)
			{
				solution_destroy(bestNeighbourSolution);
				bestNeighbourSolution = solution_duplicate(allNeighbours[i]);
				scoreBestNeighbour = tempScore;
			}
		}

		for(int i = 0; i < neighboursCount; i++)
			solution_destroy(allNeighbours[i]);
		free(allNeighbours);

		solution_destroy(currentSolution);

		scoreCurrent = scoreBestNeighbour;
		currentSolution = solution_duplicate(bestNeighbourSolution);

		if(scoreCurrent > scoreBest)
		{
			scoreBest = scoreCurrent;
			solution_destroy(bestSolution);
			bestSolution = solution_duplicate(currentSolution);
		}
		else
		{
			if(scoreCurrent <= scorePrevious)
				stop = 1;
		}

		scorePrevious = scoreCurrent;

		solution_destroy(bestNeighbourSolution);
	}
	solution_destroy(currentSolution);

	return bestSolution;
}

Solution ** metaheuristicLocal_getNeighbours(Solution * currentSolution, int searchOperator, int * neighboursCount)
{
	switch(currentSolution->type)
	{
		case DIRECT:
			switch(searchOperator)
			{
				case 0:
					return metaheuristicLocal_addAndInvertItem(currentSolution, neighboursCount);

				default:
					break;
			}
		default:
			switch(searchOperator)
			{
				case 0:
					return metaheuristicLocal_swapItem(currentSolution, neighboursCount);

				default:
					break;
			}
	}

	return NULL;
}

Solution ** metaheuristicLocal_swapItem(Solution * currentSolution, int * neighboursCount)
{
	Solution ** neighbourSolutions = NULL;

	//G�n�re toutes les permutations possibles et les transforme en solution
	for(int i = 0; i < currentSolution->solutions.indirect->instance->itemsCount; i++)
		for(int j = i + 1; j < currentSolution->solutions.indirect->instance->itemsCount; j++)
		{
			Solution * neighbourSolution = solution_duplicate(currentSolution);

			int indexSwap = solutionIndirect_getItemIndex(neighbourSolution->solutions.indirect, i);
			neighbourSolution->solutions.indirect->itemsOrder[i] = solutionIndirect_getItemIndex(neighbourSolution->solutions.indirect, j);
			neighbourSolution->solutions.indirect->itemsOrder[j] = indexSwap;

			solutionIndirect_decode(neighbourSolution->solutions.indirect);
			if(solution_doable(neighbourSolution))
			{
				(*neighboursCount)++;
				RREALLOC(neighbourSolutions, Solution*, *neighboursCount, "metaheuristicLocal_swapItem");
				neighbourSolutions[*neighboursCount - 1] = neighbourSolution;
			}
			else
				solution_destroy(neighbourSolution);
		}

	return neighbourSolutions;
}

Solution ** metaheuristicLocal_addItem(Solution * currentSolution, int * neighboursCount)
{
	Solution ** neighbourSolutions = NULL;

	//Essaie d'ajouter chaque item qui n'y est pas d�j� tout en v�rifiant que la solution ainsi obtenue est faisable
	for(int i = 0; i < currentSolution->instance->itemsCount; i++)
		if(currentSolution->solutions.direct->itemsTaken[i] == 0)
		{
			Solution * neighbourSolution = solution_duplicate(currentSolution);
			neighbourSolution->solutions.direct->itemsTaken[i] = 1;

			if(solution_doable(neighbourSolution))
			{
				(*neighboursCount)++;
				RREALLOC(neighbourSolutions, Solution*, *neighboursCount, "metaheuristicLocal_addItem");
				neighbourSolutions[*neighboursCount - 1] = neighbourSolution;
			}
			else
				solution_destroy(neighbourSolution);
		}
	return neighbourSolutions;
}

Solution ** metaheuristicLocal_invertItem(Solution * currentSolution, int * neighboursCount)
{
	Solution ** neighbourSolutions = NULL;

	//G�n�re toutes les invertions d'items possibles
	for(int i = 0; i < currentSolution->solutions.direct->instance->itemsCount; i++)
		if(currentSolution->solutions.direct->itemsTaken[i])
		{
			for(int j = 0; j < currentSolution->solutions.direct->instance->itemsCount; j++)
			{
				if(j == i)
					continue;
				if(currentSolution->solutions.direct->itemsTaken[j] == 0)
				{
					Solution * neighbourSolution = solution_duplicate(currentSolution);
					neighbourSolution->solutions.direct->itemsTaken[i] = 0;
					neighbourSolution->solutions.direct->itemsTaken[j] = 1;

					if(solution_doable(neighbourSolution))
					{
						(*neighboursCount)++;
						RREALLOC(neighbourSolutions, Solution*, *neighboursCount, "metaheuristicLocal_invertItem");
						neighbourSolutions[*neighboursCount - 1] = neighbourSolution;
					}
					else
						solution_destroy(neighbourSolution);
				}
			}
		}
	return neighbourSolutions;
}

Solution ** metaheuristicLocal_addAndInvertItem(Solution * currentSolution, int * neighboursCount)
{
	int addCount = 0;
	Solution ** addTempo = metaheuristicLocal_addItem(currentSolution, &addCount);

	int invertCount = 0;
	Solution ** invertTempo = metaheuristicLocal_invertItem(currentSolution, &invertCount);

	RREALLOC(invertTempo, Solution *, addCount + invertCount, "metaheuristicLocal_addAndInvertItem");

	for(int i = 0; i < addCount; i++)
		invertTempo[i + invertCount] = addTempo[i];

	free(addTempo);
	*neighboursCount = addCount + invertCount;
	return invertTempo;
}
