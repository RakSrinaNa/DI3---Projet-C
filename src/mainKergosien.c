#include <stdlib.h>

#include "instance.h"
#include "parser.h"
#include "solutionIndirect.h"
#include "solutionDirect.h"
#include "scheduler.h"
#include "heuristic.h"
#include "mainKergosien.h"

void mainKergosien()
{
    Instance * instances = parser_readFile("F:\\Polytech\\ProjetTutore\\DI3---Projet2\\MKP-Instances");

    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            Solution * solution = heuristic(&(instances[i]), 1, j);
            char str[50];
            sprintf(str, "test1_direct_scheduler_%d", j);
            heuristic_saveSolutionToFile(str, &(instances[i]), solution);
            heuristic_solutionDestroy(solution);
            instance_destroy(&(instances[i]));
        }
    }

    free(instances);

}

char * stringConcat(char * s1, char * s2)
{
    char * string = (char *)malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
    int i = 0;
    int j = 0;
    for(i = 0; i < strlen(s1); i++)
        string[i+j] = s1[i];
    for(j = 0; j < strlen(s2); j++)
        string[i+j] = s2[j];
    string[i+j] = '\0';

    free(s1);
    free(s2);

    return string;

}

char * stringCopy(char * string)
{
    char * str = (char *)malloc(strlen(string) * sizeof(char));
    for(int i = 0; i < strlen(string); i++)
        str[i] = string[i];

    return str;
}
