#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int * getValuesFromLine(char * line, int valuesNumber)
{
    int * values = (int *) malloc(sizeof(int) * valuesNumber);
    int valuesLength = 0;

    int index = 0;
    int reading = 0;

    char * start = line;
    int length = 0;
    do
    {
        if(line[index] == '\t' || line[index] == ' ' || line[index] == '\0')
        {
            if(reading)
            {
                reading = 0;

                valuesLength++;

                char buffer[10] = {0};
                memcpy(buffer, start, length);
                buffer[length] = '\0';
                values[valuesLength - 1] = atoi(buffer);

                length = 0;

                if(valuesLength == valuesNumber)
                {
                    break;
                }
            }
        }
        else
        {
            if(!reading)
            {
                reading = 1;
                start = line + index;
            }
            length++;
        }
        index++;
    } while(line[index - 1] != '\0');

    return values;
}
