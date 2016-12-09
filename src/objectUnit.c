#include <stdlib.h>
#include <stdio.h>

#include "objectUnit.h"
#include "object.h"

void objectTests()
{
    Object * object;
    if((object = (Object *) malloc(sizeof(Object))) == NULL)
    {
        perror("TEST MALLOC ERROR");
        exit(EXIT_FAILURE);
    }
    objectInitialize(object, 3);
    if(object->weights[0] != 0 || object->weights[1] != 0 || object->weights[2] != 0)
    {
        perror("ASSERT OBJECT SET WEIGHTS 1");
        exit(EXIT_FAILURE);
    }
    objectSetWeight(object, 1, 13);
    if(object->weights[1] != 13)
    {
        perror("ASSERT OBJECT SET WEIGHTS 2");
        exit(EXIT_FAILURE);
    }
    objectDestroy(object);
    free(object);
}
