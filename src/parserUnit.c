#include <stdlib.h>
#include <stdio.h>

#include "parserUnit.h"
#include "parser.h"

void parserTests(void)
{
    parserTestGetValuesFromLine();
}

void parserTestGetValuesFromLine()
{
    int * values = getValuesFromLine(" \t 123 \n 22\t56", 3);
    if(values[0] != 123 || values[1] != 22 || values[2] != 56)
    {
        perror("ASSERT PARSER A1");
        exit(EXIT_FAILURE);
    }
    free(values);
    values = getValuesFromLine(" \t 123 \n 22\t56", 4);
    if(values[0] != 123 || values[1] != 22 || values[2] != 56 || values[3] != 0)
    {
        perror("ASSERT PARSER A2");
        exit(EXIT_FAILURE);
    }
    free(values);
    values = getValuesFromLine(" \t 123 \n 22\t56", 2);
    if(values[0] != 123 || values[1] != 22)
    {
        perror("ASSERT PARSER A3");
        exit(EXIT_FAILURE);
    }
    free(values);
}
