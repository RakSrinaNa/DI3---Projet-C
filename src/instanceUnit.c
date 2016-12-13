#include <stdlib.h>
#include <stdio.h>

#include "instanceUnit.h"
#include "instance.h"

void instanceTests()
{
	int * weights = (int *) malloc(3 * sizeof(int));
	if(weights == NULL)
		exit(10);
	weights[0] = 1;
	weights[1] = 2;
	weights[2] = 3;
	
	Instance * instance;
	if((instance = (Instance *) malloc(sizeof(Instance))) == NULL)
	{
		perror("TEST MALLOC ERROR");
		exit(EXIT_FAILURE);
	}
	instance_initialize(instance, 0, 0);
	if(instance->items != NULL || instance->maxWeights != NULL)
	{
		perror("ASSERT INSTANCE 2");
		exit(EXIT_FAILURE);
	}
	if(instance_getItem(instance, 2) != NULL)
	{
		perror("ASSERT INSTANCE 3");
		exit(EXIT_FAILURE);
	}
	instance_initialize(instance, 3, 3);
	instance_setMaxWeights(instance, weights);
	if(instance->items == NULL || instance_item_getValue(instance, 2) != 0)
	{
		perror("ASSERT INSTANCE 4");
		exit(EXIT_FAILURE);
	}
	if(instance_item_getValue(instance, 5) != -1)
	{
		perror("ASSERT INSTANCE 5");
		exit(EXIT_FAILURE);
	}
	if(instance_getItem(instance, 3) != NULL)
	{
		perror("ASSERT INSTANCE 6");
		exit(EXIT_FAILURE);
	}
	if(instance_getMaxWeight(instance, 0) != 1 || instance_getMaxWeight(instance, 2) != 3)
	{
		perror("ASSERT INSTANCE 7");
		exit(EXIT_FAILURE);
	}
	instance_destroy(instance);
	free(instance);
}
