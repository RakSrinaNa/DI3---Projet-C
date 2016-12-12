#ifndef SOLUTIONINDIRECT
#define SOLUTIONINDIRECT

#include "solutionIndirect.h"
#include "bag.h"
#include "instance.h"

typedef struct
{
	int * itemsOrder;
	Bag * bag;

	// Functions
	int (* evaluate)(Instance * instance, Bag * bag);

	int (* doable)(Instance * instance, Bag * bag);

	void (* print)(Instance * instance, Bag * bag);

	void (* saveToFile)(char * fileName, Instance * instance, SolutionIndirect * solution, Bag * bag);
} SolutionIndirect;

SolutionIndirect * solutionIndirect_create(Instance * instance);

void solutionIndirect_destroy(SolutionIndirect * solution);

void solutionIndirect_decode(Instance * instance, SolutionIndirect * solution);

int solutionIndirect_evaluate(Instance * instance, Bag * bag);

int solutionIndirect_doable(Instance * instance, Bag * bag);

void solutionIndirect_print(Instance * instance, Bag * bag);

void solutionIndirect_saveToFile(char * fileName, Instance * instance, SolutionIndirect * solution, Bag * bag);

#endif
