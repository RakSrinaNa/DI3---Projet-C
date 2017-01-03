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
Solution ** metaheuristic_getNeightbours(Solution * currentSolution, int searchOperator, int * neightboursCount);

#endif
