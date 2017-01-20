#include <stdlib.h>
#include <memory.h>
#include <dirent.h>
#include <sys/stat.h>

#include "headers/instance.h"
#include "headers/parser.h"
#include "headers/heuristic.h"
#include "headers/metaheuristicLocal.h"
#include "headers/metaheuristicTabou.h"
#include "headers/metaheuristicGenetic.h"
#include "headers/metaheuristicKaguya.h"

void mainKergosien()
{
#if defined(_WIN32)
	_mkdir("Solutions");
#else
	mkdir("Solutions", S_IRWXU | S_IRWXG | S_IRWXO);
#endif

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

		if(i != 1)
            continue;

		sprintf(filePath, "%s/%s", dirName, file->d_name);
		printf("Processing file: %s\n", filePath);
		Parser * parser = parser_create(filePath);

		Instance * instance;
		while((instance = parser_getNextInstance(parser)) != NULL)
		{
            char outputFile[100];
            Solution * solution;
            if(1)
            {
                solution = metaheuristicKaguya_search(instance, DIRECT);
                sprintf(outputFile, "Solutions/type_direct_instance_%d_%d_scheduler_%d.txt", i, parser->instanceRead, 5);
                solution_saveToFile(outputFile, solution);
                printf("Solution written into %s\n", outputFile);
                solution_destroy(solution);
            }

            if(0)
            {
                solution = metaheuristicGenetic_search(instance, INDIRECT, 100, 0.1, 250, 0);
                solutionIndirect_print(solution->solutions.indirect);
                sprintf(outputFile, "Solutions/test1_indirect_file_%d_%d_scheduler_%d.txt", i, parser->instanceRead, 5);
                solution_saveToFile(outputFile, solution);
                printf("Solution written into %s\n", outputFile);
                solution_destroy(solution);
            }

			instance_destroy(instance);
		}
		parser_destroy(parser);
	}

	closedir(dir);
}
