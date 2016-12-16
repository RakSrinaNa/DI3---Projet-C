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
	
	valueList = NULL;
	if(scheduler_getRatio(instance, 0, 0) != 12.5 || scheduler_getRatio(instance, 1, 0) != 20 || scheduler_getRatio(instance, 5, 0) != 58 || scheduler_getRatio(instance, 12, 0) != 86 || scheduler_getRatio(instance, 0, 1) != 1 || scheduler_getRatio(instance, 2, 1) != 3)
	{
		perror("ASSERT ERROR SCHEDULER 5");
		exit(EXIT_FAILURE);
	}
	correctValueList[0] = 12;
	correctValueList[1] = 5;
	correctValueList[2] = 1;
	correctValueList[3] = 6;
	correctValueList[4] = 0;
	correctValueList[5] = 3;
	correctValueList[6] = 7;
	correctValueList[7] = 10;
	correctValueList[8] = 9;
	correctValueList[9] = 11;
	correctValueList[10] = 14;
	correctValueList[11] = 2;
	correctValueList[12] = 8;
	correctValueList[13] = 4;
	correctValueList[14] = 13;
	valueList = scheduler_ratioForDimension(instance, 0, NULL, instance->itemsCount);
	for(int i = 0; i < instance->itemsCount; i++)
		if(correctValueList[i] != valueList[i])
		{
			printf("\n%d\n", i);
			perror("ASSERT ERROR SCHEDULER 6");
			exit(EXIT_FAILURE);
		}
	free(valueList);
	
	correctValueList[0] = 12;
	correctValueList[1] = 6;
	correctValueList[2] = 2;
	correctValueList[3] = 14;
	correctValueList[4] = 3;
	correctValueList[5] = 9;
	correctValueList[6] = 8;
	correctValueList[7] = 10;
	correctValueList[8] = 4;
	correctValueList[9] = 7;
	correctValueList[10] = 0;
	correctValueList[11] = 5;
	correctValueList[12] = 1;
	correctValueList[13] = 11;
	correctValueList[14] = 13;
	valueList = scheduler_ratioForDimension(instance, 1, NULL, instance->itemsCount);
	for(int i = 0; i < instance->itemsCount; i++)
		if(correctValueList[i] != valueList[i])
		{
			perror("ASSERT ERROR SCHEDULER 7");
			exit(EXIT_FAILURE);
		}
	free(valueList);
	
	if(scheduler_getRatioAllDimensionsWeighted(instance, 12) != 344 || scheduler_getRatioAllDimensionsWeighted(instance, 3) != 27.5 || scheduler_getRatioAllDimensionsWeighted(instance, 7) != 21.25)
	{
		perror("ASSERT ERROR SCHEDULER 8");
		exit(EXIT_FAILURE);
	}
	correctValueList[0] = 12;
	correctValueList[1] = 6;
	correctValueList[2] = 5;
	correctValueList[3] = 1;
	correctValueList[4] = 0;
	correctValueList[5] = 3;
	correctValueList[6] = 7;
	correctValueList[7] = 9;
	correctValueList[8] = 10;
	correctValueList[9] = 14;
	correctValueList[10] = 11;
	correctValueList[11] = 2;
	correctValueList[12] = 8;
	correctValueList[13] = 4;
	correctValueList[14] = 13;
	valueList = scheduler_ratioAllDimensionsWeighted(instance);
	for(int i = 0; i < instance->itemsCount; i++)
		if(correctValueList[i] != valueList[i])
		{
			perror("ASSERT ERROR SCHEDULER 9");
			exit(EXIT_FAILURE);
		}
	free(valueList);
	
	instance_destroy(instance);
	free(instance);
}
