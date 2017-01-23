#include <stdbool.h>
#include <stdlib.h>

#include "headers/utils.h"
#include "headers/metaheuristicLocal.h"
#include "headers/metaheuristicTabou.h"

int movement_equals(Movement * m1, Movement * m2)
{
	if((m1->a == m2->a && m1->b == m2->b) || (m1->a == m2->b && m1->b == m2->a))
		return 1;
	return 0;
}

Tabou * tabou_create(int tabouMax)
{
	Tabou * tabou;
	MMALLOC(tabou, Tabou, 1, "tabou_create");
	tabou->changes = 0;
	tabou->size = 0;
	tabou->max = tabouMax;
	tabou->movements = NULL;
	return tabou;
}

Solution * metaheuristicTabou_search(Instance * instance, SolutionType solutionType, int iterationMax, int tabouMax, int aspiration)
{
	struct timeb timeStart, timeEnd;
	ftime(&timeStart);
	
	Solution * currentSolution = heuristic_search(instance, solutionType, 5);
	Solution * bestSolution = solution_duplicate(currentSolution);
	
	int scoreBest = solution_evaluate(bestSolution);
	
	Tabou * tabou = tabou_create(tabouMax);
	
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
			if(!tabou_isMovementTabou(tabou, movementsPossible[j]) || aspiration)
			{
				Solution * neighbourSolution = metaheuristicTabou_getNeighbourFromMovement(currentSolution, movementsPossible[j]);
				
				if(!tabou_isMovementTabou(tabou, movementsPossible[j]))
				{
					int tempScore = solution_evaluate(neighbourSolution);
					if(solution_doable(neighbourSolution) && tempScore > scoreBestNeighbour)
					{
						solution_destroy(bestNeighbourSolution);
						free(usefulMovement);
						
						bestNeighbourSolution = solution_duplicate(neighbourSolution);
						scoreBestNeighbour = tempScore;
						usefulMovement = movement_duplicate(movementsPossible[j]);
					}
					solution_destroy(neighbourSolution);
				}
				else
				{
					int tempScore = solution_evaluate(neighbourSolution);
					if(solution_doable(neighbourSolution) && tempScore > scoreBest)
					{
						solution_destroy(bestNeighbourSolution);
						free(usefulMovement);
						
						bestNeighbourSolution = solution_duplicate(neighbourSolution);
						scoreBestNeighbour = tempScore;
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
			tabou_appendMovement(tabou, usefulMovement);
		
		if(scoreCurrent > scoreBest)
		{
			scoreBest = scoreCurrent;
			solution_destroy(bestSolution);
			bestSolution = solution_duplicate(currentSolution);
			
			i = 0;
		}
		i++;
		
		//Clean the house
		for(int k = 0; k < movementsCount; k++)
			free(movementsPossible[k]);
		free(movementsPossible);
	}
	solution_destroy(currentSolution);
	//Clean the house
	tabou_destroy(tabou);
	
	ftime(&timeEnd);
	bestSolution->solveTime = solution_getTimeDiff(timeStart, timeEnd);
	
	return bestSolution;
}

Movement ** metaheuristicTabou_getMovements(Solution * solution, int * movementCount)
{
	Movement ** movements = NULL;
	int pos = 0;
	
	switch(solution->type)
	{
		case DIRECT:
			
			for(int i = 0; i < solution->instance->itemsCount; i++)
				for(int j = 0; j < solution->instance->itemsCount; j++)
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

int tabou_isMovementTabou(Tabou * tabou, Movement * movement)
{
	if(tabou->movements == NULL)
		return false;
	for(int i = 0; i < tabou->size; i++)
		if(movement_equals(tabou->movements[i], movement))
			return true;
	return false;
}

void tabou_appendMovement(Tabou * tabou, Movement * movement)
{
	if(tabou->changes < tabou->max)
	{
		RREALLOC(tabou->movements, Movement *, tabou->changes + 1, "tabou_appendMovement");
		tabou->size = tabou->changes + 1;
	}
	else
		free(tabou->movements[tabou->changes % tabou->size]);
	
	tabou->movements[tabou->changes % tabou->max] = movement;
	tabou->changes++;
}

void movement_applyMovement(Solution * solution, Movement * movement)
{
	int tempo;
	switch(solution->type)
	{
		case DIRECT:
			tempo = solution->solutions.direct->itemsTaken[movement->a];
			solution->solutions.direct->itemsTaken[movement->a] = solution->solutions.direct->itemsTaken[movement->b];
			solution->solutions.direct->itemsTaken[movement->b] = tempo;
			
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

void tabou_destroy(Tabou * tabou)
{
	for(int i = 0; i < tabou->size; i++)
		free(tabou->movements[i]);
	free(tabou->movements);
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
