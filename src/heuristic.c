#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>

#include "instance.h"
#include "solutionDirect.h"
#include "scheduler.h"
#include "heuristic.h"

Solution * heuristic(Instance * instance, int solutionType, int schedulerType)
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

    Solution * solution;
	if((solution = (Solution *) malloc(sizeof(Solution))) == NULL)
	{
		perror("ERROR MALLOC heuristic");
		exit(EXIT_FAILURE);
	}
	solution->solveTime = heuristic_getTimeDiff(timeStart, timeEnd);
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
    solution->instance = instance;

	return solution;
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

void heuristic_saveSolutionToFile(char * fileName, Solution * solution)
{
	FILE * file;
	if((file = fopen(fileName, "w+")) == NULL)
	{
		perror("ERROR FOPEN heuristic_saveSolutionToFile");
		exit(EXIT_FAILURE);
	}
    fprintf(file, "%d\t%Lf\n", heuristic_evaluate(solution), solution->solveTime);
	fclose(file);
}

long double heuristic_getTimeDiff(struct timeb start, struct timeb end)
{
    return end.time - start.time + (end.millitm - start.millitm) / 1000.0f;
}

int heuristic_evaluate(Solution * solution)
{
	switch(solution->type)
	{
		case DIRECT:
			return solutionDirect_evaluate(solution->instance, solution->solutions.direct->itemsTaken);
		case INDIRECT:
			return solutionIndirect_evaluate(solution->solutions.indirect);
	}
	return -1;
}

int heuristic_doable(Solution * solution)
{
	switch(solution->type)
	{
		case DIRECT:
			return solutionDirect_doable(solution->instance, solution->solutions.direct->itemsTaken);
		case INDIRECT:
			return solutionIndirect_doable(solution->solutions.indirect);
	}
	return -1;
}
