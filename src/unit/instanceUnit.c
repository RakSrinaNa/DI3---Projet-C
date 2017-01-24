#include <stdlib.h>
#include <stdio.h>

#include "headers/unit.h"
#include "headers/instanceUnit.h"
#include "../headers/instance.h"
#include "../headers/utils.h"

void instanceTests()
{
	int * weights = (int *) malloc(3 * sizeof(int));
	if(weights == NULL)
		exit(10);
	weights[0] = 1;
	weights[1] = 2;
	weights[2] = 3;
	
	Instance * instance;
	MMALLOC(instance, Instance, 1, NULL);
	instance_initialize(instance, 0, 0);
	if(instance->items != NULL || instance->maxWeights != NULL)
		unit_error("ASSERT INSTANCE 2");
	if(instance_getItem(instance, 2) != NULL)
		unit_error("ASSERT INSTANCE 3");
	instance_initialize(instance, 3, 3);
	instance_setMaxWeights(instance, weights);
	if(instance->items == NULL || instance_item_getValue(instance, 2) != 0)
		unit_error("ASSERT INSTANCE 4");
	if(instance_item_getValue(instance, 5) != -1)
		unit_error("ASSERT INSTANCE 5");
	if(instance_getItem(instance, 3) != NULL)
		unit_error("ASSERT INSTANCE 6");
	if(instance_getMaxWeight(instance, 0) != 1 || instance_getMaxWeight(instance, 2) != 3)
		unit_error("ASSERT INSTANCE 7");
	item_setWeight(instance_getItem(instance, 0), 2, 2);
	if(instance_item_getWeight(instance, 0, 2) != 2)
		unit_error("ASSERT INSTANCE 8");
	instance_destroy(instance);
}
