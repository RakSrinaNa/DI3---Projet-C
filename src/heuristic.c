#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>

#include "headers/heuristic.h"
#include "headers/scheduler.h"
#include "headers/utils.h"

Solution * heuristic(Instance * instance, SolutionType solutionType, int schedulerType)
{
	Bag * bag = bag_create(instance);
	int listCount = instance->itemsCount;
	
	struct timeb timeStart, timeEnd;
	ftime(&timeStart);
	int * list = heuristic_getList(instance, bag, schedulerType, NULL, listCount);
	int i = 0, j = 0;
	while(list != NULL)
	{
		i++;
		int itemIndex = scheduler_removeFromList(&list, &listCount, 0);
		if(bag_canContain(instance, bag, itemIndex))
		{
			j++;
			bag_appendItem(instance, bag, itemIndex);
			if(list != NULL && (schedulerType == 3 || schedulerType == 5) && listCount > 0)
			{
				int * listToFree = list;
				list = heuristic_getList(instance, bag, schedulerType, list, listCount);
				free(listToFree);
			}
		}
	}
	ftime(&timeEnd);
	
	Solution * solution = NULL;
	
	switch(solutionType)
	{
		case DIRECT:
			solution_fromDirect(bag_toSolutionDirect(instance, bag));
			bag_destroy(bag);
			break;
		
		case INDIRECT:
			solution_fromIndirect(solutionIndirect_create(instance));
			solution->solutions.indirect->bag = bag;
			break;
		
		default:
			perror("Unknown solutionType heuristic");
			exit(EXIT_FAILURE);
	}
	solution->solveTime = solution_getTimeDiff(timeStart, timeEnd);
	
	return solution;
}

int * heuristic_getList(Instance * instance, Bag * bag, int schedulerType, int * oldList, int listCount)
{
	switch(schedulerType)
	{
		case 0:
			return scheduler_random(instance);
		
		case 1:
			return scheduler_itemValue(instance);
		
		case 2:
			return scheduler_allDimensions(instance);
		
		case 3:
			return scheduler_forDimension(instance, bag_getCriticDimension(instance, bag), oldList, listCount);
		
		case 4:
			return scheduler_allDimensionsWeighted(instance);
		
		case 5:
			return scheduler_exponential(instance, bag, oldList, listCount);
		
		default:
			break;
	}
	
	perror("ERROR HEURISTIC getList - Worst schedulerType EVER");
	exit(EXIT_FAILURE);
}
