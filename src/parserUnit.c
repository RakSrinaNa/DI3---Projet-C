#include <stdlib.h>
#include <stdio.h>

#include "parserUnit.h"
#include "parser.h"

void parserTests(void)
{
	parserTestLineToIntArray();
	Instance * instance = parser_readFile("MKP-Instances/theBestBag.txt");
	
	if(instance->dimensionsNumber != 2 || instance->itemsCount != 15)
	{
		perror("ASSERT PARSER 1");
		exit(EXIT_FAILURE);
	}
	if(instance_getItem(instance, 4)->value != 83)
	{
		perror("ASSERT PARSER 2");
		exit(EXIT_FAILURE);
	}
	if(item_getWeight(instance_getItem(instance, 4), 0) != 81 || item_getWeight(instance_getItem(instance, 4), 1) != 70)
	{
		perror("ASSERT PARSER 3");
		exit(EXIT_FAILURE);
	}
	if(instance_getMaxWeight(instance, 0) != 7 || instance_getMaxWeight(instance, 1) != 17)
	{
		perror("ASSERT PARSER 4");
		exit(EXIT_FAILURE);
	}
	instance_destroy(instance);
	free(instance);
}

void parserTestLineToIntArray()
{
	int * values = parser_lineToIntArray(" \t 123 \n 22\t56", 3);
	if(values[0] != 123 || values[1] != 22 || values[2] != 56)
	{
		perror("ASSERT PARSER A1");
		exit(EXIT_FAILURE);
	}
	free(values);
	values = parser_lineToIntArray(" \t 123 \n 22\t56", 4);
	if(values[0] != 123 || values[1] != 22 || values[2] != 56 || values[3] != 0)
	{
		perror("ASSERT PARSER A2");
		exit(EXIT_FAILURE);
	}
	free(values);
	values = parser_lineToIntArray(" \t 123 \n 22\t56", 2);
	if(values[0] != 123 || values[1] != 22)
	{
		perror("ASSERT PARSER A3");
		exit(EXIT_FAILURE);
	}
	free(values);
}
