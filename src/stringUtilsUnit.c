#include <stdlib.h>
#include <stdio.h>

#include "stringUtilsUnit.h"
#include "stringUtils.h"

void stringUtilsTests(void)
{
    int * values = getValuesFromLine(" \t 123 \n 22\t56", 3);
    if(values[0] != 123 || values[1] != 22 || values[2] != 56)
    {
        perror("ASSERT STRINGUTILS 1");
        exit(EXIT_FAILURE);
    }
    free(values);
    values = getValuesFromLine(" \t 123 \n 22\t56", 4);
    if(values[0] != 123 || values[1] != 22 || values[2] != 56 || values[3] != 0)
    {
        perror("ASSERT STRINGUTILS 2");
        exit(EXIT_FAILURE);
    }
    free(values);
    values = getValuesFromLine(" \t 123 \n 22\t56", 2);
    if(values[0] != 123 || values[1] != 22)
    {
        perror("ASSERT STRINGUTILS 3");
        exit(EXIT_FAILURE);
    }
    free(values);
}
