#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "scheduler.h"
#include <time.h>

int * scheduler_random(Instance * instance)
{
	int * list = NULL;
	int listCount = 0;
	int * listTempo;
	int listTempoCount = instance->itemsCount;
	if((listTempo = (int *) malloc(sizeof(int) * instance->itemsCount)) == NULL)
	{
		perror("ERROR MALLOC scheduler_random");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < instance->itemsCount; i++)
		listTempo[i] = i;

    while(listTempo != NULL)
        scheduler_appendToList(&list, &listCount, scheduler_removeFromList(&listTempo, &listTempoCount, rand()%listTempoCount));

    free(listTempo);

    return list;
}

int scheduler_removeFromList(int ** list, int * listCount, int index)
{
	int element = (*list)[index];

	for(int i = index; i < *listCount - 1; i++)
		(*list)[i] = (*list)[i + 1];

	(*listCount)--;

	if(*listCount == 0)
		*list = NULL;
	else if((*list = (int *) realloc(*list, *listCount * sizeof(int))) == NULL)
	{
		perror("ERROR REALLOC heuristic_removeFromList");
		exit(EXIT_FAILURE);
	}

	return element;
}

void scheduler_appendToList(int ** list, int * listCount, int element)
{
	if(*list == NULL)
    {
        if((*list = (int *) malloc(sizeof(int))) == NULL)
        {
            perror("ERROR MALLOC scheduler_itemValue");
            exit(EXIT_FAILURE);
        }
    }
	else if((*list = (int *) realloc(*list, (1 + *listCount) * sizeof(int))) == NULL)
	{
		perror("ERROR REALLOC heuristic_removeFromList");
		exit(EXIT_FAILURE);
	}

	(*list)[*listCount] = element;
	(*listCount)++;
}

int * scheduler_itemValue(Instance * instance)
{
	int * list;
	if((list = (int *) malloc(sizeof(int) * instance->itemsCount)) == NULL)
	{
		perror("ERROR MALLOC scheduler_itemValue");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < instance->itemsCount; i++)
		list[i] = i;

	for(int i = 0; i < instance->itemsCount - 1; i++)
	{
		for(int j = 0; j < instance->itemsCount - 1 - i; j++)
		{
			if(instance_item_getValue(instance, list[j]) < instance_item_getValue(instance, list[j + 1]))
			{
				int temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}

	return list;
}

int * scheduler_ratioAllDimensions(Instance * instance)
{
	int * list;
	if((list = (int *) malloc(sizeof(int) * instance->itemsCount)) == NULL)
	{
		perror("ERROR MALLOC scheduler_ratioAllDimensions");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < instance->itemsCount; i++)
		list[i] = i;

	for(int i = 0; i < instance->itemsCount - 1; i++)
	{
		for(int j = 0; j < instance->itemsCount - 1 - i; j++)
		{
			if(scheduler_getRatioAllDimensions(instance, list[j]) < scheduler_getRatioAllDimensions(instance, list[j + 1]))
			{
				int temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}

	return list;
}

double scheduler_getRatioAllDimensions(Instance * instance, int index)
{
	double totalWeight = 0;
	for(int i = 0; i < instance->dimensionsNumber; i++)
		totalWeight += instance_item_getWeight(instance, index, i);
	if(totalWeight == 0)
		return 9999999;
	return instance_item_getValue(instance, index) / totalWeight;
}

int * scheduler_ratioCriticDimension(Instance * instance, int criticDimension, int * subList, int sizeList)
{
	int * list;
	if((list = (int *) malloc(sizeof(int) * instance->itemsCount)) == NULL)
	{
		perror("ERROR MALLOC scheduler_ratioCriticDimension");
		exit(EXIT_FAILURE);
	}

	if(subList == NULL)
	{
		if((subList = (int *) malloc(sizeof(int) * instance->itemsCount)) == NULL)
		{
			perror("ERROR MALLOC scheduler_ratioCriticDimension");
			exit(EXIT_FAILURE);
		}

		for(int i = 0; i < instance->itemsCount; i++)
			list[i] = i;
	}

	for(int i = 0; i < sizeList; i++)
		list[i] = subList[i];

	for(int i = 0; i < sizeList - 1; i++)
	{
		for(int j = 0; j < sizeList - 1 - i; j++)
		{
			if(scheduler_getRatio(instance, list[j], criticDimension) < scheduler_getRatio(instance, list[j + 1], criticDimension))
			{
				int temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
	free(subList);
	return list;
}

double scheduler_getRatio(Instance * instance, int index, int dim)
{
    int weight = instance_item_getWeight(instance, index, dim);
    if (weight == 0)
        return 999999;
	return (double) (instance_item_getValue(instance, index)) / instance_item_getWeight(instance, index, dim);
}

int * scheduler_ratioAllDimensionsWeighted(Instance * instance)
{
	int * list;
	if((list = (int *) malloc(sizeof(int) * instance->itemsCount)) == NULL)
	{
		perror("ERROR MALLOC scheduler_ratioAllDimensions");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < instance->itemsCount; i++)
		list[i] = i;

	for(int i = 0; i < instance->itemsCount - 1; i++)
	{
		for(int j = 0; j < instance->itemsCount - 1 - i; j++)
		{
			if(scheduler_getRatioAllDimensionsWeighted(instance, list[j]) < scheduler_getRatioAllDimensionsWeighted(instance, list[j + 1]))
			{
				int temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}

	return list;
}

double scheduler_getRatioAllDimensionsWeighted(Instance * instance, int index)
{
    double totalWeight = 0;
	for(int i = 0; i < instance->dimensionsNumber; i++)
		totalWeight += instance_item_getWeight(instance, index, i) / instance_getMaxWeight(instance, index);
	if(totalWeight == 0)
		return 9999999;
	return instance_item_getValue(instance, index) / totalWeight;
}
