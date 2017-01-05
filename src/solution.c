#include "heuristic.h"
#include <sys/timeb.h>
#include <stdlib.h>
#include "solution.h"
#include "solutionIndirect.h"

void solution_saveToFile(char *fileName, Solution *solution)
{
	FILE * file;
	if((file = fopen(fileName, "w+")) == NULL)
	{
		perror("ERROR FOPEN solution_saveToFile");
		exit(EXIT_FAILURE);
	}
    fprintf(file, "%d\t%Lf\n", solution_evaluate(solution), solution->solveTime);
	fclose(file);
}

long double solution_getTimeDiff(struct timeb start, struct timeb end)
{
    return end.time - start.time + (end.millitm - start.millitm) / 1000.0f;
}

int solution_evaluate(Solution *solution)
{
	switch(solution->type)
	{
		case DIRECT:
			return solutionDirect_evaluate(solution->instance, solution->solutions.direct->itemsTaken);
		case INDIRECT:
			return solutionIndirect_evaluate(solution->solutions.indirect);
	}
	return -1;
}

int solution_doable(Solution *solution)
{
	switch(solution->type)
	{
		case DIRECT:
			return solutionDirect_doable(solution->instance, solution->solutions.direct->itemsTaken);
		case INDIRECT:
			return solutionIndirect_doable(solution->solutions.indirect);
	}
	return -1;
}

Solution * solution_duplicate(Solution *solution)
{
	return NULL; //TODO Victor
}
