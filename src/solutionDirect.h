#ifndef SOLUTION
#define SOLUTION

typedef struct {

    int * itemsTaken;

    int (*evaluate)(Instance * instance, int * items);
    int (*doable)(Instance * instance, int * items);
    void (*print)(Instance * instance, int * items);
    void (*saveToFile)(char * fileName, Instance * instance, int * items);

} SolutionDirect;

#endif
