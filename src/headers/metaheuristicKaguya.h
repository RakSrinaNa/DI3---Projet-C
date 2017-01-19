#ifndef METAHEURISTICKAGUYA
#define METAHEURISTICKAGUYA

#include "solution.h"

typedef struct
{
	Solution ** people;
	int size;
	SolutionType type;
	Solution ** heirs;
	int descendants;
	Solution * leader;
} Clan;

//TODO
Solution * metaheuristicKaguya_search(Instance * instance, SolutionType solutionType);

//TODO
Clan * clan_createAncestor(Instance * instance, SolutionType solutionType);

//TODO
void clan_generation(Clan * clan);

//TODO
void clan_replaceGeneration(Clan * clan, Solution ** children, int childrenNumber);

//TODO
void clan_sacrament(Clan * clan);

//TODO
void clan_isolate(Clan * clan, int index);

//TODO
void clan_crowning(Clan * clan);

//TODO
Solution * clan_extinction(Clan * clan);

#endif
