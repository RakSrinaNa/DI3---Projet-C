#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "object.h"
#include "parser.h"
#include "stringUtils.h"

Instance * readFile (char * fileName)
{
    FILE * file;
    if((file = fopen(fileName, "r")) == NULL)
    {
        printf("ERROR FOPEN readFile parser.c");
        exit(1);
    }

    int instancesNumber = atoi(readLine(file)); // Read number of instances
    Instance * instances;
    if((instances = (Instance *) malloc(instancesNumber * sizeof(Instance))) == NULL)
    {
        printf("ERROR MALLOC readFile parser.c");
        exit(1);
    }

    for (int instanceIndex = 0; instanceIndex < instancesNumber; instanceIndex++)
        readInstance(file, instances + instanceIndex);

    fclose(file);
    return instances;
}

Instance * readInstance(FILE * file, Instance * instance)
{
    char * line = readLine(file); // Read first line
    int * lineNumbers = getValuesFromLine(line, 2); // Turn it into array of integer
    free(line);
    instance->objectsNumber = lineNumbers[0]; // Set number of objects
    instance->dimensionsNumber = lineNumbers[1]; // Set number of dimensions
    instanceInitialize(instance); // Create the right number of objects
    free(lineNumbers);

    readLine(file); // Read empty line

    line = readLine(file); // Read line of values
    lineNumbers = getValuesFromLine(line, instance->objectsNumber); // Turn it into an array of integer
    free(line);

    for (int i = 0; i < instance->objectsNumber; i++) // Set the values of all objects
        instanceGetObjectAt(instance, i)->value = lineNumbers[i]; // Set the value of the object
    free(lineNumbers);

    for (int dimension = 0; dimension < instance->dimensionsNumber; dimension++) // Set all dimension values of all objects
    {
        line = readLine(file); // Read line of the j dimension
        lineNumbers = getValuesFromLine(line, instance->objectsNumber); // Turn it into array of integer
        free(line);

        for (int i = 0; i < instance->objectsNumber; i++)
            objectSetWeight(instanceGetObjectAt(instance, i), dimension, lineNumbers[i]);
        free(lineNumbers);
    }

    line = readLine(file);
    instance->maxWeights = getValuesFromLine(line, instance->objectsNumber); // Turn it into array of integer
    free(line);
    return instance;
}

char * readLine(FILE * file)
{
	char * lineRead = NULL;
	size_t sizeRead = 0;
	do
	{
		if(lineRead != NULL) // If an empty line was read before, free it
		{
			free(lineRead);
			lineRead = NULL;
		}
		if(getline(&lineRead, &sizeRead, file) == -1) // Read a line, and return NULL if end of file
			return NULL;
	} while(*lineRead == '\n'); // While we have a non empty line
	char * newLineRead;
	if((newLineRead = (char *) realloc(lineRead, sizeRead - 1)) == NULL) // Reduce the malloc size by one
	{
        printf("ERROR REALLOC readLine parser.c");
		exit(1);
	}
	newLineRead[sizeRead - 2] = '\0'; // Change the \n into a \0
	return newLineRead;
}
