#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "instance.h"
#include "scheduler.h"
#include "utils.h"

int * scheduler_random(Instance * instance)
{
	int * list = NULL;
	int listCount = 0;
	int * listTempo;
	int listTempoCount = instance->itemsCount;
	MMALLOC(listTempo, int, instance->itemsCount, "scheduler_random");
	
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
		RREALLOC(list, int, *listCount, "heuristic_removeFromList");
		*listPtr = list;
	}
	
	return element;
}

void scheduler_appendToList(int ** list, int * listCount, int element)
{
	(*listCount)++;
	RREALLOC(*list, int, *listCount, "scheduler_removeFromList");
	(*list)[*listCount - 1] = element;
}

int * scheduler_itemValue(Instance * instance)
{
	int * list;
	double * values;
	MMALLOC(list, int, instance->itemsCount, "scheduler_itemValue");
	MMALLOC(values, double, instance->itemsCount, "scheduler_itemValue");
	
	for(int i = 0; i < instance->itemsCount; i++)
	{
		list[i] = i;
		values[i] = instance_item_getValue(instance, list[i]);
	}
	
	scheduler_sortArray(list, values, instance->itemsCount);
	free(values);
	return list;
}

int * scheduler_allDimensions(Instance * instance)
{
	int * list;
	double * values;
	MMALLOC(list, int, instance->itemsCount, "scheduler_allDimensions");
	MMALLOC(values, double, instance->itemsCount, "scheduler_allDimensions");
	
	for(int i = 0; i < instance->itemsCount; i++)
	{
		list[i] = i;
		values[i] = scheduler_allDimensions_score(instance, list[i]);
	}
	
	scheduler_sortArray(list, values, instance->itemsCount);
	free(values);
	return list;
}

double scheduler_allDimensions_score(Instance * instance, int index)
{
	double totalWeight = 0;
	for(int i = 0; i < instance->dimensionsNumber; i++)
		totalWeight += instance_item_getWeight(instance, index, i);
	if(totalWeight == 0)
		return 9999999;
	return instance_item_getValue(instance, index) / totalWeight;
}

int * scheduler_forDimension(Instance * instance, int dimension, int * itemsInList, int sizeList)
{
	int * list;
	double * values;
	MMALLOC(list, int, sizeList, "scheduler_forDimension");
	MMALLOC(values, double, sizeList, "scheduler_forDimensions");
	
	if(itemsInList != NULL)
		for(int i = 0; i < sizeList; i++)
			list[i] = itemsInList[i];
	else
		for(int i = 0; i < sizeList; i++)
			list[i] = i;
	
	for(int i = 0; i < sizeList; i++)
		values[i] = scheduler_forDimension_score(instance, list[i], dimension);
	
	scheduler_sortArray(list, values, sizeList);
	free(values);
	return list;
}

double scheduler_forDimension_score(Instance * instance, int index, int dim)
{
	int weight = instance_item_getWeight(instance, index, dim);
	if(weight == 0)
		return 999999;
	return (double) (instance_item_getValue(instance, index)) / instance_item_getWeight(instance, index, dim);
}

int * scheduler_allDimensionsWeighted(Instance * instance)
{
	int * list;
	double * values;
	MMALLOC(list, int, instance->itemsCount, "scheduler_allDimensionsWeighted");
	MMALLOC(values, double, instance->itemsCount, "scheduler_allDimensionsWeighted");
	
	for(int i = 0; i < instance->itemsCount; i++)
	{
		list[i] = i;
		values[i] = scheduler_allDimensionsWeighted_score(instance, list[i]);
	}
	
	scheduler_sortArray(list, values, instance->itemsCount);
	free(values);
	return list;
}

double scheduler_allDimensionsWeighted_score(Instance * instance, int index)
{
	double totalWeight = 0;
	for(int i = 0; i < instance->dimensionsNumber; i++)
		totalWeight += (double) instance_item_getWeight(instance, index, i) / instance_getMaxWeight(instance, i);
	if(totalWeight == 0)
		return 9999999;
	return instance_item_getValue(instance, index) / totalWeight;
}

int * scheduler_exponential(Instance * instance, Bag * bag, int * itemsInList, int sizeList)
{
	int * list;
	double * values;
	MMALLOC(list, int, sizeList, "scheduler_exponential");
	MMALLOC(values, double, sizeList, "scheduler_exponential");
	
	if(itemsInList != NULL)
		for(int i = 0; i < sizeList; i++)
			list[i] = itemsInList[i];
	else
		for(int i = 0; i < sizeList; i++)
			list[i] = i;
	
	for(int i = 0; i < sizeList; i++)
		values[i] = scheduler_exponential_score(instance, bag, list[i]);
	
	scheduler_sortArray(list, values, sizeList);
	free(values);
	return list;
}

double scheduler_exponential_score(Instance * instance, Bag * bag, int index)
{
	double totalWeight = 0;
	for(int i = 0; i < instance->dimensionsNumber; i++)
	{
		totalWeight += exp(20 * (double) bag_getWeight(bag, i) / instance_getMaxWeight(instance, i)) * instance_item_getWeight(instance, index, i);
	}
	if(totalWeight == 0)
		return scheduler_allDimensionsWeighted_score(instance, index);
	return instance_item_getValue(instance, index) / totalWeight;
}

void scheduler_sortArray(int * indexes, double * scores, int sizeList)
{
	for(int i = 0; i < sizeList - 1; i++)
		for(int j = 0; j < sizeList - 1 - i; j++)
			if(scores[j] < scores[j + 1])
			{
				double temp = scores[j];
				scores[j] = scores[j + 1];
				scores[j + 1] = temp;
				
				int temp2 = indexes[j];
				indexes[j] = indexes[j + 1];
				indexes[j + 1] = temp2;
			}
}
