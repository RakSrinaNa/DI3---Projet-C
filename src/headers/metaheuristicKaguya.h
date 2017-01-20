#ifndef METAHEURISTICKAGUYA
#define METAHEURISTICKAGUYA

#include "solution.h"

typedef struct
{
	int * DNA;
	int dilution;
} ClanMember;

typedef struct
{
	Instance * instance;
	SolutionType type;

	ClanMember ** people;
	int size;
} Clan;


//TODO

Solution * metaheuristicKaguya_search(Instance * instance, SolutionType solutionType);

Clan * clan_create(Instance * instance, SolutionType solutionType);

void clan_append(Clan * clan, ClanMember * clanMember);

void clan_remove(Clan * clan, int index);

ClanMember * clanMember_ancestor();

void clanMember_destroy(ClanMember * clanMember);

ClanMember * clanMember_generation(ClanMember * clanMember, int index);

ClanMember * clanMember_duplicate(ClanMember * clanMember);

int clanMember_doable(Clan * clan, int index);

Solution * clanMember_toSolution(Clan * clan, int index);

int clanMember_evaluate(Clan * clan, int index);

void clan_generation(Clan * clan);

void clan_dispertion(Clan * clan, Clan * descendants);

Solution * clan_extinction(Clan * clan);


#endif
