#ifndef OBJECT
#define OBJECT

typedef struct _object{

    int value;
    int * weights;

} Object;

void objectInitialize(Object * object, int dimensionsNumber);
void objectFinalize(Object * object);


#endif
