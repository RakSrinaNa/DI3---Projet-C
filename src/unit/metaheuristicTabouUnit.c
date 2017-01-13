#include <stddef.h>
#include <stdlib.h>
#include "headers/metaheuristicTabouUnit.h"
#include "../headers/utils.h"
#include "../headers/metaheuristicTabou.h"
#include "headers/unit.h"
#include "../headers/parser.h"

void metaheuristicTabouTests()
{
	movementTests();
	movementAppendTabouTests();
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
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag2.txt");
	Solution * solution;
	MMALLOC(solution, Solution, 1, NULL);
	solution->instance = instance;
	solution->type = INDIRECT;
	solution->solveTime = 0;
	solution->solutions.indirect = solutionIndirect_create(instance);
	solution->solutions.indirect->itemsOrder[0] = 0;
	solution->solutions.indirect->itemsOrder[1] = 1;
	solution->solutions.indirect->itemsOrder[2] = 2;
	m2->a = 0;
	m2->b = 2;
	
	movement_applyMovement(solution, m2);
	
	if(!unit_arrayEquals(correctOrder, solution->solutions.indirect->itemsOrder, instance->itemsCount))
		unit_error("ASSERT MOVEMENT 3");
	
	solution_destroy(solution);
	instance_destroy(instance);
	free(m2);
}

void movementAppendTabouTests()
{
	int changes = 0;
	int max = 2;
	Movement ** movements = NULL;
	
	Movement  * m1;
	MMALLOC(m1, Movement, 1, NULL);
	movement_appendTabou(&movements, max, &changes, m1);
	if(changes != 1 || movements[0] != m1)
		unit_error("ASSERT movementAppendTabouTests 1");
	
	Movement  * m2;
	MMALLOC(m2, Movement, 1, NULL);
	movement_appendTabou(&movements, max, &changes, m2);
	if(changes != 2 || movements[0] != m1 || movements[1] != m2)
		unit_error("ASSERT movementAppendTabouTests 2");
	
	Movement  * m3;
	MMALLOC(m3, Movement, 1, NULL);
	movement_appendTabou(&movements, max, &changes, m3);
	if(changes != 3 || movements[0] != m3 || movements[1] != m2)
		unit_error("ASSERT movementAppendTabouTests 3");
	
	
	for(int i = 0; i < MIN(max, changes); i++)
		free(movements[i]);
	free(movements);
}
