#include <stdlib.h>
#include <memory.h>
#include <dirent.h>

#include "instance.h"
#include "parser.h"
#include "heuristic.h"
#include "solution.h"

void mainKergosien()
{
    char dirName[] = "./MKP-Instances";
    char filePath[200];
    DIR * dir = opendir(dirName);

    int i = 0;

    struct dirent * file;
    while((file = readdir(dir)) != NULL)
    {
        if(strstr(file->d_name, "mknap") == NULL)
            continue;

        i++;

        sprintf(filePath, "%s/%s", dirName, file->d_name);
        printf("Processing file: %s\n", filePath);
        Parser * parser = parser_create(filePath);

        Instance * instance;
        while((instance = parser_getNextInstance(parser)) != NULL)
        {
            for(int j = 0; j < 6; j++)
            {
                if(j < 5)
                    continue;
                char outputFile[100];
                Solution * solution;
                if(1) {
                    solution = heuristic(instance, 1, j);
                    sprintf(outputFile, "Solutions/type_direct_instance_%d_%d_scheduler_%d.txt", i, parser->instanceRead, j);
                    solution_saveToFile(outputFile, solution);
                    printf("Solution written into %s\n", outputFile);
                    solution_destroy(solution);
                }

                if(0) {
                    solution = heuristic(instance, 0, j);
                    sprintf(outputFile, "Solutions/test1_indirect_file_%d_%d_scheduler_%d.txt", i, parser->instanceRead, j);
                    solution_saveToFile(outputFile, solution);
                    printf("Solution written into %s\n", outputFile);
                    solution_destroy(solution);
                }
            }
            instance_destroy(instance);
        }
        parser_destroy(parser);

    }

    closedir(dir);
}
