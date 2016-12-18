#include <stdlib.h>
#include "unit.h"
#include "bagUnit.h"
#include "bag.h"
#include "parser.h"

void bagTests()
{
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag.txt");
	Bag * bag = bag_create(instance);
	
	if(bag->itemsCount != 0)
		unit_error("ASSERT BAG 1");
	if(bag_getWeight(bag, 0) != 0 || bag_getWeight(bag, 1) != 0)
		unit_error("ASSERT BAG 2");
	if(bag_canContain(instance, bag, 2) != 0 || bag_canContain(instance, bag, 5) != 0 || bag_canContain(instance, bag, 4) != 0)
		unit_error("ASSERT BAG 3");
	if(bag_canContain(instance, bag, 0) != 1 || bag_canContain(instance, bag, 12) != 1)
		unit_error("ASSERT BAG 4");
	bag_addWeight(bag, 1, 100);
	if(bag_getWeight(bag, 1) != 100)
		unit_error("ASSERT BAG 5");
	bag_addWeight(bag, 1, -100);
	if(bag_getWeight(bag, 1) != 0)
		unit_error("ASSERT BAG 6");
	bag_appendItem(instance, bag, 12);
	if(bag->itemsCount != 1 || bag_getItemIndex(bag, 0) != 12)
		unit_error("ASSERT BAG 7");
	if(bag_getWeight(bag, 0) != 1 || bag_getWeight(bag, 1) != 6)
		unit_error("ASSERT BAG 8");
	bag_appendItem(instance, bag, 1);
	if(bag->itemsCount != 2 || bag_getItemIndex(bag, 1) != 1)
		unit_error("ASSERT BAG 9");
	if(bag_getWeight(bag, 0) != 5 || bag_getWeight(bag, 1) != 94)
		unit_error("ASSERT BAG 10");
	
	char * filename = "testBag.txt";
	FILE * file;
	if((file = fopen(filename, "w+")) == NULL)
	{
		perror("ERROR FOPEN BAG UNIT");
		exit(EXIT_FAILURE);
	}
	bag_saveItems(bag, file);
	fseek(file, 0, SEEK_SET);
	int * bagItems = parser_lineToIntArray(parser_readLine(file), bag->itemsCount);
	fclose(file);
	if(remove(filename) != 0)
		perror("ERROR REMOVE BAG UNIT");
	for(int i = 0; i < bag->itemsCount; i++)
		if(bagItems[i] != bag_getItemIndex(bag, i))
			unit_error("ASSERT BAG 11");
	free(bagItems);
	bag_destroy(bag);
	instance_destroy(instance);
	free(instance);
}
