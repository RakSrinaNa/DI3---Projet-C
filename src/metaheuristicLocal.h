#ifndef METAHEURISTIC
#define METAHEURISTIC

#include "instance.h"
#include "solutionDirect.h"
#include "scheduler.h"
#include "heuristic.h"
#include "metaheuristicLocal.h"

//TODO
Solution * metaheuristicLocal_search(Instance * instance, SolutionType solutionType, int operatorSearch);

//TODO
Solution ** metaheuristicLocal_getNeighbours(Solution * currentSolution, int searchOperator, int * neighboursCount);

//TODO
Solution ** metaheuristicLocal_swapItem(Solution * currentSolution, int * neighboursCount);

//TODO
Solution ** metaheuristicLocal_addItem(Solution * currentSolution, int * neighboursCount);

//TODO
Solution ** metaheuristicLocal_intervertItem(Solution * currentSolution, int * neighboursCount);

#endif
