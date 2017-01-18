#include <string.h>

#include "unit/headers/mainUnit.h"
#include "headers/mainKergosien.h"
#include "headers/parser.h"
#include "headers/solution.h"
#include "headers/metaheuristicGenetic.h"

int main(int argc, char * argv[])
{
	if(argc >= 4)
	{
		char * filename = argv[1];
		//int codeType = atoi(argv[2]);
		//int codeMethod = atoi(argv[3]);
		parser_readAllFile(filename);
	}
	else if(argc == 2) // Used to start tests
	{
		if(strcmp(argv[1], "test") == 0)
		{
			mainUnit();
		}
		else if(strcmp(argv[1], "ker") == 0)
		{
			mainKergosien();
		}
		else if(strcmp(argv[1], "temp") == 0)
		{
			Parser * parser = parser_create("./MKP-Instances/_mknapcb1_res.txt");
			Instance * instance;
			while((instance = parser_getNextInstance(parser)) != NULL)
			{
				Solution * solution = metaheuristicGenetic_search(instance, DIRECT, 100, 0.3, 300, 2);
				if(solution->type == INDIRECT)
					solutionIndirect_print(solution->solutions.indirect);
				else
					solutionDirect_print(solution->solutions.direct);
				solution_destroy(solution);
				instance_destroy(instance);
			}
			parser_destroy(parser);
		}
	}

	return 0;
}
