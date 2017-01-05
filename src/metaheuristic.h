#ifndef METAHEURISTIC
#define METAHEURISTIC

#include "instance.h"
#include "solutionDirect.h"
#include "scheduler.h"
#include "heuristic.h"
#include "metaheuristic.h"

//TODO
Solution * metaheuristic_localSearch(Instance *instance, SolutionType solutionType, int operatorSearch);

//TODO
Solution ** metaheuristic_getNeighbours(Solution *currentSolution, int searchOperator, int *neighboursCount);

//TODO
Solution ** metaheuristic_swapItem(Solution * currentSolution, int * neighboursCount);

//TODO
Solution ** metaheuristic_addItem(Solution * currentSolution, int * neighboursCount);

//TODO
Solution ** metaheuristic_intervertItem(Solution * currentSolution, int * neighboursCount);

#endif
