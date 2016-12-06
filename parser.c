#include <stdio.h>
#include <stdlib.h>

void readFile (char * fileName){

    FILE * file = fopen(fileName);
    Instance instance;

    int instanceNumber = atoi(readLine(file)); // Read number of instances

    char * line = readLine(file); // Read first line

    instance.objectNumber = atoi(stringToTab(line)[0]); // Set number of objects
    instance.dimensionNumber = atoi(stringToTab(line)[1]); // Set number of dimensions

    readLine(file); // Read empty line


    fclose(file);

}

int * stringToTab(char * string){

    int * tab = malloc(sizeof(int));
    int number = 0;

    while (*string != '\0'){


    }

}
