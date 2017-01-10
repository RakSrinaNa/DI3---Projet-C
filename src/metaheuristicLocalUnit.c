#include <stdlib.h>
#include "metaheuristicLocalUnit.h"
#include "metaheuristicLocal.h"
#include "parser.h"
#include "utils.h"
#include "solution.h"
#include "unit.h"

void metaheuristicLocalTests()
{
	metaheuristicLocalInvertItemTests();
	metaheuristicLocalAddItemTests();
}

void metaheuristicLocalInvertItemTests()
{
	int correctResult[2][3] = {{0, 1, 0}, {0, 0, 1}};
	int count = 0;
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag2.txt");
	Solution * solution;
	MMALLOC(solution, Solution, 1, NULL);
	solution->instance = instance;
	solution->type = DIRECT;
	solution->solveTime = 0;
	solution->solutions.direct = solutionDirect_create(instance);
	solution->solutions.direct->itemsTaken[0] = 1;
	solution->solutions.direct->itemsTaken[1] = 0;
	solution->solutions.direct->itemsTaken[2] = 0;
	Solution ** results = metaheuristicLocal_invertItem(solution, &count);
	if(count != 2)
		unit_error("ASSERT metaheuristicLocalInvertItemTests 1");
	for(int i = 0; i < count; i++)
		if(!unit_arrayEquals(correctResult[i], results[i]->solutions.direct->itemsTaken, 2))
			unit_error("ASSERT metaheuristicLocalInvertItemTests 2");
	for(int i = 0; i < count; i++)
		solution_destroy(results[i]);
	free(results);
	solution_destroy(solution);
	free(instance);
}

void metaheuristicLocalAddItemTests()
{
	int correctResult[2][3] = {{1, 1, 0}, {1, 0, 1}};
	int count = 0;
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag2.txt");
	Solution * solution;
	MMALLOC(solution, Solution, 1, NULL);
	solution->instance = instance;
	solution->type = DIRECT;
	solution->solveTime = 0;
	solution->solutions.direct = solutionDirect_create(instance);
	solution->solutions.direct->itemsTaken[0] = 1;
	solution->solutions.direct->itemsTaken[1] = 0;
	solution->solutions.direct->itemsTaken[2] = 0;
	Solution ** results = metaheuristicLocal_addItem(solution, &count);
	if(count != 2)
		unit_error("ASSERT metaheuristicLocalAddItemTests 1");
	for(int i = 0; i < count; i++)
		if(!unit_arrayEquals(correctResult[i], results[i]->solutions.direct->itemsTaken, 2))
			unit_error("ASSERT metaheuristicLocalAddItemTests 2");
	for(int i = 0; i < count; i++)
		solution_destroy(results[i]);
	free(results);
	solution_destroy(solution);
	free(instance);
}
