#ifndef BAG
#define BAG

#include "instance.h"

typedef struct
{
    int * items;
    int itemsCount;
    int * weights;
    int * maxWeights;

} Bag;

Bag * bag_create(Instance * instance);

void bag_destroy(Bag * bag);

void bag_appendItem(Instance * instance, Bag * bag, int itemIndex);

int bag_canContain(Instance * instance, Bag * bag, int itemIndex);

int bag_getItem(Bag * bag, int index);

#endif
