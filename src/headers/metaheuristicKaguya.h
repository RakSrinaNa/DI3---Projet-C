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

/**
 *
 * @param instance
 * @param solutionType
 * @return
 */
Solution * metaheuristicKaguya_search(Instance * instance, SolutionType solutionType);

/**
 *
 * @param instance
 * @param solutionType
 * @return
 */
Clan * clan_create(Instance * instance, SolutionType solutionType);

/**
 *
 * @param clan
 * @param clanMember
 */
void clan_append(Clan * clan, ClanMember * clanMember);

/**
 *
 * @param clan
 * @param index
 */
void clan_remove(Clan * clan, int index);

/**
 *
 * @return
 */
ClanMember * clanMember_ancestor();

/**
 *
 * @param clanMember
 */
void clanMember_destroy(ClanMember * clanMember);

/**
 *
 * @param clanMember
 * @param index
 * @return
 */
ClanMember * clanMember_generation(ClanMember * clanMember, int index);

/**
 *
 * @param clanMember
 * @return
 */
ClanMember * clanMember_duplicate(ClanMember * clanMember);

/**
 *
 * @param clan
 * @param index
 * @return
 */
int clanMember_doable(Clan * clan, int index);

/**
 *
 * @param clan
 * @param index
 * @return
 */
Solution * clanMember_toSolution(Clan * clan, int index);

/**
 *
 * @param clan
 * @param index
 * @return
 */
int clanMember_evaluate(Clan * clan, int index);

/**
 *
 * @param clan
 */
void clan_generation(Clan * clan);

/**
 *
 * @param clan
 * @param descendants
 */
void clan_dispertion(Clan * clan, Clan * descendants);

/**
 *
 * @param clan
 * @return
 */
Solution * clan_extinction(Clan * clan);

#endif
