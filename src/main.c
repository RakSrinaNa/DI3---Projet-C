#include <string.h>
#include <stdlib.h>

#include "unit/headers/mainUnit.h"
#include "headers/mainKergosien.h"
#include "headers/parser.h"
#include "headers/solution.h"
#include "headers/metaheuristicLocal.h"
#include "headers/metaheuristicTabou.h"
#include "headers/metaheuristicGenetic.h"

int main(int argc, char * argv[]) //TODO Comment
{
	if(argc >= 4)
	{
		char * filename = argv[1];
		int codeType = atoi(argv[2]);
		int codeMethod = atoi(argv[3]);
		Parser * parser = parser_create(filename);
		Instance * instance;
		while((instance = parser_getNextInstance(parser)) != NULL)
		{
			Solution * solution;
			switch(codeType)
			{
				case 0:
					switch(codeMethod)
					{
						case 0:
							solution = heuristic_search(instance, DIRECT, 0);
							break;
						case 1:
							solution = heuristic_search(instance, INDIRECT, 0);
							break;
						case 2:
							solution = heuristic_search(instance, DIRECT, 1);
							break;
						case 3:
							solution = heuristic_search(instance, INDIRECT, 1);
							break;
						case 4:
							solution = heuristic_search(instance, DIRECT, 2);
							break;
						case 5:
							solution = heuristic_search(instance, INDIRECT, 2);
							break;
						case 6:
							solution = heuristic_search(instance, DIRECT, 3);
							break;
						case 7:
							solution = heuristic_search(instance, INDIRECT, 3);
							break;
						case 8:
							solution = heuristic_search(instance, DIRECT, 4);
							break;
						case 9:
							solution = heuristic_search(instance, INDIRECT, 4);
							break;
						case 10:
							solution = heuristic_search(instance, DIRECT, 5);
							break;
						case 11:
							solution = heuristic_search(instance, INDIRECT, 5);
							break;
						default:
							exit(EXIT_FAILURE);
					}
					solution = heuristic_search(instance, DIRECT, 0);
				case 1:
					switch(codeMethod)
					{
						case 0:
							solution = metaheuristicLocal_search(instance, DIRECT, 0, 5);
						case 1:
							solution = metaheuristicLocal_search(instance, INDIRECT, 0, 5);
						default:
							exit(EXIT_FAILURE);
					}
				case 2:
					switch(codeMethod)
					{
						case 0:
							solution = metaheuristicTabou_search(instance, DIRECT, 50, 50, 1);
						case 1:
							solution = metaheuristicTabou_search(instance, INDIRECT, 50, 50, 1);
						default:
							exit(EXIT_FAILURE);
					}
				case 3:
					switch(codeMethod)
					{
						case 0:
							solution = metaheuristicGenetic_search(instance, DIRECT, 50, 0.2, 50, 0, 0);
						case 1:
							solution = metaheuristicGenetic_search(instance, INDIRECT, 50, 0.2, 50, 0, 0);
						case 2:
							solution = metaheuristicGenetic_search(instance, DIRECT, 50, 0.2, 50, 0, 1);
						case 3:
							solution = metaheuristicGenetic_search(instance, INDIRECT, 50, 0.2, 50, 0, 1);
						case 4:
							solution = metaheuristicGenetic_search(instance, DIRECT, 50, 0.2, 50, 1, 0);
						case 5:
							solution = metaheuristicGenetic_search(instance, INDIRECT, 50, 0.2, 50, 1, 0);
						case 6:
							solution = metaheuristicGenetic_search(instance, DIRECT, 50, 0.2, 50, 1, 1);
						case 7:
							solution = metaheuristicGenetic_search(instance, INDIRECT, 50, 0.2, 50, 1, 1);
						case 8:
							solution = metaheuristicGenetic_search(instance, DIRECT, 50, 0.2, 50, 2, 0);
						case 9:
							solution = metaheuristicGenetic_search(instance, INDIRECT, 50, 0.2, 50, 2, 0);
						case 10:
							solution = metaheuristicGenetic_search(instance, DIRECT, 50, 0.2, 50, 2, 1);
						case 11:
							solution = metaheuristicGenetic_search(instance, INDIRECT, 50, 0.2, 50, 2, 1);
						default:
							exit(EXIT_FAILURE);
					}
				default:
					exit(EXIT_FAILURE);
			}
			if(solution->type == INDIRECT)
				solutionIndirect_print(solution->solutions.indirect);
			else
				solutionDirect_print(solution->solutions.direct);
			solution_destroy(solution);
			instance_destroy(instance);
		}
		parser_destroy(parser);
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
				Solution * solution = metaheuristicLocal_search(instance, DIRECT, 0, 5);
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
