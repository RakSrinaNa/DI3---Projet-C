#include "headers/heuristic.h"
#include "headers/utils.h"
#include "headers/solution.h"
#include <stdlib.h>

void solution_saveToFile(char * fileName, Solution * solution)
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

int solution_evaluate(Solution * solution)
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

int solution_doable(Solution * solution)
{
	switch(solution->type)
	{
		case DIRECT:
			return solutionDirect_doable(solution->solutions.direct);
		case INDIRECT:
			return solutionIndirect_doable(solution->solutions.indirect);
	}
	return -1;
}

Solution * solution_duplicate(Solution * solution)
{
	Solution * newSolution;
	MMALLOC(newSolution, Solution, 1, "solution_duplicate");
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
	return newSolution;
}

void solution_destroy(Solution * solution)
{
	if(solution == NULL)
		return;
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

Solution * solution_fromIndirect(SolutionIndirect * solutionIndirect)
{
	Solution * solution;
	MMALLOC(solution, Solution, 1, "solution_fromIndirect");
	solution->solveTime = 0;
	solution->type = INDIRECT;
	solution->solutions.indirect = solutionIndirect;
	solution->instance = solutionIndirect->instance;
	return solution;
}

Solution * solution_fromDirect(SolutionDirect * solutionDirect)
{
	Solution * solution;
	MMALLOC(solution, Solution, 1, "solution_fromDirect");
	solution->solveTime = 0;
	solution->type = DIRECT;
	solution->solutions.direct = solutionDirect;
	solution->instance = solutionDirect->instance;
	return solution;
}
