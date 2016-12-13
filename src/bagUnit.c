#include <stdlib.h>
#include "bagUnit.h"
#include "bag.h"
#include "parser.h"

void bagTests()
{
	Instance * instance = parser_readFile("MKP-Instances/theBestBag.txt");
	Bag * bag = bag_create(instance);
	
	if(bag->itemsCount != 0)
	{
		perror("ASSERT BAG 1");
		exit(EXIT_FAILURE);
	}
	if(bag_getWeight(bag, 0) != 0 || bag_getWeight(bag, 1) != 0)
	{
		perror("ASSERT BAG 2");
		exit(EXIT_FAILURE);
	}
	if(bag_canContain(instance, bag, 2) != 0 || bag_canContain(instance, bag, 5) != 0 || bag_canContain(instance, bag, 4) != 0)
	{
		perror("ASSERT BAG 3");
		exit(EXIT_FAILURE);
	}
	if(bag_canContain(instance, bag, 0) != 1 || bag_canContain(instance, bag, 12) != 1)
	{
		perror("ASSERT BAG 4");
		exit(EXIT_FAILURE);
	}
	bag_addWeight(bag, 1, 100);
	if(bag_getWeight(bag, 1) != 100)
	{
		perror("ASSERT BAG 5");
		exit(EXIT_FAILURE);
	}
	bag_addWeight(bag, 1, -100);
	if(bag_getWeight(bag, 1) != 0)
	{
		perror("ASSERT BAG 6");
		exit(EXIT_FAILURE);
	}
	bag_appendItem(instance, bag, 12);
	if(bag->itemsCount != 1 || bag_getItemIndex(bag, 0) != 12)
	{
		perror("ASSERT BAG 7");
		exit(EXIT_FAILURE);
	}
	if(bag_getWeight(bag, 0) != 1 || bag_getWeight(bag, 1) != 6)
	{
		perror("ASSERT BAG 8");
		exit(EXIT_FAILURE);
	}
	bag_appendItem(instance, bag, 1);
	if(bag->itemsCount != 2 || bag_getItemIndex(bag, 1) != 1)
	{
		perror("ASSERT BAG 9");
		exit(EXIT_FAILURE);
	}
	if(bag_getWeight(bag, 0) != 5 || bag_getWeight(bag, 1) != 94)
	{
		perror("ASSERT BAG 10");
		exit(EXIT_FAILURE);
	}
	
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
		{
			perror("ASSERT BAG 11");
			exit(EXIT_FAILURE);
		}
	free(bagItems);
	bag_destroy(bag);
	instance_destroy(instance);
	free(instance);
}
