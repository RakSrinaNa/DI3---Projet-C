#ifndef OBJECT
    #define OBJECT

    typedef struct{
        int value;
        int * weights;
    } Item;

    void itemInitialize (Item *item, int dimensionsNumber);
    void itemSetWeight (Item *item, int weightPos, int weight);
    void itemDestroy (Item *item);

#endif
