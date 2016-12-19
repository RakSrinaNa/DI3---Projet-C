#include <stdlib.h>

#include "unit.h"
#include "parserUnit.h"
#include "parser.h"
#include "instance.h"
#include "item.h"

void parserTests(void)
{
	parserTestLineToIntArray();
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag.txt");
	
	if(instance->dimensionsNumber != 2 || instance->itemsCount != 15)
		unit_error("ASSERT PARSER 1");
	if(instance_getItem(instance, 4)->value != 83)
		unit_error("ASSERT PARSER 2");
	if(item_getWeight(instance_getItem(instance, 4), 0) != 81 || item_getWeight(instance_getItem(instance, 4), 1) != 70)
		unit_error("ASSERT PARSER 3");
	if(instance_getMaxWeight(instance, 0) != 7 || instance_getMaxWeight(instance, 1) != 56)
		unit_error("ASSERT PARSER 4");

	Parser * parser = parser_create("MKP-Instances/theBestBag.txt");
	if(parser->instanceCount != 1)
		unit_error("ASSERT PARSER 5");
	Instance * instance1 = parser_getNextInstance(parser);
	if(instance1->itemsCount != instance->itemsCount || instance1->dimensionsNumber != instance->dimensionsNumber || !unit_arrayEquals(instance->maxWeights, instance1->maxWeights, instance->dimensionsNumber))
		unit_error("ASSERT PARSER 6");
	for(int i = 0; i < instance->itemsCount; i++)
	{
		Item * item = instance_getItem(instance, i);
		Item * item1 = instance_getItem(instance1, i);
		if(item->value != item1->value || !unit_arrayEquals(item->weights, item1->weights, instance->dimensionsNumber))
			unit_error("ASSERT PARSER 7");
	}

	instance_destroy(instance);

	if(parser_getNextInstance(parser) != NULL)
		unit_error("ASSERT PARSER 8");

	parser_destroy(parser);
	free(instance);
}

void parserTestLineToIntArray()
{
	int correctValues[4] = {123, 22, 56, 0};
	int * values = parser_lineToIntArray(" \t 123 \n 22\t56", 3);
	if(!unit_arrayEquals(correctValues, values, 3))
		unit_error("ASSERT PARSER A1");
	free(values);
	values = parser_lineToIntArray(" \t 123 \n 22\t56", 4);
	if(!unit_arrayEquals(correctValues, values, 4))
		unit_error("ASSERT PARSER A2");
	free(values);
	values = parser_lineToIntArray(" \t 123 \n 22\t56", 2);
	if(!unit_arrayEquals(correctValues, values, 2))
		unit_error("ASSERT PARSER A3");
	free(values);
}
