#include <stdlib.h>
#include <stdio.h>

#include "itemUnit.h"
#include "item.h"

void itemTests ()
{
    Item * item;
    if((item = (Item *) malloc(sizeof(Item))) == NULL)
    {
        perror("TEST MALLOC ERROR");
        exit(EXIT_FAILURE);
    }
    item_initialize(item, 0);
    if(item->weights != NULL)
    {
        perror("ASSERT ITEM 1");
        exit(EXIT_FAILURE);
    }
	item_initialize(item, 3);
    if(item_getWeight(item, 0) != 0 || item_getWeight(item, 1) != 0 || item_getWeight(item, 2) != 0)
    {
        perror("ASSERT ITEM 2");
        exit(EXIT_FAILURE);
    }
    item_setWeight(item, 1, 13);
    if(item_getWeight(item, 1) != 13)
    {
        perror("ASSERT ITEM 3");
        exit(EXIT_FAILURE);
    }
    item_destroy(item);
    free(item);
}
