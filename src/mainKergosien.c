#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "instance.h"
#include "parser.h"
#include "solutionIndirect.h"*
#include "solutionDirect.h"
#include "scheduler.h"
#include "heuristic.h"

void mainKergosien()
{

    Instance * instances = parser_readFile("..\\MKP-Instances\\_mknapcb1_res.txt");

    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //Solution * solution = heuristic(&(instances[i]), 1, j);
            //solutionDirect_saveToFileResultAndTime(char * fileName, instances[i], solution);

        }
    }

    free(instances);

}
