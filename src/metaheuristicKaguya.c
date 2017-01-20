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
    Clan * clan = clan_create(instance, solutionType);
    Clan * descendants = clan_create(instance, solutionType);

    clan_append(clan, clanMember_ancestor());

    while(clan->size > 0)
    {
        clan_generation(clan);
        clan_dispertion(clan, descendants);
    }

    return clan_extinction(clan);
}

Clan * clan_create(Instance * instance, SolutionType solutionType)
{
    Clan * clan;
    MMALLOC(clan, Clan, 1, "clan_createAncestor");

    clan->type = solutionType;
    clan->instance = instance;

    clan->people = NULL;
    clan->size = 0;

    return clan;
}

void clan_append(Clan * clan, ClanMember * clanMember)
{
    clan->size++;
    RREALLOC(clan->people, ClanMember*, clan->size, "clan_append");
    clan->people[clan->size-1] = clanMember;
}

void clan_remove(Clan * clan, int index)
{
	clanMember_destroy(clan->people[index]);
	clan->size--;
	if(clan->size == 0)
		clan->people = NULL;
	else
	{
		clan->people[index] = clan->people[clan->size];
		RREALLOC(clan->people, ClanMember*, clan->size, "clan_remove");
	}
}

ClanMember * clanMember_ancestor()
{
    ClanMember * ancestor;
    MMALLOC(ancestor, ClanMember, 1, "clanMember_ancestor");
    ancestor->DNA = NULL;
    ancestor->dilution = 0;
    return ancestor;
}

void clanMember_destroy(ClanMember * clanMember)
{
	free(clanMember->DNA);
	free(clanMember);
}

ClanMember * clanMember_generation(ClanMember * clanMember, int index)
{
    ClanMember * heir = clanMember_duplicate(clanMember);
    heir->dilution++;
    heir->DNA[heir->dilution-1] = index;
    return heir;
}

ClanMember * clanMember_duplicate(ClanMember * clanMember)
{
    ClanMember * newMember;
    MMALLOC(newMember, ClanMember, 1, "clanMember_duplicate");
    newMember->dilution = clanMember->dilution;
    newMember->DNA = clanMember->DNA;
    return newMember;
}

int clanMember_doable(Clan * clan, int index)
{
	Solution * solution = clanMember_toSolution(clan, index);
	int result = solution_doable(solution);
	solution_destroy(solution);

	return result;
}

Solution * clanMember_toSolution(Clan * clan, int index)
{
    Solution * solution = NULL;
    switch(clan->type)
    {
	case DIRECT:
		solution = solution_full(clan->instance, clan->type);
		for(int i = 0; i < clan->people[index]->dilution; i++)
		{
            solution->solutions.direct->itemsTaken[clan->people[index]->DNA[i]] = 0;
		}
		break;

	case INDIRECT:
		break;
    }

    return solution;
}

int clanMember_isInDNA(ClanMember * clanMember, int index)
{
	for(int i = 0; i < clanMember->dilution; i++)
		if(index == clanMember->DNA[i])
			return 1;
	return 0;
}

int clanMember_evaluate(Clan * clan, int index)
{
	Solution * solution = clanMember_toSolution(clan, index);
	int score = solution_evaluate(solution);
	solution_destroy(solution);

	return score;
}

void clan_generation(Clan * clan)
{
	int initialSize = clan->size;
    for(int i = 0; i < initialSize; i++)
    {
        switch(clan->type)
        {
        case DIRECT:
			for(int j = 0; j < clan->instance->itemsCount; j++)
			{
				if(!clanMember_isInDNA(clan->people[i], j))
				{
                    ClanMember * heir = clanMember_generation(clan->people[i], j);
                    clan_append(clan, heir);
				}
			}
            break;

        case INDIRECT:
            break;
        }
    }
    for(int j = 0; j < initialSize; j++)
		clan_remove(clan, 0);

}

void clan_dispertion(Clan * clan, Clan * descendants)
{
	for(int i = 0; i < clan->size; i++)
	{
		if(clanMember_doable(clan, i))
		{
			clan_append(descendants, clanMember_duplicate(clan->people[i]));
			clan_remove(clan, i);
			i--;
		}
	}
}

void clan_destroy(Clan * clan)
{
	int initialSize = clan->size;
    for(int i = 0; i < initialSize; i++)
		clan_remove(clan, 0);
	free(clan);
}

Solution * clan_extinction(Clan * clan)
{
	Solution * bestSolution = NULL;
	for(int i = 0; i < clan->size; i++)
	{
		Solution * solution = clanMember_toSolution(clan, i);
		if(solution_evaluate(bestSolution) < solution_evaluate(solution))
		{
            solution_destroy(bestSolution);
            bestSolution = solution;
		}
		else
			solution_destroy(solution);
	}
	clan_destroy(clan);

    return bestSolution;
}
