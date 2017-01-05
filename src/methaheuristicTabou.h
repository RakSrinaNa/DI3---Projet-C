#ifndef METHAHEURISTICTABOU
#define METHAHEURISTICTABOU

#include "instance.h"
#include "heuristic.h"

typedef struct {
    int a;
    int b;
} Movement;

//TODO
int mouvement_equals(Movement * m1, Movement * m2);

//TODO
Solution *metaheuristicTablou_search(Instance *instance, SolutionType solutionType, int iterationMax, int tabouMax, int aspiration);

//TODO
void movement_append(Movement **tabou, int max, Movement *movement);

//TODO
int metaheuristicTabou_isTabou(Movement **movementsList, Movement *movement);

//TODO
Solution *metaheuristicTabou_getNeighbourFromMovement(Solution *solution, Movement *movement);

//TODO
Movement **metaheuristicTabou_getMovements();

#endif
