#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "instance.h"
#include "solutionDirect.h"
#include "scheduler.h"
#include "heuristic.h"
#include "metaheuristicLocal.h"

Solution * metaheuristicLocal_search(Instance *instance, SolutionType solutionType, int searchOperator)
{
    Solution * currentSolution = heuristic(instance, solutionType, 5);
    Solution * bestSolution = currentSolution;

    int scoreBest = solution_evaluate(bestSolution);
    int scoreCurrent = solution_evaluate(currentSolution);

    int stop = 0;

    int scorePrevious = scoreCurrent;

    while(!stop)
    {
        Solution * bestNeighbourSolution = NULL;
        int scoreBestNeighbour = 0;
        int bestNeighbourIndex = -1;

        int neighboursCount = 0;
        Solution ** allNeighbours = metaheuristicLocal_getNeighbours(currentSolution, searchOperator, &neighboursCount);

        for(int i = 0; i < neighboursCount; i++)
        {
            if(solution_evaluate(allNeighbours[i]) > scoreBestNeighbour)
            {
                bestNeighbourSolution = allNeighbours[i];
                bestNeighbourIndex = i;
                scoreBestNeighbour = solution_evaluate(allNeighbours[i]);
            }
        }

        free(currentSolution);
        for(int i = 0; i < neighboursCount; i++)
            if(i != bestNeighbourIndex)
                free(allNeighbours[i]);
        free(allNeighbours);

        scoreCurrent = scoreBestNeighbour;
        currentSolution = bestNeighbourSolution;

        if(scoreCurrent > scoreBest)
        {
            scoreBest = scoreCurrent;
            bestSolution = currentSolution;
        }
        else
        {
            if(scoreCurrent < scorePrevious)
                stop = 1;
        }

        scorePrevious = scoreCurrent;
    }

    return bestSolution;

}

Solution ** metaheuristicLocal_getNeighbours(Solution *currentSolution, int searchOperator, int *neighboursCount)
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
                    return metaheuristicLocal_swapItem(currentSolution, neighboursCount);

                default:
                    break;
            }
    }

    return NULL;
}

Solution ** metaheuristicLocal_swapItem(Solution *currentSolution, int *neighboursCount)
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
                solution_destroy(neighbourSolution);
        }
    }

    return neighbourSolutions;
}

Solution ** metaheuristicLocal_addItem(Solution *currentSolution, int *neighboursCount)
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
                solution_destroy(neighbourSolution);
        }
    }
    return neighbourSolutions;
}

Solution ** metaheuristicLocal_intervertItem(Solution *currentSolution, int *neighboursCount)
{
    Solution ** neighbourSolutions = NULL;

    for(int i = 0; i < currentSolution->solutions.indirect->instance->itemsCount; i++)
    {
        if(currentSolution->solutions.direct->itemsTaken[i])
        {
            Solution * neighbourSolution = solution_duplicate(currentSolution);
            neighbourSolution->solutions.direct->itemsTaken[i] = 0;

            for(int j = 0; j < currentSolution->solutions.indirect->instance->itemsCount; j++)
            {

                if(currentSolution->solutions.direct->itemsTaken[i] == 0)
                {
                    neighbourSolution->solutions.direct->itemsTaken[i] = 1;

                    if(solution_doable(neighbourSolution))
                    {
                        (*neighboursCount)++;
                        neighbourSolutions = (Solution **)realloc(neighbourSolutions, sizeof(Solution *) * *neighboursCount);
                        neighbourSolutions[*neighboursCount - 1] = neighbourSolution;
                    }
                    else
                       solution_destroy(neighbourSolution);
                }

            }

        }

    }
    return neighbourSolutions;
}
