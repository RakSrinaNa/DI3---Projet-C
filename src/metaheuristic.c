#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "instance.h"
#include "solutionDirect.h"
#include "scheduler.h"
#include "heuristic.h"
#include "metaheuristic.h"

Solution * metaheuristic_localSearch(Instance *instance, SolutionType solutionType, int searchOperator)
{
    Solution * currentSolution = heuristic(instance, solutionType, 2);
    Solution * bestSolution = currentSolution;

    int fBest = solution_evaluate(bestSolution);
    int fCurrent = solution_evaluate(currentSolution);

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
            if(solution_evaluate(allNeighbours[i]) > fBestNeighbour)
            {
                bestNeighbourSolution = allNeighbours[i];
                bestNeighbourIndex = i;
                fBestNeighbour = solution_evaluate(allNeighbours[i]);
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
    switch(currentSolution->type) {
        case DIRECT:
            switch (searchOperator) {
                case 0:
                    return NULL;

                default:
                    break;
            }
        default:
            switch (searchOperator) {
                case 0:
                    return metaheuristic_swapItem(currentSolution, neighboursCount);

                default:
                    break;
            }
    }

    return NULL;
}

Solution ** metaheuristic_swapItem(Solution * currentSolution, int * neighboursCount)
{
    Solution ** neighbourSolutions = NULL;

    for(int i = 0; i < currentSolution->solutions.indirect->instance->itemsCount; i++)
    {
        for(int j = i+1; j < currentSolution->solutions.indirect->instance->itemsCount; j++)
        {
            Solution * neighbourSolution = solution_duplicate(currentSolution);

            int tempo = solutionIndirect_getItemIndex(neighbourSolution->solutions.indirect, i);
            neighbourSolution->solutions.indirect->itemsOrder[i] = solutionIndirect_getItemIndex(neighbourSolution->solutions.indirect, j);
            neighbourSolution->solutions.indirect->itemsOrder[j] = tempo;

            solutionIndirect_decode(neighbourSolution->solutions.indirect);
            if(solution_doable(neighbourSolution))
            {
                (*neighboursCount)++;
                neighbourSolutions = (Solution **)realloc(neighbourSolutions, sizeof(Solution *) * *neighboursCount);
                neighbourSolutions[*neighboursCount - 1] = neighbourSolution;
            }
            else
                heuristic_solutionDestroy(neighbourSolution);
        }
    }

    return neighbourSolutions;
}

Solution ** metaheuristic_addItem(Solution * currentSolution, int * neighboursCount)
{
    Solution ** neighbourSolutions = NULL;

    for(int i = 0; i < currentSolution->instance->itemsCount; i++)
    {
        if(currentSolution->solutions.direct->itemsTaken[i] == 0)
        {
            Solution * neighbourSolution = solution_duplicate(currentSolution);

            neighbourSolution->solutions.direct->itemsTaken[i] = 1;

            if(solution_doable(neighbourSolution))
            {
                (*neighboursCount)++;
                neighbourSolutions = (Solution **)realloc(neighbourSolutions, sizeof(Solution *) * *neighboursCount);
                neighbourSolutions[*neighboursCount - 1] = neighbourSolution;
            }
            else
                heuristic_solutionDestroy(neighbourSolution);
        }
    }
    return neighbourSolutions;
}


