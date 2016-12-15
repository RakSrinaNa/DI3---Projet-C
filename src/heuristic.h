#ifndef HEURISTIC
#define HEURISTIC

Solution * heuristic(Instance * instance, int solutionType, int schedulerType);

int * heuristic_getList(Instance * instance, Bag * bag, int schedulerType);

int heuristic_removeFromList(int * list, int * listCount);

#endif
