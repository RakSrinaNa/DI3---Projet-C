#define _POSIX_C_SOURCE_200809L

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "instance.h"
#include "parser.h"

Instance * readFile (char * fileName)
{
    FILE * file;
    if((file = fopen(fileName, "r")) == NULL)
    {
        perror("ERROR FOPEN readFile parser.c");
        exit(EXIT_FAILURE);
    }

    int instancesNumber = atoi(readLine(file)); // Read number of instances
    Instance * instances;
    if((instances = (Instance *) malloc(instancesNumber * sizeof(Instance))) == NULL)
    {
        perror("ERROR MALLOC readFile parser.c");
        exit(EXIT_FAILURE);
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
	instance_initialize(instance, lineNumbers[0], lineNumbers[1]); // Create the right number of items
    free(lineNumbers);

    readLine(file); // Read empty line

    line = readLine(file); // Read line of values
    lineNumbers = getValuesFromLine(line, instance->itemsCount); // Turn it into an array of integer
    free(line);

    for (int i = 0; i < instance->itemsCount; i++) // Set the values of all items
		instance_getItem(instance, i)->value = lineNumbers[i]; // Set the value of the item
    free(lineNumbers);

    for (int dimension = 0; dimension < instance->dimensionsNumber; dimension++) // Set all dimension values of all items
    {
        line = readLine(file); // Read line of the j dimension
        lineNumbers = getValuesFromLine(line, instance->itemsCount); // Turn it into array of integer
        free(line);

        for (int i = 0; i < instance->itemsCount; i++)
			item_setWeight(instance_getItem(instance, i), dimension, lineNumbers[i]);
        free(lineNumbers);
    }

    line = readLine(file);
    instance->maxWeights = getValuesFromLine(line, instance->itemsCount); // Turn it into array of integer
    free(line);
    return instance;
}

char * readLine(FILE * file)
{
	char * lineRead = NULL;
	size_t sizeLine = 0;
    ssize_t sizeRead = 0;
	do
	{
		if(lineRead != NULL) // If an empty line was read before, free it
		{
			free(lineRead);
			lineRead = NULL;
		}
		if((sizeRead = getline(&lineRead, &sizeLine, file)) == -1) // Read a line, and return NULL if end of file
			return NULL;
	} while(*lineRead == '\n'); // While we have a non empty line
	return lineRead;
}

int * getValuesFromLine(char * line, int valuesNumber)
{
	int * values;
	if((values  = (int *) malloc(sizeof(int) * valuesNumber)) == NULL) // Creating the array for the integers
	{
		perror("ERROR MALLOC getValuesFromLine parser.c");
		exit(EXIT_FAILURE);
	}

	int valuesLength = 0; // Number of values actually put in the array

	int index = 0; // The reading index
	int reading = 0; // Boolean to know if we are currently reading a number

	char * start = line; // The beginning of our number we are reading
	int length = 0; // The length of the number we are reading

	do
	{
		if(line[index] == '\t' || line[index] == ' ' || line[index] == '\0' || line[index] == '\n') // If we don't read a number
		{
			if(reading) // If we were reading, add the number to the array
			{
				reading = 0;

				valuesLength++;

				char buffer[10] = {0};
				memcpy(buffer, start, length);
				buffer[length] = '\0';
				values[valuesLength - 1] = atoi(buffer);

				length = 0;

				if(valuesLength == valuesNumber) // If we read enough, stop
				{
					break;
				}
			}
		}
		else // If we read a number
		{
			if(!reading) // If we just started reading it, change start and reading values
			{
				reading = 1;
				start = line + index;
			}
			length++;
		}
		index++;
	} while(line[index - 1] != '\0'); // Read while we didn't reached the end of the string
	for(int i = valuesLength; i < valuesNumber; i++) // Set missing values to 0
		values[i] = 0;
	return values;
}
