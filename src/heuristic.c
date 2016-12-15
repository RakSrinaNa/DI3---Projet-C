#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "solutionDirect.h"
#include "solutionIndirect.h"
#include "scheduler.h"
#include "heuristic.h"

Solution * heuristic(Instance * instance, int solutionType, int schedulerType)
{
	Bag * bag = bag_create(instance);
	int * list = heuristic_getList(instance, bag, schedulerType);
	int listCount = instance->itemsCount;
	
	while(list != NULL)
	{
		int itemIndex = heuristic_removeFromList(&list, &listCount);
		if(bag_canContain(instance, bag, itemIndex))
		{
			bag_appendItem(instance, bag, itemIndex);
			if(schedulerType == 3 && listCount > 0)
				list = scheduler_ratioCriticDimension(instance, bag_getCriticDimension(instance, bag), list, listCount);
		}
	}
	free(list);
	
	Solution * solution;
	if((solution = (Solution *) malloc(sizeof(Solution))) == NULL)
	{
		perror("ERROR MALLOC heuristic");
		exit(EXIT_FAILURE);
	}
	if(solutionType)
	{
		solution->type = DIRECT;
		solution->solutions.indirect = solutionIndirect_create(instance);
		solution->solutions.indirect->bag = bag;
	}
	else
		solution->type = INDIRECT;
	solution->solutions.direct = bag_toSolutionDirect(instance, bag);
	
	return solution;
}

int * heuristic_getList(Instance * instance, Bag * bag, int schedulerType)
{
	switch(schedulerType)
	{
		case 0:
			return NULL;
		
		case 1:
			return scheduler_itemValue(instance);
		
		case 2:
			return scheduler_ratioAllDimensions(instance);
		
		case 3:
			return scheduler_ratioCriticDimension(instance, bag_getCriticDimension(instance, bag), NULL, instance->dimensionsNumber);
		default:
			break;
	}
	
	perror("ERROR HEURISTIC getList");
	exit(EXIT_FAILURE);
}

int heuristic_removeFromList(int ** list, int * listCount)
{
	int element = (*list)[0];
	
	for(int i = 0; i < (*listCount) - 1; i++)
		(*list)[i] = (*list)[i + 1];
	
	(*listCount)--;
	
	if(*listCount == 0)
		(*list) = NULL;
	else if(((*list) = (int *) realloc(list, (*listCount) * sizeof(int))) == NULL)
	{
		perror("ERROR REALLOC heuristic_removeFromList");
		exit(EXIT_FAILURE);
	}
	
	return element;
}
