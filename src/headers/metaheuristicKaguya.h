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
 * Starts the Kaguya metaheuristic function depending on the solutionType.
 *
 * @param instance A pointer to the related instance.
 * @param solutionType The type of the solution.
 * @return A pointer to the best solution.
 */
Solution * metaheuristicKaguya_search(Instance * instance, SolutionType solutionType);

/**
 * Create a clan.
 *
 * @param instance A pointer to the related instance.
 * @param solutionType The type of the solution.
 * @return A pointer to the created clan.
 */
Clan * clan_create(Instance * instance, SolutionType solutionType);

/**
 * Append a ClanMember to a clan.
 *
 * @param clan A pointer to the clan.
 * @param clanMember A pointer to the ClanMember to append.
 */
void clan_append(Clan * clan, ClanMember * clanMember);

/**
 * Remove the ClanMember at the given index.
 *
 * @param clan A pointer to the clan.
 * @param index The index of the ClanMember to remove.
 */
void clan_remove(Clan * clan, int index);

/**
 * Create the default ClanMember.
 *
 * @return A pointer to the original ClanMember.
 */
ClanMember * clanMember_ancestor();

/**
 * Destroy and free a ClanMember.
 *
 * @param clanMember A pointer to the ClanMember to destroy.
 */
void clanMember_destroy(ClanMember * clanMember);

/**
 * Create an new ClanMember with a mutation.
 *
 * @param clanMember A pointer to the parent ClanMember.
 * @param index The index of the object to remove from the ClanMember.
 * @return A pointer to the new ClanMember.
 */
ClanMember * clanMember_generation(ClanMember * clanMember, int index);

/**
 * Duplicate a ClanMember on the heap.
 *
 * @param clanMember A pointer to the ClanMember to duplicate.
 * @return A pointer to the duplicated ClanMember.
 */
ClanMember * clanMember_duplicate(ClanMember * clanMember);

/**
 * Tells if a ClanMember is doable.
 *
 * @param clan A pointer to the Clan.
 * @param index The index of the ClanMember to test.
 * @return 1 if doable, 0 else.
 */
int clanMember_doable(Clan * clan, int index);

/**
 * Turn a ClanMember into a solution.
 *
 * @param clan A pointer to the Clan.
 * @param index The index of the ClanMember to transform.
 * @return A pointer to the solution corresponding.
 */
Solution * clanMember_toSolution(Clan * clan, int index);

/**
 * Evaluate a ClanMember.
 *
 * @param clan A pointer to the Clan.
 * @param index The index of the ClanMember to evaluate.
 * @return The score for the ClanMember.
 */
int clanMember_evaluate(Clan * clan, int index);

/**
 * Create a new generation for the clan.
 *
 * @param clan A pointer to the Clan.
 */
void clan_generation(Clan * clan);

/**
 * If some ClanMember of the Clan are doable, they go to the clan named descendants.
 *
 * @param clan A pointer to the Clan to verify.
 * @param descendants A pointer to the clan of doable ClanMembers.
 */
void clan_dispertion(Clan * clan, Clan * descendants);

/**
 * Destroy a Clan and all its ClanMembers.
 *
 * @param clan A pointer to the CLan to destroy.
 * @return A pointer to the solution corresponding to the best ClanMember.
 */
Solution * clan_extinction(Clan * clan);

#endif
