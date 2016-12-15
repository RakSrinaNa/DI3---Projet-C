#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "solutionDirect.h"
#include "solutionIndirect.h"
#include "bag.h"
#include "scheduler"

Solution * heuristic(Instance * instance, int solutionType, int schedulerType)
{
    Bag * bag = bag_create(instance);
    int * list = heuristic_getList(instance, bag, schedulerType);
    int listCount = instance->itemsCount;

    while(list != NULL)
    {
        int itemIndex = heuristic_removeFromList(list, &listCount);
        if(bag_canContain(instance, bag, itemIndex))
        {
            bag_appendItem(instance, bag, itemIndex)
            if(schedulerType == 3 && listCount > 0)
                list = scheduler_ratioCriticDimension(instance, bag_getCriticDimension(instance, bag), list, listCount);
        }
    }

    Solution * solution;
    if(solutionType)
    {
        solution->solutionIndirect = solutionIndirect_create(instance);
        solution->solutionIndirect->bag = bag;
    }
    else
        solution->solutionDirect = bag_toSolutionDirect(instance, bag);

    return solution;

}

int * heuristic_getList(Instance * instance, Bag * bag, int schedulerType)
{
    switch (schedulerType)
    {
    case 0:
        return NULL;

    case 1:
        return scheduler_itemValue(instance);

    case 2:
        return scheduler_ratioAllDimensions(instance);

    case 3:
        int * list = (int *)malloc(sizeof(int) * instance->itemsCount);
        for(int i = 0; i < instance->itemsCount; i++)
            list[i] = i;
        return scheduler_ratioCriticDimension(instance, bag_getCriticDimension(instance, bag), list, instance->dimensionsNumber);
    }

    perror("ERROR HEURISTIC getList");
    exit(EXIT_FAILURE);
}

int heuristic_removeFromList(int * list, int * listCount)
{
    int element = list[0];

    for(int i = 0; i < (*listCount)-1; i++)
        list[i] = list[i+1];

    (*listCount)--;

    if (listCount == 0)
        list = NULL;
    else
        list = (int *)realloc(list, (*listCount) * sizeof(int));

    return element;
}
