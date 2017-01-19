#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "headers/solutionIndirect.h"
#include "headers/solutionDirect.h"
#include "headers/solution.h"
#include "headers/utils.h"
#include "headers/metaheuristicKaguya.h"

Solution * metaheuristicKaguya_search(Instance * instance, SolutionType solutionType)
{
    Clan * clan = clan_createAncestor(instance, solutionType);

    while(clan->size > 0)
    {
        clan_generation(clan);
        clan_sacrament(clan);
        clan_crowning(clan);
    }

    return clan_extinction(clan);
}

Clan * clan_createAncestor(Instance * instance, SolutionType solutionType)
{
    Clan * clan;
    MMALLOC(clan, Clan, 1, "clan_createAncestor");

    clan->type = solutionType;
    clan->size = 1;
    MMALLOC(clan->people, Solution*, clan->size, "clan_createAncestor");
    clan->people[0] = solution_full(instance, clan->type);

    if(solution_doable(clan->people[0]))
    {
        MMALLOC(clan->heirs, Solution*, clan->size, "clan_createAncestor");
        clan->heirs[0] = solution_duplicate(clan->people[0]);
        clan->descendants = 1;
    }
    else
    {
        clan->heirs = NULL;
        clan->descendants = 0;
    }

    return clan;
}

void clan_generation(Clan * clan)
{
    Solution ** children = NULL;
    int childrenNumber = 0;

    for(int i = 0; i < clan->size; i++)
    {
        switch(clan->type)
        {
        case DIRECT:
            for(int j = 0; j < clan->people[i]->instance->itemsCount; j++)
            {
                if(solutionDirect_isItemTaken(clan->people[i]->solutions.direct, j))
                {
                    Solution * solution = solution_duplicate(clan->people[i]);
                    solution->solutions.direct->itemsTaken[j] = 0;
                    childrenNumber++;
                    RREALLOC(children, Solution *, childrenNumber, "clan_generation");
                    children[childrenNumber - 1] = solution;
                }
            }
            break;
        case INDIRECT:
            break;
        }
    }
    clan_replaceGeneration(clan, children, childrenNumber);
}

void clan_replaceGeneration(Clan * clan, Solution ** children, int childrenNumber)
{
    for(int i = 0; i < clan->size; i++)
        solution_destroy(clan->people[i]);
    free(clan->people);

    clan->people = children;
    clan->size = childrenNumber;
}

void clan_sacrament(Clan * clan)
{
    for(int i = 0; i < clan->size; i++)
        if(solution_doable(clan->people[i]))
        {
            clan_isolate(clan, i);
            i--;
        }
}

void clan_isolate(Clan * clan, int index)
{
    clan->descendants++;
    RREALLOC(clan->heirs, Solution *, clan->descendants, "clan_isolate");
    clan->heirs[clan->descendants - 1] = clan->people[index];

    clan->size--;
    if(clan->size == 0)
        clan->people = NULL;
    else
    {
        clan->people[index] = clan->people[clan->size];
        RREALLOC(clan->people, Solution *, clan->size, "clan_isolate");
    }
}

void clan_crowning(Clan * clan)
{
    for(int i = 0; i < clan->descendants; i++)
    {
        if(solution_evaluate(clan->leader) < solution_evaluate(clan->heirs[i]))
        {
            solution_destroy(clan->leader);
            clan->leader = solution_duplicate(clan->heirs[i]);
        }
        solution_destroy(clan->heirs[i]);
    }
    free(clan->heirs);
    clan->descendants = 0;
}

Solution * clan_extinction(Clan * clan)
{
    for(int i = 0; i < clan->size; i++)
		solution_destroy(clan->people[i]);
	free(clan->people);

    for(int i = 0; i < clan->descendants; i++)
		solution_destroy(clan->heirs[i]);
	free(clan->heirs);

    Solution * last = solution_duplicate(clan->leader);
    solution_destroy(clan->leader);
    free(clan);

    return last;
}
