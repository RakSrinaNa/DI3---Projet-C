#ifndef SCHEDULER
#define SCHEDULER

#include "instance.h"

int * scheduler_itemValue(Instance * instance);

int * scheduler_ratioAllDimensions(Instance * instance);

double scheduler_getRatioAllDimensions(Instance * instance, int index);

#endif
