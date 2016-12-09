#ifndef SOLUTIONDIRECT
#define SOLUTIONDIRECT

typedef struct {

    int * itemsTaken;

    int (*evaluate)(Instance * instance, int * items);
    int (*doable)(Instance * instance, int * items);
    void (*print)(Instance * instance, int * items);
    void (*saveToFile)(char * fileName, Instance * instance, int * items);

} SolutionDirect;

SolutionDirect *  solutionDirectCreate(Instance * instance);
void solutionDirectDestroy(SolutionDirect * solution);
int solutionDirectEvaluate(Instance * instance, int * items);
int solutionDirectDoable(Instance * instance, int * items);
void solutionDirectPrint(Instance * instance, int * items);
void solutionDirectSaveToFile(char * fileName, Instance * instance, int * items);

#endif
