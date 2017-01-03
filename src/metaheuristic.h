#ifndef METAHEURISTIC
#define METAHEURISTIC

#include "instance.h"
#include "solutionDirect.h"
#include "scheduler.h"
#include "heuristic.h"
#include "metaheuristic.h"

//TODO
Solution * metaheuristic_localSearch(Instance * instance, int solutionType, int operatorSearch);

//TODO
Solution ** metaheuristic_getNeighbours(Solution *currentSolution, int searchOperator, int *neighboursCount);

//TODO
Solution ** swapItem(Solution * currentSolution, int searchOperator, int * neighboursCount);

#endif
