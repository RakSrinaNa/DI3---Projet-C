#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "instance.h"
#include "object.h"
#include "stringUtils.h"

void readFile (char * fileName){

    FILE * file = fopen(fileName, "r");

    int instanceNumber = atoi(readLine(file)); // Read number of instances

    for (int i = 0; i < instanceNumber; i++){

        Instance * instance = (Instance *) malloc(sizeof(Instance));

        char * line = readLine(file); // Read first line
        int * lineNumber = getValuesFromLine(line, 2); // Turn it into array of integer

        instance->objectNumber = lineNumber[0]; // Set number of objects
        instance->dimensionNumber = lineNumber[1]; // Set number of dimensions

        instanceInitialize(instance); // Create the right number of objects

        readLine(file); // Read empty line


        free(line);
        free(lineNumber);
        line = readLine(file); // Read line of values
        lineNumber = getValuesFromLine(line, instance->objectNumber); // Turn it into array of integer

        // Set the values of all objects
        for (int j = 0; j < instance->objectNumber; j++){

            Object * object = (Object *) malloc(sizeof(Object)); // Create an object

            objectInitialize(object, instance->dimensionNumber);
            object->value = lineNumber[j]; // Set the value of the object
            instanceSetObject(instance, object, j); // Put the object

        }

        // Set all dimensions of all objects
        for (int j = 0; j < instance->dimensionNumber; j++){

            free(line);
            free(lineNumber);
            line = readLine(file); // Read line of the j dimension
            lineNumber = getValuesFromLine(line, instance->objectNumber); // Turn it into array of integer

            for (int k = 0; k < instance->objectNumber; k++){

                instance->objects[k]->weights[j] = lineNumber[k];

            }
        }


        free(line);
        free(lineNumber);
        line = readLine(file);
        instance->maxWeights = getValuesFromLine(line, instance->objectNumber); // Turn it into array of integer

        free(line);

        printf("Instance %d\n", i);
        free(instance);

    }

    fclose(file);

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
		{
			return NULL;
		}
	} while(*lineRead == '\n'); // While we have a non empty line
	char * newLineRead;
	if((newLineRead = (char *) realloc(lineRead, sizeRead - 1)) == NULL) // Reduce the malloc size by one
	{
		exit(EXIT_FAILURE);
	}
	newLineRead[sizeRead - 2] = '\0'; // Change the \n into a \0
	return newLineRead;
}
