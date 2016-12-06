#include <stdio.h>
#include <stdlib.h>

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
