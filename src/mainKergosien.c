#include <stdlib.h>
#include <memory.h>
#include <dirent.h>

#include "instance.h"
#include "parser.h"
#include "heuristic.h"

void mainKergosien()
{
    char dirName[] = "./MKP-Instances";
    char str[200];
    DIR * dir = opendir(dirName);

    int i = 0;

    struct dirent * file;
    while((file = readdir(dir)) != NULL)
    {
        if(strcoll(file->d_name, "mknap") == NULL)
            continue;

        i++;

        sprintf(str, "%s/%s", dirName, file->d_name);
        Parser * parser = parser_create(str);

        Instance * instance;
        while((instance = parser_getNextInstance(parser)) != NULL)
        {
            for(int j = 0; j < 5; j++)
            {
                char str2[50];
                Solution * solution = heuristic(instance, 1, j);
                sprintf(str2, "Solutions/test1_direct_file_%d_scheduler_%d.txt", i, j);
                heuristic_saveSolutionToFile(str2, instance, solution);
                heuristic_solutionDestroy(solution);

                solution = heuristic(instance, 0, j);
                sprintf(str2, "Solutions/test1_indirect_file_%d_scheduler_%d.txt", i, j);
                heuristic_saveSolutionToFile(str2, instance, solution);
                heuristic_solutionDestroy(solution);
            }
            instance_destroy(instance);
        }
        parser_destroy(parser);

    }

    closedir(dir);
}
