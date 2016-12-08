#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int * getValuesFomLine(char * line, int valuesNumber)
{
    int * values;
	if((values  = (int *) malloc(sizeof(int) * valuesNumber)) == NULL) // Creating the array for the integers
	{
		printf("MALLOC ERROR getValuesFromLine stringUtils.c");
		exit(1);
	}

    int valuesLength = 0; // Number of values actually put in the array

    int index = 0; // The reading index
    int reading = 0; // Boolean to know if we are currently reading a number

    char * start = line; // The beginning of our number we are reading
    int length = 0; // The length of the number we are reading

    do
    {
        if(line[index] == '\t' || line[index] == ' ' || line[index] == '\0') // If we don't read a number
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

    return values;
}
