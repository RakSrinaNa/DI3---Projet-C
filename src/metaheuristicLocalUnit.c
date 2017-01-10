#include <stdlib.h>
#include "metaheuristicLocalUnit.h"
#include "metaheuristicLocal.h"
#include "parser.h"
#include "utils.h"
#include "solution.h"
#include "unit.h"
#include "instance.h"

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
		if(!unit_arrayEquals(correctResult[i], results[i]->solutions.direct->itemsTaken, solution->instance->itemsCount))
			unit_error("ASSERT metaheuristicLocalInvertItemTests 2");
	for(int i = 0; i < count; i++)
		solution_destroy(results[i]);
	free(results);
	solution_destroy(solution);
	free(instance);
}

void metaheuristicLocalAddItemTests()
{
	int correctResult[3] = {1, 0, 1};
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
	if(count != 1)
		unit_error("ASSERT metaheuristicLocalAddItemTests 1");
	if(!unit_arrayEquals(correctResult, results[0]->solutions.direct->itemsTaken, solution->instance->itemsCount))
		unit_error("ASSERT metaheuristicLocalInvertItemTests 2");
	free(results);
	solution_destroy(solution);
	free(instance);
}

void metaheuristicLocalSwapItemsTests()
{
	int correctResult[3][3] = {{1, 0, 2}, {2, 1, 0}, {0, 2, 1}};
	int * itemOrder;
	MMALLOC(itemOrder, int, 3, NULL);
	itemOrder[0] = 0;
	itemOrder[1] = 1;
	itemOrder[2] = 2;
	int count = 0;
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag2.txt");
	Solution * solution;
	MMALLOC(solution, Solution, 1, NULL);
	solution->instance = instance;
	solution->type = DIRECT;
	solution->solveTime = 0;
	solution->solutions.indirect = solutionIndirect_create(instance);
	solution->solutions.indirect->itemsOrder = itemOrder;
	solutionIndirect_decode(solution->solutions.indirect);
	Solution ** results = metaheuristicLocal_swapItem(solution, &count);
	if(count != 2)
		unit_error("ASSERT metaheuristicLocalSwapItemsTests 1");
	for(int i = 0; i < count; i++)
		if(!unit_arrayEquals(correctResult[i], results[i]->solutions.indirect->itemsOrder, solution->instance->itemsCount))
			unit_error("ASSERT metaheuristicLocalSwapItemsTests 2");
	for(int i = 0; i < count; i++)
		solution_destroy(results[i]);
	free(results);
	solution_destroy(solution);
	free(instance);
}
