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
			perror("ASSERT ERROR SCHEDULER 1");
			exit(EXIT_FAILURE);
		}
	int length = 15;
	int result = scheduler_removeFromList(&valueList, &length, 3);
	if(length != 14 || result != 10 || valueList[3] != 4 || valueList[4] != 9 || valueList[13] != 0)
	{
		perror("ASSERT ERROR SCHEDULER 2");
		exit(EXIT_FAILURE);
	}
	scheduler_appendToList(&valueList, &length, 100);
	if(length != 15 || valueList[14] != 100)
	{
		perror("ASSERT ERROR SCHEDULER 3");
		exit(EXIT_FAILURE);
	}
	free(valueList);
	
	if(scheduler_getRatioAllDimensions(instance, 5) != 0.90625)
	{
		perror("ASSERT ERROR SCHEDULER 4");
		exit(EXIT_FAILURE);
	}
	correctValueList[0] = 12;
	correctValueList[1] = 6;
	correctValueList[2] = 3;
	correctValueList[3] = 9;
	correctValueList[4] = 7;
	correctValueList[5] = 0;
	correctValueList[6] = 14;
	correctValueList[7] = 5;
	correctValueList[8] = 2;
	correctValueList[9] = 1;
	correctValueList[10] = 10;
	correctValueList[11] = 8;
	correctValueList[12] = 11;
	correctValueList[13] = 4;
	correctValueList[14] = 13;
	valueList = scheduler_ratioAllDimensions(instance);
	for(int i = 0; i < instance->itemsCount; i++)
		if(correctValueList[i] != valueList[i])
		{
			perror("ASSERT ERROR SCHEDULER 5");
			exit(EXIT_FAILURE);
		}
	free(valueList);
	
	instance_destroy(instance);
	free(instance);
}
