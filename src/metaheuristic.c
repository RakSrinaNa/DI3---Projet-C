#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "instance.h"
#include "solutionDirect.h"
#include "scheduler.h"
#include "heuristic.h"
#include "metaheuristic.h"

Solution * metaheuristic_localSearch(Instance * instance, int solutionType, int searchOperator)
{
    Solution * currentSolution = heuristic(instance, solutionType, 2);
    Solution * bestSolution = currentSolution;

    int fBest = heuristic_evaluate(bestSolution);
    int fCurrent = heuristic_evaluate(currentSolution);

    int stop = 0;

    int fPrec = fCurrent;

    while(!stop)
    {
        Solution * bestNeightbourSolution = NULL;
        int fBestNeightbour = 0;
        int bestNeightbourIndex = -1;

        int neightboursCount = 0;
        Solution ** allNeightbours = metaheuristic_getNeightbours(currentSolution, searchOperator, &neightboursCount);

        for(int i = 0; i < neightboursCount; i++)
        {
            if(heuristic_evaluate(allNeightbours[i]) > fBestNeightbour)
            {
                bestNeightbourSolution = allNeightbours[i];
                bestNeightbourIndex = i;
                fBestNeightbour = heuristic_evaluate(allNeightbours[i]);
            }
        }

        free(currentSolution);
        for(int i = 0; i < neightboursCount; i++)
            if(i != bestNeightbourIndex)
                free(allNeightbours[i]);
        free(allNeightbours);

        fCurrent = fBestNeightbour;
        currentSolution = bestNeightbourSolution;

        if(fCurrent > fBest)
        {
            fBest = fCurrent;
            bestSolution = currentSolution;
        }
        else
        {
            if(fCurrent < fPrec)
                stop = 1;
        }

        fPrec = fCurrent;
    }

    return bestSolution;

}

Solution ** metaheuristic_getNeightbours(Solution * currentSolution, int searchOperator, int * neightboursCount)
{

}

