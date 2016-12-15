#ifndef SCHEDULER
#define SCHEDULER

#include "instance.h"

int * scheduler_itemValue(Instance * instance);

int * scheduler_ratioAllDimensions(Instance * instance);

double scheduler_getRatioAllDimensions(Instance * instance, int index);

int * scheduler_ratioCriticDimension(Instance * instance, int criticDimension, int * subList, int sizeList);

double scheduler_getRatio(Instance * instance, int index, int dim);

#endif
