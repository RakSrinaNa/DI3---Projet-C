#include <stdlib.h>
#include "heuristic.h"
#include "unit.h"
#include "parser.h"
#include "scheduler.h"
#include "solution.h"

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

    Solution * solution = heuristic(instance, 0, 0);
    if(solution->type != INDIRECT || solution->instance != instance)
        unit_error("ASSERT HEURISTIC 4");
    heuristic_solutionDestroy(solution);
    solution = heuristic(instance, 1, 0);
    if(solution->type != DIRECT)
        unit_error("ASSERT HEURISTIC 5");
    heuristic_solutionDestroy(solution);

    int correctTaken[15] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0};
    int correctBag[2] = {12, 6};
    solution = heuristic(instance, 0, 1);
    if(solutionIndirect_evaluate(solution->solutions.indirect) != 167 || !unit_arrayEquals(correctBag, solution->solutions.indirect->bag->items, solution->solutions.indirect->bag->itemsCount))
        unit_error("ASSERT HEURISTIC 6");
    heuristic_solutionDestroy(solution);

    solution = heuristic(instance, 1, 1);
    if(solutionDirect_evaluate(instance, solution->solutions.direct->itemsTaken) != 167 || !unit_arrayEquals(correctTaken, solution->solutions.direct->itemsTaken, instance->itemsCount))
        unit_error("ASSERT HEURISTIC 7");
    heuristic_solutionDestroy(solution);

    solution = heuristic(instance, 0, 2);
    if(solutionIndirect_evaluate(solution->solutions.indirect) != 167 || !unit_arrayEquals(correctBag, solution->solutions.indirect->bag->items, solution->solutions.indirect->bag->itemsCount))
        unit_error("ASSERT HEURISTIC 8");
    heuristic_solutionDestroy(solution);

    solution = heuristic(instance, 1, 2);
    if(solutionDirect_evaluate(instance, solution->solutions.direct->itemsTaken) != 167 || !unit_arrayEquals(correctTaken, solution->solutions.direct->itemsTaken, instance->itemsCount))
        unit_error("ASSERT HEURISTIC 9");
    heuristic_solutionDestroy(solution);

    solution = heuristic(instance, 0, 3);
    if(solutionIndirect_evaluate(solution->solutions.indirect) != 167 || !unit_arrayEquals(correctBag, solution->solutions.indirect->bag->items, solution->solutions.indirect->bag->itemsCount))
        unit_error("ASSERT HEURISTIC 10");
    heuristic_solutionDestroy(solution);

    solution = heuristic(instance, 1, 3);
    if(solutionDirect_evaluate(instance, solution->solutions.direct->itemsTaken) != 167 || !unit_arrayEquals(correctTaken, solution->solutions.direct->itemsTaken, instance->itemsCount))
        unit_error("ASSERT HEURISTIC 11");
    heuristic_solutionDestroy(solution);

    instance_destroy(instance);
    free(instance);
}
