#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "instance.h"
#include "solutionDirect.h"
#include "scheduler.h"
#include "heuristic.h"

Solution * heuristic(Instance * instance, int solutionType, int schedulerType)
{
	Bag * bag = bag_create(instance);
	int listCount = instance->itemsCount;
	
	struct timeval timeStart, timeEnd;
	gettimeofday(&timeStart, NULL);
	int * list = heuristic_getList(instance, bag, schedulerType);
	int i = 0, j = 0;
	while(list != NULL)
	{
		i++;
		int itemIndex = scheduler_removeFromList(&list, &listCount, 0);
		if(bag_canContain(instance, bag, itemIndex))
		{
			j++;
			bag_appendItem(instance, bag, itemIndex);
			if(list != NULL && schedulerType == 3 && listCount > 0)
			{
				int * listToFree = list;
				list = scheduler_ratioForDimension(instance, bag_getCriticDimension(instance, bag), list, listCount);
				free(listToFree);
			}
		}
	}
	gettimeofday(&timeEnd, NULL);
	
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
			return scheduler_ratioForDimension(instance, bag_getCriticDimension(instance, bag), NULL, instance->itemsCount);
		
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

void heuristic_solutionDestroy(Solution * solution)
{
	switch(solution->type)
	{
		case DIRECT:
			solutionDirect_destroy(solution->solutions.direct);
			break;
		case INDIRECT:
			solutionIndirect_destroy(solution->solutions.indirect);
			break;
	}
	free(solution);
}
