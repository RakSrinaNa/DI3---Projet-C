#include <stdlib.h>

#include "headers/unit.h"
#include "headers/schedulerUnit.h"
#include "../headers/scheduler.h"
#include "../headers/parser.h"

void schedulerTests()
{
	schedulerSortArrayTests();
	
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag.txt");
	
	int correctValueList[15] = {3, 12, 7, 10, 4, 9, 14, 6, 11, 1, 13, 8, 2, 5, 0};
	int * valueList = scheduler_itemValue(instance);
	if(!unit_arrayEquals(correctValueList, valueList, instance->itemsCount))
		unit_error("ASSERT ERROR SCHEDULER 1");
	
	correctValueList[0] = 3;
	correctValueList[1] = 12;
	correctValueList[2] = 7;
	correctValueList[3] = 4;
	correctValueList[4] = 9;
	correctValueList[5] = 14;
	correctValueList[6] = 6;
	correctValueList[7] = 11;
	correctValueList[8] = 1;
	correctValueList[9] = 13;
	correctValueList[10] = 8;
	correctValueList[11] = 2;
	correctValueList[12] = 5;
	correctValueList[13] = 0;
	correctValueList[14] = 100;
	int length = 15;
	int result = scheduler_removeFromList(&valueList, &length, 3);
	if(length != 14 || result != 10 || !unit_arrayEquals(correctValueList, valueList, length))
		unit_error("ASSERT ERROR SCHEDULER 2");
	scheduler_appendToList(&valueList, &length, 100);
	if(length != 15 || !unit_arrayEquals(correctValueList, valueList, length))
		unit_error("ASSERT ERROR SCHEDULER 3");
	free(valueList);
	
	if(scheduler_allDimensions_score(instance, 5) != 0.90625)
		unit_error("ASSERT ERROR SCHEDULER 4");
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
	valueList = scheduler_allDimensions(instance);
	if(!unit_arrayEquals(correctValueList, valueList, instance->itemsCount))
		unit_error("ASSERT ERROR SCHEDULER 5");
	free(valueList);
	
	valueList = NULL;
	if(scheduler_forDimension_score(instance, 0, 0) != 12.5 || scheduler_forDimension_score(instance, 1, 0) != 20 || scheduler_forDimension_score(instance, 5, 0) != 58 || scheduler_forDimension_score(instance, 12, 0) != 86 || scheduler_forDimension_score(instance, 0, 1) != 1 || scheduler_forDimension_score(instance, 2, 1) != 3)
		unit_error("ASSERT ERROR SCHEDULER 5");
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
	valueList = scheduler_forDimension(instance, 0, NULL, instance->itemsCount);
	
	if(!unit_arrayEquals(correctValueList, valueList, instance->itemsCount))
		unit_error("ASSERT ERROR SCHEDULER 6");
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
	valueList = scheduler_forDimension(instance, 1, NULL, instance->itemsCount);
	if(!unit_arrayEquals(correctValueList, valueList, instance->itemsCount))
		unit_error("ASSERT ERROR SCHEDULER 7");
	free(valueList);
	
	if(scheduler_allDimensionsWeighted_score(instance, 12) != 344 || scheduler_allDimensionsWeighted_score(instance, 3) != 27.5 || scheduler_allDimensionsWeighted_score(instance, 7) != 21.25)
		unit_error("ASSERT ERROR SCHEDULER 8");
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
	valueList = scheduler_allDimensionsWeighted(instance);
	if(!unit_arrayEquals(correctValueList, valueList, instance->itemsCount))
		unit_error("ASSERT ERROR SCHEDULER 9");
	free(valueList);
	
	instance_destroy(instance);
}

void schedulerSortArrayTests()
{
	int correctIndexesList[] = {2, 5, 6, 4, 9, 8, 1, 0, 3, 7};
	int indexes[] = {0, 1, 2, 3, 4, 5 ,6 ,7 ,8, 9};
	double values[] = {1, 1.5, 9, 0.1, 4, 8, 8, 0.1, 2, 3};
	scheduler_sortArray(indexes, values, 10);
	if(!unit_arrayEquals(correctIndexesList, indexes, 10))
		unit_error("ASSERT ERROR SCHEDULER A1");
}
