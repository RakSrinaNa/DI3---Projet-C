#include <stdlib.h>
#include "heuristic.h"
#include "unit.h"
#include "parser.h"
#include "scheduler.h"

void heuristicTests()
{
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag.txt");
	Bag * bag = bag_create(instance);
	
	int * correctList = scheduler_itemValue(instance);
	int * list = heuristic_getList(instance, bag, 1, NULL, instance->itemsCount);
	if(!unit_arrayEquals(correctList, list, instance->itemsCount))
		unit_error("ASSERT HEURISTIC 1");
	free(correctList);
	free(list);
	correctList = scheduler_allDimensions(instance);
	list = heuristic_getList(instance, bag, 2, NULL, instance->itemsCount);
	if(!unit_arrayEquals(correctList, list, instance->itemsCount))
		unit_error("ASSERT HEURISTIC 2");
	free(correctList);
	free(list);
	correctList = scheduler_forDimension(instance, bag_getCriticDimension(instance, bag), NULL, instance->itemsCount);
	list = heuristic_getList(instance, bag, 3, NULL, instance->itemsCount);
	if(!unit_arrayEquals(correctList, list, instance->itemsCount))
		unit_error("ASSERT HEURISTIC 3");
	free(correctList);
	free(list);
	
	Solution * solution = heuristic(instance, INDIRECT, 0);
	if(solution->type != INDIRECT || solution->instance != instance)
		unit_error("ASSERT HEURISTIC 4");
	solution_destroy(solution);
	solution = heuristic(instance, DIRECT, 0);
	if(solution->type != DIRECT)
		unit_error("ASSERT HEURISTIC 5");
	solution_destroy(solution);
	
	int correctTaken[15] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0};
	int correctBag[2] = {12, 6};
	solution = heuristic(instance, INDIRECT, 1);
	if(solution_evaluate(solution) != 167 || !unit_arrayEquals(correctBag, solution->solutions.indirect->bag->items, solution->solutions.indirect->bag->itemsCount))
		unit_error("ASSERT HEURISTIC 6");
	solution_destroy(solution);
	
	solution = heuristic(instance, DIRECT, 1);
	if(solution_evaluate(solution) != 167 || !unit_arrayEquals(correctTaken, solution->solutions.direct->itemsTaken, instance->itemsCount))
		unit_error("ASSERT HEURISTIC 7");
	solution_destroy(solution);
	
	solution = heuristic(instance, INDIRECT, 2);
	if(solution_evaluate(solution) != 167 || !unit_arrayEquals(correctBag, solution->solutions.indirect->bag->items, solution->solutions.indirect->bag->itemsCount))
		unit_error("ASSERT HEURISTIC 8");
	solution_destroy(solution);
	
	solution = heuristic(instance, DIRECT, 2);
	if(solution_evaluate(solution) != 167 || !unit_arrayEquals(correctTaken, solution->solutions.direct->itemsTaken, instance->itemsCount))
		unit_error("ASSERT HEURISTIC 9");
	solution_destroy(solution);
	
	solution = heuristic(instance, INDIRECT, 3);
	if(solution_evaluate(solution) != 167 || !unit_arrayEquals(correctBag, solution->solutions.indirect->bag->items, solution->solutions.indirect->bag->itemsCount))
		unit_error("ASSERT HEURISTIC 10");
	solution_destroy(solution);
	
	solution = heuristic(instance, DIRECT, 3);
	if(solution_evaluate(solution) != 167 || !unit_arrayEquals(correctTaken, solution->solutions.direct->itemsTaken, instance->itemsCount))
		unit_error("ASSERT HEURISTIC 11");
	solution_destroy(solution);
	
	instance_destroy(instance);
	free(instance);
}
