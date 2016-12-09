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
    itemInitialize(item, 3);
    if(item->weights[0] != 0 || item->weights[1] != 0 || item->weights[2] != 0)
    {
        perror("ASSERT OBJECT SET WEIGHTS 1");
        exit(EXIT_FAILURE);
    }
    itemSetWeight(item, 1, 13);
    if(item->weights[1] != 13)
    {
        perror("ASSERT OBJECT SET WEIGHTS 2");
        exit(EXIT_FAILURE);
    }
    itemDestroy(item);
    free(item);
}
