#include <stddef.h>
#include <stdlib.h>
#include "metaheuristicTabouUnit.h"
#include "utils.h"
#include "metaheuristicTabou.h"
#include "unit.h"
#include "parser.h"
#include "solution.h"
#include "instance.h"

void metaheuristicTabouTests()
{
	movementTests();
}

void movementTests()
{
	Movement * m1;
	MMALLOC(m1, Movement, 1, NULL);
	m1->a = 9;
	m1->b = 15;
	
	Movement * m2 = movement_duplicate(m1);
	if(movement_equals(m1, m2) != 1)
		unit_error("ASSERT MOVEMENT 1");
	m2->a = 15;
	m2->b = 9;
	if(movement_equals(m1, m2) != 1)
		unit_error("ASSERT MOVEMENT 2");
	free(m1);
	
	int correctOrder[3] = {2, 1, 0};
	int * itemOrder;
	MMALLOC(itemOrder, int, 3, NULL);
	itemOrder[0] = 0;
	itemOrder[1] = 1;
	itemOrder[2] = 2;
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag2.txt");
	Solution * solution;
	MMALLOC(solution, Solution, 1, NULL);
	solution->instance = instance;
	solution->type = INDIRECT;
	solution->solveTime = 0;
	solution->solutions.indirect = solutionIndirect_create(instance);
	solution->solutions.indirect->itemsOrder = itemOrder;
	m2->a = 0;
	m2->b = 2;
	
	movement_applyMovement(solution, m2);
	
	if(!unit_arrayEquals(correctOrder, solution->solutions.indirect->itemsOrder, instance->itemsCount))
		unit_error("ASSERT MOVEMENT 3");
	
	solution_destroy(solution);
	instance_destroy(instance);
	free(m2);
}
