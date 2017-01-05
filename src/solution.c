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
			return solutionDirect_evaluate(solution->solutions.direct);
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

Solution * solution_duplicate(Solution * solution)
{
	Solution * newSolution;
	if((newSolution = (Solution *) malloc(sizeof(Solution))) == NULL)
	{
		perror("MALLOC ERROR solution_duplicate");
		exit(EXIT_FAILURE);
	}
	newSolution->instance = solution->instance;
	newSolution->type = solution->type;
	newSolution->solveTime = solution->solveTime;
	switch(solution->type)
	{
		case DIRECT:
			newSolution->solutions.direct = solutionDirect_duplicate(solution->solutions.direct);
			break;

		case INDIRECT:
			newSolution->solutions.indirect = solutionIndirect_duplicate(solution->solutions.indirect);
			break;

		default:
			perror("Unknown solutionType solution_duplicate");
			exit(EXIT_FAILURE);
	}
	return NULL;
}

void solution_destroy(Solution *solution)
{
	switch(solution->type)
	{
		case DIRECT:
			solutionDirect_destroy(solution->solutions.direct);
			break;
		case INDIRECT:
			solutionIndirect_destroy(solution->solutions.indirect);
			break;
	}
	free(solution);
}
