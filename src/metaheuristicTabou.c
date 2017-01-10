#include <stdbool.h>
#include <stdlib.h>
#include <sys/param.h>

#include "utils.h"
#include "metaheuristicLocal.h"
#include "metaheuristicTabou.h"
#include "solution.h"
#include "instance.h"


int movement_equals(Movement * m1, Movement * m2)
{
	if((m1->a == m2->a && m1->b == m2->b) || (m1->a == m2->b && m1->b == m2->a))
		return 1;
	return 0;
}

Solution * metaheuristicTablou_search(Instance * instance, SolutionType solutionType, int iterationMax, int tabouMax, int aspiration)
{
	Solution * currentSolution = heuristic(instance, solutionType, 5);
	Solution * bestSolution = currentSolution;

	int scoreBest = solution_evaluate(currentSolution);

    Movement ** tabou = NULL;
    int tabouChanges = 0;

	int i = 0;

	while(i < iterationMax)
	{
		int scoreBestNeighbor = 0;
		int movementsCount = 0;

		Movement ** movementsPossible = metaheuristicTabou_getMovements(currentSolution);

		Solution * bestNeighbourSolution = NULL;

		Movement * usefulMovement = NULL;

		for(int j = 0; j < movementsCount; j++)
		{
			if(!metaheuristicTabou_isTabou(tabou, tabouMax, &tabouChanges, movementsPossible[j]) || aspiration)
			{
				Solution * neighbourSolution = metaheuristicTabou_getNeighbourFromMovement(currentSolution, movementsPossible[j]);

				if(!metaheuristicTabou_isTabou(tabou, tabouMax, &tabouChanges, movementsPossible[j]))
				{
					if(solution_evaluate(neighbourSolution) > scoreBestNeighbor)
					{
						bestNeighbourSolution = neighbourSolution;
						scoreBestNeighbor = solution_evaluate(neighbourSolution);
						usefulMovement = movement_duplicate(movementsPossible[j]);
					}
				}
				else
				{
					if(solution_evaluate(neighbourSolution) > scoreBest)
					{
						bestNeighbourSolution = neighbourSolution;
						scoreBestNeighbor = solution_evaluate(neighbourSolution);
						usefulMovement = movement_duplicate(movementsPossible[j]);
					}
				}
			}
		}

		int scoreCurrent = scoreBestNeighbor;

		currentSolution = bestNeighbourSolution;
		movement_appendTabou(tabou, tabouMax, &tabouChanges, usefulMovement);

		if(scoreCurrent > scoreBest)
		{
			scoreBest = scoreCurrent;
			bestSolution = currentSolution;
			i = 0;
		}
		i++;

        //Clean the house
        movement_tabouDestroy(movementsPossible, MIN(tabouMax, tabouChanges)); // TODO TABOU COUNT

	}

    //Clean the house
    movement_tabouDestroy(tabou, 0); // TODO TABOU COUNT

	return bestSolution;
}

Movement ** metaheuristicTabou_getMovements(Solution * solution)
{
	Movement ** movements = NULL;
	int pos = 0;

	for(int i = 0; i < solution->instance->itemsCount; i++)
        for(int j = i+1; j < solution->instance->itemsCount; j++)
        {
            if((movements = (Movement **)realloc(movements, sizeof(Movement *) * pos++)) == NULL)
            {
                perror("ERROR REALLOC metaheuristicTabou_getMovement");
                exit(EXIT_FAILURE);
            }
            Movement * movement;
            if((movement = (Movement *)malloc(sizeof(Movement))) == NULL)
            {
                perror("ERROR MALLOC metaheuristicTabou_getMovement");
                exit(EXIT_FAILURE);
            }
            movement->a = solutionIndirect_getItemIndex(solution->solutions.indirect, i);
            movement->b = solutionIndirect_getItemIndex(solution->solutions.indirect, j);
            movements[pos - 1] = movement;
        }

	return movements;
}

Solution * metaheuristicTabou_getNeighbourFromMovement(Solution * solution, Movement * movement)
{
	Solution * newSolution = solution_duplicate(solution);
    movement_applyMovement(newSolution, movement);
	return newSolution;
}

int metaheuristicTabou_isTabou(Movement ** tabou, int max, int * tabouChanges, Movement * movement)
{
	for(int i = 0; i < MIN(max, *tabouChanges); i++)
		if(movement_equals(tabou[i], movement))
			return true;
	return false;
}

void movement_appendTabou(Movement ** tabou, int max, int * tabouChanges, Movement * movement)
{
	if(*tabouChanges < max)
		if((tabou = (Movement **) realloc(tabou, sizeof(Movement *) * (*tabouChanges + 1))) == NULL)
		{
			perror("ERROR MALLOC metaheuristicTabou");
			exit(EXIT_FAILURE);
		}

	tabou[(*tabouChanges) % max] = movement;
	(*tabouChanges)++;
}

void movement_applyMovement(Solution * solution, Movement * movement)
{
    for(int i = 0; i < solution->instance->itemsCount; i++)
    {
        if(solution->solutions.indirect->itemsOrder[i] == movement->a)
            solution->solutions.indirect->itemsOrder[i] = movement->b;
        else if(solution->solutions.indirect->itemsOrder[i] == movement->b)
            solution->solutions.indirect->itemsOrder[i] = movement->a;
    }
    solutionIndirect_decode(solution->solutions.indirect);
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
    if((newMovement = (Movement *)malloc(sizeof(Movement))) == NULL)
    {
        perror("ERROR MALLOC movement_duplicate");
        exit(EXIT_FAILURE);
    }
    newMovement->a = movement->a;
    newMovement->b = movement->b;

    return newMovement;
}
