#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instance.h"
#include "parser.h"

Parser * parser_create(char * filename)
{
	Parser * parser;
	if((parser = (Parser *) malloc(sizeof(Parser))) == NULL)
	{
		perror("ERROR MALLOC parser_create");
		exit(EXIT_FAILURE);
	}
	parser->filename = filename;
	parser->offset = 0;
	parser->instanceRead = 0;
	FILE * file;
	if((file = fopen(parser->filename, "rb")) == NULL)
	{
		perror("ERROR FOPEN parser_create");
		exit(EXIT_FAILURE);
	}

	parser->instanceCount = atoi(parser_readLine(file)); // Read number of instances
	if(fgetpos(file, &(parser->offset)) != 0)
    {
        perror("ERROR FGETPOS parser_create");
        exit(EXIT_FAILURE);
    }
	fclose(file);
	
	return parser;
}

void parser_destroy(Parser * parser)
{
	free(parser);
}

Instance * parser_getNextInstance(Parser * parser)
{
	if(parser->instanceRead >= parser->instanceCount)
		return NULL;
	Instance * instance;
	if((instance = (Instance *) malloc(sizeof(Instance))) == NULL) // Create instance
	{
		perror("ERROR MALLOC parser_getNextInstance");
		exit(EXIT_FAILURE);
	}
	
	FILE * file;
	if((file = fopen(parser->filename, "rb")) == NULL)
	{
		perror("ERROR FOPEN parser_getNextInstance");
		exit(EXIT_FAILURE);
	}
	fsetpos(file, &(parser->offset));
	parser_readInstance(file, instance);
	parser->instanceCount = atoi(parser_readLine(file)); // Read number of instances
	parser->offset = ftell(file);
	fclose(file);
	parser->instanceRead++;
	return instance;
}

Instance * parser_readAllFile(char * fileName)
{
	FILE * file;
	if((file = fopen(fileName, "r")) == NULL)
	{
		perror("ERROR FOPEN parser_readAllFile");
		exit(EXIT_FAILURE);
	}
	
	int instancesNumber = atoi(parser_readLine(file)); // Read number of instances
	Instance * instances;
	if((instances = (Instance *) malloc(instancesNumber * sizeof(Instance))) == NULL) // Create instances
	{
		perror("ERROR MALLOC parser_readAllFile");
		exit(EXIT_FAILURE);
	}
	
	for(int instanceIndex = 0; instanceIndex < instancesNumber; instanceIndex++) // Read every instance
		parser_readInstance(file, instances + instanceIndex);
	
	fclose(file);
	return instances;
}

void parser_readInstance(FILE * file, Instance * instance)
{
	char * line = parser_readLine(file); // Read the number of items and dimensions
	int * lineNumbers = parser_lineToIntArray(line, 2);
	free(line);
	instance_initialize(instance, lineNumbers[0], lineNumbers[1]); // Initialize the instance with the number of items and dimensions
	free(lineNumbers);
	
	parser_readLine(file); // Read line to skip it, we don't use it for now
	
	line = parser_readLine(file); // Read line of values
	lineNumbers = parser_lineToIntArray(line, instance->itemsCount);
	free(line);
	
	for(int i = 0; i < instance->itemsCount; i++) // Set the values of all items
		instance_getItem(instance, i)->value = lineNumbers[i];
	free(lineNumbers);
	
	for(int dimension = 0; dimension < instance->dimensionsNumber; dimension++) // Set all dimension values of all items
	{
		line = parser_readLine(file); // Read line of the 'dimention'th dimension
		lineNumbers = parser_lineToIntArray(line, instance->itemsCount);
		free(line);
		
		for(int i = 0; i < instance->itemsCount; i++) // Set the weight for its associated item
			item_setWeight(instance_getItem(instance, i), dimension, lineNumbers[i]);
		free(lineNumbers);
	}
	
	line = parser_readLine(file); // Read maximum weights
	instance_setMaxWeights(instance, parser_lineToIntArray(line, instance->itemsCount));
	free(line);
}

char * parser_readLine(FILE * file)
{
	char * lineRead = NULL;
	size_t size = 0;
	do
	{
		if(lineRead != NULL) // If an empty line was read before, free it
		{
			free(lineRead);
			lineRead = NULL;
		}
		if(getLine(&lineRead, &size, file) == -1) // Read a line, and return NULL if end of file
			return NULL;
	} while(*lineRead == '\n'); // While we have a non empty line
	return lineRead;
}

int * parser_lineToIntArray(char * line, int valuesNumber)
{
	int * values;
	if((values = (int *) malloc(sizeof(int) * valuesNumber)) == NULL) // Creating the array for the integers
	{
		perror("ERROR MALLOC parser_lineToIntArray parser.c");
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
				memcpy(buffer, start, (unsigned int)length);
				buffer[length] = '\0';
				values[valuesLength - 1] = atoi(buffer);
				
				length = 0;
				
				if(valuesLength == valuesNumber) // If we read enough, stop
					break;
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


int getLine(char ** linePtr, size_t * lineSize, FILE * file)
{
	char * bufferPtr = NULL; // Buffer string
	unsigned int writingHead = 0; // Pointer to the writing position in the buffer
	size_t size = 0; // The size of the buffer
	int charRead; // The char read
	
	if(linePtr == NULL || file == NULL || lineSize == NULL)
		return -1;
	
	bufferPtr = *linePtr;
	size = *lineSize;
	charRead = fgetc(file);
	if(charRead == EOF)
		return -1;
	if(bufferPtr == NULL) // If the string passed as parameter is NULL, initialize it
	{
		bufferPtr = (char *) malloc(50 * sizeof(char));
		if(bufferPtr == NULL)
			return -1;
		size = 50;
	}
	while(charRead != EOF) // While we didn't reach the end of the file
	{
		if(writingHead > size - 1U) // If we went over the buffer size (letting space for \0), make it bigger
		{
			size += 50;
			char * newBufferPtr = realloc(bufferPtr, size);
			if(newBufferPtr == NULL) // If realloc fails
			{
				bufferPtr[writingHead] = '\0';
				*linePtr = bufferPtr;
				*lineSize = size;
				return -1;
			}
			bufferPtr = newBufferPtr;
		}
		bufferPtr[writingHead++] = (char) charRead; // Write the char read into out buffer
		if(charRead == '\n') // If it's the end of the line, get out of the while
			break;
		charRead = fgetc(file); // Read next char
	}
	
	bufferPtr[writingHead++] = '\0'; // Write the terminating byte
	*linePtr = bufferPtr; // Set the buffer at being pointed by linePtr
	*lineSize = size; // Set size being pointer by lineSize
	
	return writingHead - 1; // Return the length of the read string, not counting the terminating byte
}
