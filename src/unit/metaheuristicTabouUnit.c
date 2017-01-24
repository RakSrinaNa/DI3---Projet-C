#include "headers/metaheuristicTabouUnit.h"
#include "../headers/utils.h"
#include "../headers/metaheuristicTabou.h"
#include "headers/unit.h"
#include "../headers/parser.h"

void metaheuristicTabouTests()
{
	movementTests();
	movementTabouTests();
	metaheuristicTabouGetMovementsTest();
	metaheuristicTabouGetMovementsTests();
	metaheuristicTabouSearchTests();
}

void movementTests()
{
	Movement * m1;
	MMALLOC(m1, Movement, 1, NULL);
	m1->a = 9;
	m1->b = 15;
	
	Movement * m2 = movement_duplicate(m1);
	if(movement_equals(m1, m2) != 1)
		unit_error("ASSERT movementTests 1");
	m2->a = 15;
	m2->b = 9;
	if(movement_equals(m1, m2) != 1)
		unit_error("ASSERT movementTests 2");
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
		unit_error("ASSERT movementTests 3");
	
	solution_destroy(solution);
	int correctTaken[] = {0, 0, 1};
	MMALLOC(solution, Solution, 1, NULL);
	solution->instance = instance;
	solution->type = DIRECT;
	solution->solveTime = 0;
	solution->solutions.direct = solutionDirect_create(instance);
	solution->solutions.direct->itemsTaken[0] = 1;
	
	movement_applyMovement(solution, m2);
	if(!unit_arrayEquals(correctTaken, solution->solutions.direct->itemsTaken, instance->itemsCount))
		unit_error("ASSERT movementTests 4");
	
	correctTaken[0] = 1;
	solution->solutions.direct->itemsTaken[0] = 1;
	movement_applyMovement(solution, m2);
	if(!unit_arrayEquals(correctTaken, solution->solutions.direct->itemsTaken, instance->itemsCount))
		unit_error("ASSERT movementTests 5");
	
	correctTaken[0] = 0;
	correctTaken[2] = 0;
	solution->solutions.direct->itemsTaken[0] = 0;
	solution->solutions.direct->itemsTaken[2] = 0;
	movement_applyMovement(solution, m2);
	if(!unit_arrayEquals(correctTaken, solution->solutions.direct->itemsTaken, instance->itemsCount))
		unit_error("ASSERT movementTests 6");
	
	solution_destroy(solution);
	instance_destroy(instance);
	free(m2);
}

void movementTabouTests()
{
	Tabou * tabou = tabou_create(2);
	
	Movement * m1;
	MMALLOC(m1, Movement, 1, NULL);
	m1->a = 4;
	m1->b = 5;
	tabou_appendMovement(tabou, m1);
	if(tabou->size != 1 || tabou->changes != 1 || tabou->movements[0] != m1)
		unit_error("ASSERT movementTabouTests 1");
	
	Movement * m2;
	MMALLOC(m2, Movement, 1, NULL);
	m2->a = 5;
	m2->b = 6;
	tabou_appendMovement(tabou, m2);
	if(tabou->size != 2 || tabou->changes != 2 || tabou->movements[0] != m1 || tabou->movements[1] != m2)
		unit_error("ASSERT movementTabouTests 2");
	
	Movement * m3;
	MMALLOC(m3, Movement, 1, NULL);
	m3->a = 6;
	m3->b = 7;
	tabou_appendMovement(tabou, m3);
	if(tabou->size != 2 || tabou->changes != 3 || tabou->movements[0] != m3 || tabou->movements[1] != m2)
		unit_error("ASSERT movementTabouTests 3");
	
	Movement * m4;
	MMALLOC(m4, Movement, 1, NULL);
	m4->a = 7;
	m4->b = 6;
	
	if(tabou_isMovementTabou(tabou, m4) != 1)
		unit_error("ASSERT movementTabouTests 4");
	
	m4->a = 10;
	if(tabou_isMovementTabou(tabou, m4) != 0)
		unit_error("ASSERT movementTabouTests 4");
	
	free(m4);
	tabou_destroy(tabou);
}

void metaheuristicTabouGetMovementsTest()
{
	int correctOrder[3] = {0, 2, 1};
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
	
	Movement * m1;
	MMALLOC(m1, Movement, 1, NULL);
	m1->a = 1;
	m1->b = 2;
	
	Solution * moved = metaheuristicTabou_getNeighbourFromMovement(solution, m1);
	if(moved == solution || !unit_arrayEquals(correctOrder, moved->solutions.indirect->itemsOrder, instance->itemsCount))
		unit_error("ASSERT metaheuristicTabouGetMovementsTest 1");
	
	free(m1);
	solution_destroy(moved);
	solution_destroy(solution);
	instance_destroy(instance);
}

void metaheuristicTabouGetMovementsTests()
{
	int correctSolutions[3][2] = {{0, 1}, {0, 2}, {1, 2}};
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
	Movement * m1;
	MMALLOC(m1, Movement, 1, NULL);
	
	int count;
	Movement ** movements = metaheuristicTabou_getMovements(solution, &count);
	if(count != 3)
		unit_error("ASSERT metaheuristicTabouGetMovementsTests 1");
	for(int i = 0; i < count; i++)
	{
		m1->a = correctSolutions[i][0];
		m1->b = correctSolutions[i][1];
	}
	
	free(m1);
	for(int i = 0; i < count; i++)
		free(movements[i]);
	free(movements);
	solution_destroy(solution);
	instance_destroy(instance);
}

void metaheuristicTabouSearchTests()
{
	Parser * parser = parser_create("MKP-Instances/_mknapcb1_res.txt");
	Instance * instance = parser_getNextInstance(parser);
	solution_destroy(metaheuristicTabou_search(instance, INDIRECT, 5, 10, 1));
	printf("~");
	solution_destroy(metaheuristicTabou_search(instance, INDIRECT, 5, 10, 0));
	printf("~");
	solution_destroy(metaheuristicTabou_search(instance, DIRECT, 5, 10, 1));
	printf("~");
	solution_destroy(metaheuristicTabou_search(instance, DIRECT, 5, 10, 0));
	printf("~");
	instance_destroy(instance);
	parser_destroy(parser);
}
