#include <stdlib.h>
#include <stdio.h>

#include "unit.h"
#include "itemUnit.h"
#include "item.h"

void itemTests()
{
	Item * item;
	if((item = (Item *) malloc(sizeof(Item))) == NULL)
	{
		perror("TEST MALLOC ERROR");
		exit(EXIT_FAILURE);
	}
	item_initialize(item, 0);
	if(item->weights != NULL)
		unit_error("ASSERT ITEM 1");
	item_initialize(item, 3);
	if(item_getWeight(item, 0) != 0 || item_getWeight(item, 1) != 0 || item_getWeight(item, 2) != 0)
		unit_error("ASSERT ITEM 2");
	item_setWeight(item, 1, 13);
	if(item_getWeight(item, 1) != 13)
		unit_error("ASSERT ITEM 3");
	item_destroy(item);
	free(item);
}
