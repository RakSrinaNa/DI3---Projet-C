#include <stdbool.h>
#include <stdlib.h>

#include "headers/utils.h"
#include "headers/metaheuristicLocal.h"
#include "headers/metaheuristicTabou.h"
#include "headers/solution.h"

int movement_equals(Movement * m1, Movement * m2)
{
	if((m1->a == m2->a && m1->b == m2->b) || (m1->a == m2->b && m1->b == m2->a))
		return 1;
	return 0;
}

Solution * metaheuristicTabou_search(Instance * instance, SolutionType solutionType, int iterationMax, int tabouMax, int aspiration)
{
	struct timeb timeStart, timeEnd;
	ftime(&timeStart);

	Solution * currentSolution = heuristic(instance, solutionType, 5);
	Solution * bestSolution = solution_duplicate(currentSolution);

	int scoreBest = solution_evaluate(bestSolution);

	Movement ** tabou = NULL;
	int tabouChanges = 0;

	int i = 0;

	while(i < iterationMax)
	{
		int scoreBestNeighbour = 0;
		int movementsCount = 0;

		Movement ** movementsPossible = metaheuristicTabou_getMovements(currentSolution, &movementsCount);

		Solution * bestNeighbourSolution = NULL;

		Movement * usefulMovement = NULL;

		for(int j = 0; j < movementsCount; j++)
		{
			if(!metaheuristicTabou_isTabou(tabou, tabouMax, tabouChanges, movementsPossible[j]) || aspiration)
			{
				Solution * neighbourSolution = metaheuristicTabou_getNeighbourFromMovement(currentSolution, movementsPossible[j]);

				if(!metaheuristicTabou_isTabou(tabou, tabouMax, tabouChanges, movementsPossible[j]))
				{
					if(solution_evaluate(neighbourSolution) > scoreBestNeighbour)
					{
						solution_destroy(bestNeighbourSolution);
						free(usefulMovement);

						bestNeighbourSolution = solution_duplicate(neighbourSolution);
						scoreBestNeighbour = solution_evaluate(neighbourSolution);
						usefulMovement = movement_duplicate(movementsPossible[j]);
					}
					solution_destroy(neighbourSolution);
				}
				else
				{
					if(solution_evaluate(neighbourSolution) > scoreBest)
					{
						solution_destroy(bestNeighbourSolution);
						free(usefulMovement);

						bestNeighbourSolution = solution_duplicate(neighbourSolution);
						scoreBestNeighbour = solution_evaluate(neighbourSolution);
						usefulMovement = movement_duplicate(movementsPossible[j]);
					}
					solution_destroy(neighbourSolution);
				}
			}
		}

		int scoreCurrent = scoreBestNeighbour;

		if(bestNeighbourSolution != NULL)
		{
			solution_destroy(currentSolution);
			currentSolution = solution_duplicate(bestNeighbourSolution);
		}
		solution_destroy(bestNeighbourSolution);
		if(usefulMovement != NULL)
			movement_appendTabou(&tabou, tabouMax, &tabouChanges, usefulMovement);

		if(scoreCurrent > scoreBest)
		{
			scoreBest = scoreCurrent;
			bestSolution = currentSolution;
			i = 0;
		}
		i++;

		//Clean the house
		movement_tabouDestroy(movementsPossible, movementsCount);
	}

	//Clean the house
	movement_tabouDestroy(tabou, MMIN(tabouMax, tabouChanges));

	ftime(&timeEnd);
	bestSolution->solveTime = solution_getTimeDiff(timeStart, timeEnd);

	return bestSolution;
}

Movement ** metaheuristicTabou_getMovements(Solution * solution, int * movementCount)
{
	Movement ** movements = NULL;
	int pos = 0;

	switch (solution->type)
	{
	case DIRECT:

		for (int i = 0; i < solution->instance->itemsCount; i++)
			for (int j = 0; j < solution->instance->itemsCount; j++)
			{
				pos++;
				Movement * movement;
				RREALLOC(movements, Movement *, pos, "metaheuristicTabou_getMovements");
				MMALLOC(movement, Movement, 1, "metaheuristicTabou_getMovements");
				movement->a = i;
				movement->b = j;
				movements[pos - 1] = movement;
			}
		*movementCount = pos;
		break;

	case INDIRECT:

		for(int i = 0; i < solution->instance->itemsCount; i++)
			for(int j = i + 1; j < solution->instance->itemsCount; j++)
			{
				pos++;
				Movement * movement;
				RREALLOC(movements, Movement *, pos, "metaheuristicTabou_getMovements");
				MMALLOC(movement, Movement, 1, "metaheuristicTabou_getMovements");
				movement->a = solutionIndirect_getItemIndex(solution->solutions.indirect, i);
				movement->b = solutionIndirect_getItemIndex(solution->solutions.indirect, j);
				movements[pos - 1] = movement;
			}
		*movementCount = pos;
		break;
	}

	return movements;
}

Solution * metaheuristicTabou_getNeighbourFromMovement(Solution * solution, Movement * movement)
{
	Solution * newSolution = solution_duplicate(solution);
	movement_applyMovement(newSolution, movement);
	return newSolution;
}

int metaheuristicTabou_isTabou(Movement ** tabou, int max, int tabouChanges, Movement * movement)
{
	if(tabou == NULL)
		return false;
	for(int i = 0; i < MMIN(max, tabouChanges); i++)
		if(movement_equals(tabou[i], movement))
			return true;
	return false;
}

void movement_appendTabou(Movement *** tabouPtr, int max, int * tabouChanges, Movement * movement)
{
	Movement ** tabou = *tabouPtr;
	if(*tabouChanges < max)
	{
		RREALLOC(tabou, Movement *, (*tabouChanges) + 1, "movement_appendTabou");
	}
	else
		free(tabou[(*tabouChanges) % max]);

	tabou[(*tabouChanges) % max] = movement;
	(*tabouChanges)++;

	*tabouPtr = tabou;
}

void movement_applyMovement(Solution * solution, Movement * movement)
{
	switch (solution->type)
	{
	case DIRECT:
		if(solution->solutions.direct->itemsTaken[movement->a] == 0)
			solution->solutions.direct->itemsTaken[movement->a] = 1;
		else
			solution->solutions.direct->itemsTaken[movement->a] = 0;
		if(solution->solutions.direct->itemsTaken[movement->b] == 1)
			solution->solutions.direct->itemsTaken[movement->b] = 0;
		else
			solution->solutions.direct->itemsTaken[movement->b] = 0;

		break;

	case INDIRECT:

		for(int i = 0; i < solution->instance->itemsCount; i++)
		{
			if(solution->solutions.indirect->itemsOrder[i] == movement->a)
				solution->solutions.indirect->itemsOrder[i] = movement->b;
			else if(solution->solutions.indirect->itemsOrder[i] == movement->b)
				solution->solutions.indirect->itemsOrder[i] = movement->a;
		}
		solutionIndirect_decode(solution->solutions.indirect);
		break;
	}


}

void movement_tabouDestroy(Movement ** tabou, int tabouCount)
{
	for(int i = 0; i < tabouCount; i++)
		free(tabou[i]);
	free(tabou);
}

Movement * movement_duplicate(Movement * movement)
{
	Movement * newMovement;
	MMALLOC(newMovement, Movement, 1, "movement_duplicate");

	newMovement->a = movement->a;
	newMovement->b = movement->b;

	return newMovement;
}
