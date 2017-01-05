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
        Solution * bestNeighbourSolution = NULL;
        int fBestNeighbour = 0;
        int bestNeighbourIndex = -1;

        int neighboursCount = 0;
        Solution ** allNeighbours = metaheuristic_getNeighbours(currentSolution, searchOperator, &neighboursCount);

        for(int i = 0; i < neighboursCount; i++)
        {
            if(heuristic_evaluate(allNeighbours[i]) > fBestNeighbour)
            {
                bestNeighbourSolution = allNeighbours[i];
                bestNeighbourIndex = i;
                fBestNeighbour = heuristic_evaluate(allNeighbours[i]);
            }
        }

        free(currentSolution);
        for(int i = 0; i < neighboursCount; i++)
            if(i != bestNeighbourIndex)
                free(allNeighbours[i]);
        free(allNeighbours);

        fCurrent = fBestNeighbour;
        currentSolution = bestNeighbourSolution;

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

Solution ** metaheuristic_getNeighbours(Solution * currentSolution, int searchOperator, int * neighboursCount)
{
    if(currentSolution->type == DIRECT)
        switch (searchOperator)
        {
            case 0:
                return NULL;

            default:
                break;
        }
    else
        switch (searchOperator)
        {
            case 0:
                return metaheuristic_swapItem(currentSolution, searchOperator, neighboursCount);

            default:
                break;
        }

    return NULL;
}

Solution ** metaheuristic_swapItem(Solution * currentSolution, int searchOperator, int * neightboursCount)
{
    Solution ** neightbourSolutions = NULL;

    for(int i = 0; i < currentSolution->solutions.indirect->instance->itemsCount; i++)
    {
        for(int j = i+1; j < currentSolution->solutions.indirect->instance->itemsCount; j++)
        {
            Solution * neightbourSolution = heuristic_solutionCopy(currentSolution);

            int tempo = solutionIndirect_getItemIndex(neightbourSolution->solutions.indirect, i);
            neightbourSolution->solutions.indirect->itemsOrder[i] = solutionIndirect_getItemIndex(neightbourSolution->solutions.indirect, j);
            neightbourSolution->solutions.indirect->itemsOrder[j] = tempo;

            solutionIndirect_decode(neightbourSolution->solutions.indirect);
            if(solutionIndirect_doable(neightbourSolution->solutions.indirect))
            {
                (*neightboursCount)++;
                neightbourSolutions = (Solution **)realloc(neightbourSolutions, sizeof(Solution *) * *neightboursCount);
                neightbourSolutions[*neightboursCount - 1] = neightbourSolution;
            }
            else
                heuristic_solutionDestroy(neightbourSolution);
        }
    }

    return neightbourSolutions;
}

