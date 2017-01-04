#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "instance.h"
#include "scheduler.h"

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
		scheduler_appendToList(&list, &listCount, scheduler_removeFromList(&listTempo, &listTempoCount, rand() % listTempoCount));

	return list;
}

int scheduler_removeFromList(int ** listPtr, int * listCount, int index)
{
	int * list = *listPtr;
	int element = list[index];

	for(int i = index; i < *listCount - 1; i++)
		list[i] = list[i + 1];

	(*listCount)--;

	if(*listCount == 0)
	{
		free(list);
		*listPtr = NULL;
	}
	else
	{
		if((list = (int *) realloc(list, *listCount * sizeof(int))) == NULL)
		{
			perror("ERROR REALLOC heuristic_removeFromList");
			exit(EXIT_FAILURE);
		}
		*listPtr = list;
	}

	return element;
}

void scheduler_appendToList(int ** list, int * listCount, int element)
{
	(*listCount)++;
	if((*list = (int *) realloc(*list, *listCount * sizeof(int))) == NULL)
	{
		perror("ERROR REALLOC heuristic_removeFromList");
		exit(EXIT_FAILURE);
	}

	(*list)[*listCount - 1] = element;
}

int * scheduler_itemValue(Instance * instance)
{
	int * list;
    double * values;
	if((list = (int *) malloc(sizeof(int) * instance->itemsCount)) == NULL)
	{
		perror("ERROR MALLOC scheduler_itemValue");
		exit(EXIT_FAILURE);
	}
    if((values = (double *) malloc(sizeof(double) * instance->itemsCount)) == NULL)
    {
        perror("ERROR MALLOC scheduler_weNeedToFindAName");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < instance->itemsCount; i++)
    {
        list[i] = i;
        values[i] = instance_item_getValue(instance, list[i]);
    }

    scheduler_sortArray(list, values, instance->itemsCount);
    free(values);
	return list;
}

int * scheduler_ratioAllDimensions(Instance * instance)
{
	int * list;
    double * values;
	if((list = (int *) malloc(sizeof(int) * instance->itemsCount)) == NULL)
	{
		perror("ERROR MALLOC scheduler_ratioAllDimensions");
		exit(EXIT_FAILURE);
	}
    if((values = (double *) malloc(sizeof(double) * instance->itemsCount)) == NULL)
    {
        perror("ERROR MALLOC scheduler_weNeedToFindAName");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < instance->itemsCount; i++)
    {
        list[i] = i;
        values[i] = scheduler_getRatioAllDimensions(instance, list[i]);
    }

    scheduler_sortArray(list, values, instance->itemsCount);
    free(values);
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

int * scheduler_ratioForDimension(Instance * instance, int dimension, int * itemsInList, int sizeList)
{
	int * list;
    double * values;
	if((list = (int *) malloc(sizeof(int) * sizeList)) == NULL)
	{
		perror("ERROR MALLOC scheduler_ratioForDimension");
		exit(EXIT_FAILURE);
	}
    if((values = (double *) malloc(sizeof(double) * sizeList)) == NULL)
    {
        perror("ERROR MALLOC scheduler_weNeedToFindAName");
        exit(EXIT_FAILURE);
    }

	if(itemsInList != NULL)
		for(int i = 0; i < sizeList; i++)
			list[i] = itemsInList[i];
	else
		for(int i = 0; i < sizeList; i++)
			list[i] = i;

    for(int i = 0; i < sizeList; i++)
        values[i] = scheduler_getRatio(instance, list[i], dimension);

    scheduler_sortArray(list, values, sizeList);
    free(values);
	return list;
}

double scheduler_getRatio(Instance * instance, int index, int dim)
{
	int weight = instance_item_getWeight(instance, index, dim);
	if(weight == 0)
		return 999999;
	return (double) (instance_item_getValue(instance, index)) / instance_item_getWeight(instance, index, dim);
}

int * scheduler_ratioAllDimensionsWeighted(Instance * instance)
{
	int * list;
    double * values;
	if((list = (int *) malloc(sizeof(int) * instance->itemsCount)) == NULL)
	{
		perror("ERROR MALLOC scheduler_ratioAllDimensions");
		exit(EXIT_FAILURE);
	}
    if((values = (double *) malloc(sizeof(double) * instance->itemsCount)) == NULL)
    {
        perror("ERROR MALLOC scheduler_weNeedToFindAName");
        exit(EXIT_FAILURE);
    }

	for(int i = 0; i < instance->itemsCount; i++)
    {
		list[i] = i;
        values[i] = scheduler_getRatioAllDimensionsWeighted(instance, list[i]);
    }

    scheduler_sortArray(list, values, instance->itemsCount);
    free(values);
	return list;
}

double scheduler_getRatioAllDimensionsWeighted(Instance * instance, int index)
{
	double totalWeight = 0;
	for(int i = 0; i < instance->dimensionsNumber; i++)
		totalWeight += (double) instance_item_getWeight(instance, index, i) / instance_getMaxWeight(instance, i);
	if(totalWeight == 0)
		return 9999999;
	return instance_item_getValue(instance, index) / totalWeight;
}

int * scheduler_weNeedToFindAName(Instance * instance, Bag * bag, int * itemsInList, int sizeList)
{
	int * list;
	double * values;
    if((list = (int *) malloc(sizeof(int) * sizeList)) == NULL)
    {
        perror("ERROR MALLOC scheduler_weNeedToFindAName");
        exit(EXIT_FAILURE);
    }
    if((values = (double *) malloc(sizeof(double) * sizeList)) == NULL)
    {
        perror("ERROR MALLOC scheduler_weNeedToFindAName");
        exit(EXIT_FAILURE);
    }

	if(itemsInList != NULL)
		for(int i = 0; i < sizeList; i++)
			list[i] = itemsInList[i];
	else
		for(int i = 0; i < sizeList; i++)
			list[i] = i;

    for(int i = 0; i < sizeList; i++)
        values[i] = scheduler_weNeedToFindANameRatio(instance, bag, list[i]);

	scheduler_sortArray(list, values, sizeList);
    free(values);
	return list;
}

double scheduler_weNeedToFindANameRatio(Instance * instance, Bag * bag, int index)
{
	double totalWeight = 0;
	for(int i = 0; i < instance->dimensionsNumber; i++)
    {
        totalWeight += exp(20 * (double) bag_getWeight(bag, i) / instance_getMaxWeight(instance, i)) * instance_item_getWeight(instance, index, i);
    }
	if(totalWeight == 0)
		return scheduler_getRatioAllDimensionsWeighted(instance, index);
	return instance_item_getValue(instance, index) / totalWeight;
}

void scheduler_sortArray(int * indexes, double * values, int sizeList)
{
    for(int i = 0; i < sizeList - 1; i++)
        for(int j = 0; j < sizeList - 1 - i; j++)
            if(values[j] < values[j + 1])
            {
                double temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;

                int temp2 = indexes[j];
                indexes[j] = indexes[j + 1];
                indexes[j + 1] = temp2;
            }
}
