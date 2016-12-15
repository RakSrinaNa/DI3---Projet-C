#include <stdlib.h>
#include "scheduler.h"
#include "parser.h"

void schedulerTests()
{
	Instance * instance = parser_readFile("MKP-Instances/theBestBag.txt");
	
	int correctValueList[15] = {3, 12, 7, 10, 4, 9, 14, 6, 11, 1, 13, 8, 2, 5, 0};
	int * valueList = scheduler_itemValue(instance);
	for(int i = 0; i < instance->itemsCount; i++)
		if(correctValueList[i] != valueList[i])
		{
			free(valueList);
			perror("ASSERT ERROR SCHEDULER 1");
			exit(EXIT_FAILURE);
		}
	free(valueList);
	
	instance_destroy(instance);
	free(instance);
}
