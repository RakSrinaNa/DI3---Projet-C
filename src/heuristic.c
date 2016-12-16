#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "instance.h"
#include "solutionDirect.h"
#include "scheduler.h"

Solution * heuristic(Instance * instance, int solutionType, int schedulerType)
{
	Bag * bag = bag_create(instance);
	int listCount = instance->itemsCount;
	
	struct timeval timeStart, timeEnd;
	gettimeofday(&timeStart, NULL);
	int * list = heuristic_getList(instance, bag, schedulerType);
	
	while(list != NULL)
	{
		int itemIndex = scheduler_removeFromList(&list, &listCount, 0);
		if(bag_canContain(instance, bag, itemIndex))
		{
			bag_appendItem(instance, bag, itemIndex);
			if(schedulerType == 3 && listCount > 0)
				list = scheduler_ratioForDimension(instance, bag_getCriticDimension(instance, bag), list, listCount);
		}
	}
	gettimeofday(&timeEnd, NULL);
	free(list);
	
	Solution * solution;
	if((solution = (Solution *) malloc(sizeof(Solution))) == NULL)
	{
		perror("ERROR MALLOC heuristic");
		exit(EXIT_FAILURE);
	}
	solution->solveTime = timeEnd.tv_usec - timeStart.tv_usec;
	if(solutionType)
	{
		solution->type = DIRECT;
		solution->solutions.direct = bag_toSolutionDirect(instance, bag);
		bag_destroy(bag);
	}
	else
	{
		solution->type = INDIRECT;
		solution->solutions.indirect = solutionIndirect_create(instance);
		solution->solutions.indirect->bag = bag;
	}
	
	
	return solution;
}

int * heuristic_getList(Instance * instance, Bag * bag, int schedulerType)
{
	switch(schedulerType)
	{
		case 0:
			return scheduler_random(instance);
		
		case 1:
			return scheduler_itemValue(instance);
		
		case 2:
			return scheduler_ratioAllDimensions(instance);
		
		case 3:
			return scheduler_ratioForDimension(instance, bag_getCriticDimension(instance, bag), NULL, instance->dimensionsNumber);
		
		default:
			break;
	}
	
	perror("ERROR HEURISTIC getList - Worst schedulerType EVER");
	exit(EXIT_FAILURE);
}

void heuristic_saveSolutionToFile(char * fileName, Instance * instance, Solution * solution)
{
	FILE * file;
	if((file = fopen(fileName, "w+")) == NULL)
	{
		perror("ERROR FOPEN heuristic_saveSolutionToFile");
		exit(EXIT_FAILURE);
	}
	switch(solution->type)
	{
		case DIRECT:
			fprintf(file, "%d\t%ld\n", solutionDirect_evaluate(instance, solution->solutions.direct->itemsTaken), solution->solveTime);
			break;
		case INDIRECT:
			fprintf(file, "%d\t%ld\n", solutionIndirect_evaluate(solution->solutions.indirect), solution->solveTime);
			break;
	}
	
	fclose(file);
}
