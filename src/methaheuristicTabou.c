#include <stdbool.h>
#include "metaheuristicLocal.h"
#include "methaheuristicTabou.h"

#define UNUSED(x) (void)(x)

int mouvement_equals(Movement * m1, Movement * m2)
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

	int i = 0;

	while(i < iterationMax)
	{
		int scoreBestNeighbor = 0;
		int movementsCount = 0;

		Movement ** tabou = NULL;
		int tabouChanges = 0;

		Movement ** movementsPossible = metaheuristicTabou_getMovements();

		Solution * bestNeighbourSolution = NULL;

		Movement * usefulMovement = NULL;

		for(int j = 0; j < movementsCount; j++)
		{
			if(!metaheuristicTabou_isTabou(tabou, tabouMax, &tabouChanges, movementsPossible[j]) || aspiration)
			{
				Solution * neighbourSolution = metaheuristicTabou_getNeighbourFromMovement(currentSolution, movementsPossible[j]);

				if(!metaheuristicTabou_isTabou(tabou, movementsPossible[j]))
				{
					if(solution_evaluate(neighbourSolution) > scoreBestNeighbor)
					{
						bestNeighbourSolution = neighbourSolution;
						scoreBestNeighbor = solution_evaluate(neighbourSolution);
						usefulMovement = movementsPossible[j];
					}
				}
				else
				{
					if(solution_evaluate(neighbourSolution) > scoreBest)
					{
						bestNeighbourSolution = neighbourSolution;
						scoreBestNeighbor = solution_evaluate(neighbourSolution);
						usefulMovement = movementsPossible[j];
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
	}

	return bestSolution;
}

Movement ** metaheuristicTabou_getMovements()
{
	//TODO
	return NULL;
}

Solution * metaheuristicTabou_getNeighbourFromMovement(Solution * solution, Movement * movement)
{
	//TODO
	UNUSED(solution);
	UNUSED(movement);
	return NULL;
}

int metaheuristicTabou_isTabou(Movement ** tabou, int max, int * tabouChanges, Movement * movement)
{
	for(int i = 0; i < min(max, *tabouChanges); i++)
        if(mouvement_equals(tabou[i], movement))
            return true;
	return false;
}

void movement_appendTabou(Movement ** tabou, int max, int * tabouChanges, Movement * movement)
{
    if(*tabouChanges < max)
        if((tabou = (Movement *)realloc(tabou, sizeof(Movement *) * (*tabouChanges + 1))) == NULL)
        {
            perror("ERROR MALLOC metaheuristicTabou");
            exit(EXIT_FAILURE);
        }

    tabou[(*tabouChanges) % max] = movement;
    (*tabouChanges)++;

}
