#include <stdlib.h>
#include "solutionUnit.h"
#include "../solution.h"
#include "../utils.h"
#include "../parser.h"
#include "unit.h"
#include "../instance.h"
#include "../bag.h"

void solutionTests()
{
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag2.txt");
	
	Solution * solution;
	MMALLOC(solution, Solution, 1, NULL);
	solution->type = INDIRECT;
	solution->solveTime = 2.2;
	solution->solutions.indirect = solutionIndirect_create(instance);
	solution->solutions.indirect->itemsOrder[0] = 0;
	solution->solutions.indirect->itemsOrder[1] = 1;
	solution->solutions.indirect->itemsOrder[2] = 2;
	solutionIndirect_decode(solution->solutions.indirect);
	
	if(solutionIndirect_doable(solution->solutions.indirect) != solution_doable(solution))
		unit_error("ASSERT SOLUTION 1");
	if(solutionIndirect_evaluate(solution->solutions.indirect) != solution_evaluate(solution))
		unit_error("ASSERT SOLUTION 2");
	
	Solution * dup = solution_duplicate(solution);
	if(dup == NULL || solution->instance != dup->instance || solution->type != dup->type || solution->solveTime != dup->solveTime)
		unit_error("ASSERT SOLUTION 3");
	if(solution->solutions.indirect->instance != dup->solutions.indirect->instance || !unit_arrayEquals(solution->solutions.indirect->itemsOrder, dup->solutions.indirect->itemsOrder, instance->itemsCount))
		unit_error("ASSERT SOLUTION 4");
	if(solution->solutions.indirect->bag->itemsCount != dup->solutions.indirect->bag->itemsCount || !unit_arrayEquals(solution->solutions.indirect->bag->items, dup->solutions.indirect->bag->items, solution->solutions.indirect->bag->itemsCount) || !unit_arrayEquals(solution->solutions.indirect->bag->weights, dup->solutions.indirect->bag->weights, instance->dimensionsNumber))
		unit_error("ASSERT SOLUTION 5");
	
	solution_destroy(solution);
	solution_destroy(dup);
	instance_destroy(instance);
}
