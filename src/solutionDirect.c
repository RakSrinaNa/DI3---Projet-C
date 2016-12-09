#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "object.h"


SolutionDirect *  solutionDirectCreate(Instance * instance){
    SolutionDirect * solution = (SolutionDirect *)malloc(sizeof(SolutionDirect));
    solution->itemsTaken = int[instance->objectsNumber];
    for (int i = 0; i < instance->objectsNumber; i++)
        solution->itemsTaken[i] = 0;

    solution->evaluate = solutionDirectEvaluate;
    solution->doable = solutionDirectDoable;
    solution->print = solutionDirectPrint;
    solution->saveToFile = solutionDirectSaveToFile;

    return solution;
}

void solutionDirectDestroy(SolutionDirect * solution){
    free(solution);
}

int solutionDirectEvaluate(Instance * instance, int * items){
    int totalValue = 0;

    for (int i = 0; i < instance->objectsNumber; i++)
        if (items[i])
            totalValue += instanceGetObjectAt(instance, i)->value;

    return totalValue;
}

int solutionDirectDoable(Instance * instance, int * items){
    int totalWeights[intsance->dimensionsNumber] = {0};

    // Count the total weight for each dimension in this solution
    for (int i = 0; i < instance->objectsNumber; i++)
        for (int j = 0; j < instance->dimensionsNumber; j++)
            totalWeights[j] += instanceGetObjectAt(instance, i)->weights[j];

    // Verifies that each dimension can contain the total weight associated
    for (int i = 0; i < instance->dimensionsNumber; i++)
        if (totalWeights[i] > instance->maxWeights[i])
            return 0;

    return 1;
}

void solutionDirectPrint(Instance * instance, int * items){

    printf("Total value in the bag : %d\n", solutionDirectEvaluate(instance, items));
    printf("Objects in the bag : ");
    for (int i = 0; i < instance->objectsNumber; i++)
        if(items[i])
            printf("%d\t", i);
    printf("\n");

}

void solutionDirectSaveToFile(char * fileName, Instance * instance, int * items){
    FILE * file = fopen(fileName, "w+");

    fprintf(file, "%d\n", solutionDirectEvaluate(instance, items));
    for (int i = 0; i < instance->objectsNumber; i++)
        fprintf(file, "%d\t\t", items[i]);

    fclose(file);
}
