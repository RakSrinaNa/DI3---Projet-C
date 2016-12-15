#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "item.h"
#include "solutionDirect.h"
#include "solutionIndirect.h"

int * scheduler_itemValue(Instance * instance)
{
    int * list = (int *)malloc(sizeof(int) * instance->itemsCount);

    for(int i = 0; i < instance->itemsCount; i++)
        list[i] = i;

    for(int i = 0; i < instance->itemsCount-1; i++){
        for (int j = 0; j < instance->itemsCount-1-i; j++){
            if (instance_item_getValue(instance, list[j]) < instance_item_getValue(instance, list[j+1])){
                int t = list[j];
                list[j] = list[j+1];
                list[j+1] = t;
            }
        }
    }

    return list;
}

int * scheduler_ratioAllDimensions(Instance * instance)
{
    int * list = (int *)malloc(sizeof(int) * instance->itemsCount);

    for(int i = 0; i < instance->itemsCount; i++)
        list[i] = i;

    for(int i = 0; i < instance->itemsCount-1; i++){
        for (int j = 0; j < instance->itemsCount-1-i; j++){
            if (scheduler_getRatioAllDimensions(instance, list[j]) < scheduler_getRatioAllDimensions(instance, list[j+1])){
                int t = list[j];
                list[j] = list[j+1];
                list[j+1] = t;
            }
        }
    }

    return list;
}

double scheduler_getRatioAllDimensions(Instance instance, int index)
{
    double totalWeight;
    for(int i = 0; i < instance->dimensionsNumber; i++)
        totalWeight += instance_item_getWeight(instance, index, i);

    return instance_item_getValue(instance, index)/totalWeight;
}
