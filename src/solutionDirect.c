#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "solutionDirect.h"


SolutionDirect *  solutionDirectCreate(Instance * instance)
{
    SolutionDirect * solution;
    if((solution = (SolutionDirect *)malloc(sizeof(SolutionDirect))) == NULL)
    {
        perror("ERROR MALLOC solutionDirectCreate");
        exit(EXIT_FAILURE);
    }

    if((solution->itemsTaken = (int *)malloc(sizeof(int) * instance->itemsCount)) == NULL)
    {
        perror("ERROR MALLOC solutionDirectCreate");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < instance->itemsCount; i++)
        solution->itemsTaken[i] = 0;

    solution->evaluate = solutionDirectEvaluate;
    solution->doable = solutionDirectDoable;
    solution->print = solutionDirectPrint;
    solution->saveToFile = solutionDirectSaveToFile;

    return solution;
}

void solutionDirectDestroy(SolutionDirect * solution)
{
    free(solution->itemsTaken);
    free(solution);
}

int solutionDirectEvaluate(Instance * instance, int * items)
{
    int totalValue = 0;

    for (int i = 0; i < instance->itemsCount; i++)
        if (items[i])
            totalValue += instance_getItem(instance, i)->value;

    return totalValue;
}

int solutionDirectDoable(Instance * instance, int * items)
{
    int * totalWeights = (int *)malloc(sizeof(int) * instance->dimensionsNumber);
    for (int i = 0; i < instance->dimensionsNumber; i++)
        totalWeights[i] = 0;

    // Count the total weight for each dimension in this solution
    for (int i = 0; i < instance->itemsCount; i++)
        for (int j = 0; j < instance->dimensionsNumber; j++)
            if (items[i])
                totalWeights[j] += instance_getItem(instance, i)->weights[j];

    // Verifies that each dimension can contain the total weight associated
    for (int i = 0; i < instance->dimensionsNumber; i++)
        if (totalWeights[i] > instance->maxWeights[i])
        {
            free(totalWeights);
            return 0;
        }

    free(totalWeights);
    return 1;
}

void solutionDirectPrint(Instance * instance, int * items)
{
    printf("Total value in the bag : %d\n", solutionDirectEvaluate(instance, items));
    printf("Objects in the bag : ");
    for (int i = 0; i < instance->itemsCount; i++)
        if(items[i])
            printf("%d\t", i);
    printf("\n");
}

void solutionDirectSaveToFile(char * fileName, Instance * instance, int * items)
{
    FILE * file;
    if((file = fopen(fileName, "w+")) == NULL)
    {
        perror("ERROR FOPEN solutionDirectSaveToFile");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d\n", solutionDirectEvaluate(instance, items));
    for (int i = 0; i < instance->itemsCount; i++)
        fprintf(file, "%d\t\t", items[i]);

    fclose(file);
}
